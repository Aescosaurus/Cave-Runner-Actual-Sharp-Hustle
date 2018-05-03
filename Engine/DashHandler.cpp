#include "DashHandler.h"
#include "SpriteEffect.h"

const Surface Dash::surf = Surface( "Images/Slash.bmp" );
Dash DashHandler::curDash( { -9999.0f,-9999.0f } );

Dash::Dash( const Vec2& pos )
	:
	pos( Vei2( pos ) ),
	hitbox( pos,
		float( surf.GetWidth() ),
		float( surf.GetHeight() ) ),
	timer( 0.0f )
{
}

void Dash::Update( float dt )
{
	if( timer > lifetime )
	{
		pos = { -9999,-9999 };
		hitbox.MoveTo( pos );
	}
	else timer += dt;
}

void Dash::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x,pos.y,surf,SpriteEffect
		::Chroma( Colors::Magenta ) );
}

const Rect& Dash::GetRect() const
{
	return hitbox;
}

bool Dash::IsActive() const
{
	return( timer < lifetime );
}

void DashHandler::Update( float dt )
{
	curDash.Update( dt );
}

void DashHandler::Draw( Graphics& gfx )
{
	curDash.Draw( gfx );
}

void DashHandler::AddDash( const Vec2& pos )
{
	curDash = Dash( pos );
}

Rect DashHandler::GetRect()
{
	return curDash.GetRect();
}

bool DashHandler::DashActive()
{
	return( curDash.IsActive() );
}
