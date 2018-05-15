#include "Spike.h"
#include "Random.h"
#include "SpriteEffect.h"

std::vector<Surface> Spike::surfs;
Sound Spike::Crash = Sound( "Audio/Crash.wav" );

Spike::Spike( const Vec2& pos )
	:
	pos( pos ),
	hitbox( pos,float( size ),float( size ) ),
	mySurf( Random::RangeI( 0,nSurfs - 1 ) )
{
}

void Spike::Update( const Vec2& plPos,float dt )
{
	if( falling )
	{
		grav += gravAcc;
		pos.y += grav;
	}
}

void Spike::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),
		surfs[mySurf],SpriteEffect
		::Chroma( Colors::Magenta ) );

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

void Spike::LoadSurfs()
{
	for( int i = 0; i < nSurfs; ++i )
	{
		surfs.emplace_back( Surface( "Images/Spike" + std
			::to_string( i + 1 ) + ".bmp" )
			.GetExpanded( size,size ) );
	}
}

void Spike::Move( const Vec2& amount )
{
	pos += amount;

	hitbox.MoveTo( pos );
}

void Spike::OnPlayerJump( float dt )
{
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		if( Random::RangeI( 0,10 ) > 7 )
		{
			falling = true;
			Crash.Play();
		}
	}
}

void Spike::Destroy()
{
	dead = true;
	// Spawn particles or something here.
}

const Rect& Spike::GetRect() const
{
	return hitbox;
}

bool Spike::IsDead() const
{
	return( ( pos.y > float( Graphics::ScreenHeight ) ||
		pos.x + float( size ) < 0.0f ) || dead );
}
