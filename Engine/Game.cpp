/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "FrameTimer.h"
#include "MapLoader.h"
#include "Random.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	Platform::LoadSprites();
	Spike::LoadSurfs();

	MapLoader::UpdateNLevels( nMaxLevels );

	MapLoader::AddPlats( MapLoader::GetLevel( 0 ),
		{ 0,0 },plats,spikes,enemies,grasses );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = FrameTimer::Mark() * dtMult;

	if( dt > 0.05f ) dt = 0.0f;

	if( state == GameState::Menu )
	{
		start.Update( wnd.mouse );
		quit.Update( wnd.mouse );
		lvlEditor.Update( wnd.mouse );

		if( start.IsPressed() ) state = GameState::Started;
		if( quit.IsPressed() ) wnd.Kill();
		if( lvlEditor.IsPressed() ) state = GameState::LevelEditor;

		// Not a huge fan of return for flow control,
		//  but in this case I think it's okay.
		return;
	}
	else if( state == GameState::LevelEditor )
	{
		le.Update( wnd.mouse,nMaxLevels,dt );
		menu.Update( wnd.mouse );
		if( menu.IsPressed() ) HardRestart();
		return;
	}

	restart.Update( wnd.mouse );
	menu.Update( wnd.mouse );
	if( restart.IsPressed() ) SoftRestart();
	if( menu.IsPressed() ) HardRestart();

	curTime += dt;

	pl.Update2( wnd.kbd,dt );
	pl.CheckHits( plats );

	if( !pl.GetRect().IsContainedBy( Graphics
		::GetScreenRect() ) )
	{
		Restart();
		return;
	}

	for( auto& it = plats.begin();
		it < plats.end();
		++it )
	{
		it->Move( { -moveSpeed * dt,0.0f } );

		if( it->WillDelete() )
		{
			it = plats.erase( it );
			if( it == plats.end() ) break;
		}
	}

	const bool plJumping = pl.IsJumping();
	for( auto& it = spikes.begin();
		it < spikes.end();
		++it )
	{
		if( it->GetRect()
			.IsOverlappingWith( pl.GetRect() ) &&
			!pl.DashIsActive() )
		{
			Restart();
			return;
		}

		it->Update( pl.GetPos(),dt );
		it->Move( { -moveSpeed * dt,0.0f } );

		if( it->GetRect().IsOverlappingWith( pl.GetDashHitbox() ) &&
			pl.DashIsActive() )
		{
			it->Destroy();
		}

		if( plJumping )
		{
			it->OnPlayerJump( dt );
		}

		if( it->IsDead() )
		{
			it = spikes.erase( it );
			if( it == spikes.end() ) break;
		}
	}

	for( auto& it = enemies.begin();
		it < enemies.end();
		++it )
	{
		it->Update( dt );
		it->CheckHits( plats );
		it->Move( { -moveSpeed * dt,0.0f } );

		if( it->GetRect().IsOverlappingWith( pl.GetDashHitbox() ) &&
			pl.DashIsActive() )
		{
			it->Destroy();
		}

		if( pl.GetRect()
			.IsOverlappingWith( it->GetRect() ) &&
			!pl.DashIsActive() )
		{
			Restart();
			return;
		}

		if( it->IsDead() )
		{
			it = enemies.erase( it );
			if( it == enemies.end() ) break;
		}
	}

	if( plats[plats.size() - 1].GetRect().right <
		float( Graphics::ScreenWidth ) )
	{
		MapLoader::AddPlats( MapLoader::GetLevel( Random
			::RangeI( 1,nMaxLevels ) ),
			Vei2( int( plats[plats.size() - 1]
				.GetRect().right ),0 ),
			plats,spikes,enemies,grasses );
	}

	for( auto& grass : grasses )
	{
		grass.Move( { -moveSpeed * dt,0.0f } );
		grass.Update( dt );
	}

	textPos -= moveSpeed * dt;
}

void Game::Restart()
{
	dtMult = 0.0f;
}

void Game::HardRestart()
{
	// started = false;
	state = GameState::Menu;
	
	SoftRestart();
}

void Game::SoftRestart()
{
	textPos = textOffset / 2.0f;

	curTime = 0.0f;
	dtMult = 1.0f;

	pl.Reset();

	plats.clear();
	spikes.clear();
	enemies.clear();

	MapLoader::AddPlats( MapLoader::GetLevel( 0 ),
		{ 0,0 },plats,spikes,enemies,grasses );
}

void Game::ComposeFrame()
{
	if( state == GameState::Menu )
	{
		crOrig.DrawText( "Cave Runner",{ 40,40 },
			Colors::White,gfx );

		start.Draw( gfx );
		quit.Draw( gfx );
		lvlEditor.Draw( gfx );

		return;
	}
	else if( state == GameState::LevelEditor )
	{
		le.Draw( gfx );
		menu.Draw( gfx );
		
		return;
	}

#if NDEBUG
	gfx.DrawRect( 0,0,
		Graphics::ScreenWidth,Graphics::ScreenHeight,
		Colors::Brown );
#endif

	for( const Platform& plat : plats )
	{
		plat.Draw( gfx );
	}
	for( const Spike& spike : spikes )
	{
		spike.Draw( gfx );
	}
	for( const Enemy& e : enemies )
	{
		e.Draw( gfx );
	}
	for( const Grass& g : grasses )
	{
		g.Draw( gfx );
	}

	pl.Draw( gfx );

#if NDEBUG
	gfx.DrawRectDim( 0,320,
		Graphics::ScreenWidth,Graphics::ScreenHeight,
		Colors::Gray );
#endif

	restart.Draw( gfx );
	menu.Draw( gfx );

	crOrig.DrawText( std::to_string( int( curTime ) ),
		{ gfx.ScreenWidth / 2 - 5,360 },Colors::White,gfx );

	if( textPos + textOffset * 6.0f > 0.0f )
	{
		crOrig.DrawText( "W to jumP",
			Vei2( Vec2{ textPos,textHeight } ),
			Colors::White,gfx );
		crOrig.DrawText( "jumPing makes the\nrocks fall",
			Vei2( Vec2{ textPos + textOffset,textHeight } ),
			Colors::White,gfx );
		crOrig.DrawText( "D to dash",
			Vei2( Vec2{ textPos + textOffset * 2.0f,textHeight } ),
			Colors::White,gfx );
		crOrig.DrawText( "Dashing kills enemies",
			Vei2( Vec2{ textPos + textOffset * 3.0f,textHeight } ),
			Colors::White,gfx );
		crOrig.DrawText( "Don't get Pushed back!",
			Vei2( Vec2{ textPos + textOffset * 4.0f,textHeight } ),
			Colors::White,gfx );
	}
}
