#include "LevelEditor.h"
#include "SpriteEffect.h"
#include <fstream>
#include "MapLoader.h"

LevelEditor::LevelEditor( const Font& ref )
	:
	myFont( ref )
{
	tiles.resize( width * height );

	for( int i = 0; i < width; ++i )
	{
		tiles[i] = 1;
	}

	const int offset = width * height - width;
	for( int i = 0; i < width; ++i )
	{
		tiles[i + offset] = 1;
	}
}

void LevelEditor::Update( const Mouse& mouse,int& nLevels,float dt )
{
	blank.Update( mouse );
	block.Update( mouse );
	spike.Update( mouse );
	enemyb.Update( mouse );
	grassb.Update( mouse );

	save.Update( mouse );
	load.Update( mouse );

	if( save.IsPressed() ) Save( nLevels );
	if( load.IsPressed() ) Load();

	if( blank.IsPressed() ) brush = 0;
	if( block.IsPressed() ) brush = 1;
	if( spike.IsPressed() ) brush = 2;
	if( enemyb.IsPressed() ) brush = 3;
	if( grassb.IsPressed() ) brush = 4;

	{
		auto msPos = mouse.GetPos();
		msPos -= { startX,startY };

		while( msPos.x % 32 != 0 ) --msPos.x;
		while( msPos.y % 32 != 0 ) --msPos.y;

		msPos.x = msPos.x / 32;
		msPos.y = msPos.y / 32;

		if( msPos.x >= 0 && msPos.y >= 0 &&
			msPos.x < width && msPos.y < height )
		{
			curMsPos = msPos;

			if( mouse.LeftIsPressed() )
			{
				tiles[msPos.y * width + msPos.x] = brush;
			}
		}
	}

	if( saveTimer <= saveCooldown ) saveTimer += dt;
}

void LevelEditor::Draw( Graphics& gfx ) const
{
#if NDEBUG
	gfx.DrawRect( 0,0,
		Graphics::ScreenWidth,Graphics::ScreenHeight,
		Colors::Brown );

	gfx.DrawRectDim( 0,320,
		Graphics::ScreenWidth,Graphics::ScreenHeight,
		Colors::Gray );
#endif
	for( int i = 0; i < height; ++i )
	{
		for( int j = 0; j < width; ++j )
		{
			const auto tile = tiles[i * width + j];
			// 0 = background,
			// 1 = floor/wall,
			// 2 = spike,
			// 3 = enemy
			if( tile == 0 ) continue;

			gfx.DrawSprite( j * 32 + startX,i * 32 + startY,
				imgs[tile - 1],
				SpriteEffect::Chroma( Colors::Magenta ) );
		}
	}

	if( brush > 0 )
	{
		gfx.DrawSprite( curMsPos.x * 32,curMsPos.y * 32,
			imgs[brush - 1],
			SpriteEffect::Chroma( Colors::Magenta ) );
	}
	else
	{
		gfx.DrawRect( curMsPos.x * 32,curMsPos.y * 32,
			32,32,Colors::Black );
	}

	blank.Draw( gfx );
	block.Draw( gfx );
	spike.Draw( gfx );
	enemyb.Draw( gfx );
	grassb.Draw( gfx );

	save.Draw( gfx );
	load.Draw( gfx );

	if( saveTimer < saveCooldown )
	{
		myFont.DrawText( "Saved",{ Graphics::ScreenWidth / 2 -
			100,Graphics::ScreenHeight / 2 - 50 },Colors::White,
			saveTimer,gfx );
	}
}

void LevelEditor::Save( int& nLevels )
{
	saveTimer = 0.0f;

	for( int i = 1; i < 9999999; ++i )
	{
		const std::string name = "Maps/Level" + std::to_string( i ) + ".lvl";
		std::ifstream test( name );

		if( test.good() ) continue;
		else
		{
			std::ofstream out( name );
			// for( int i : tiles )
			for( int i = 0; i < int( tiles.size() ); ++i )
			{
				if( i != 0 && i % width == 0 ) out << '\n';
				out << tiles[i];
			}
			out.close();

			break;
		}
	}

	MapLoader::UpdateNLevels( nLevels );

	// Put a popup here saying you saved.
}

void LevelEditor::Load()
{
}
