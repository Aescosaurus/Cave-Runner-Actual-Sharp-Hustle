#include "Platform.h"
#include "Random.h"
#include "SpriteEffect.h"

std::vector<Surface> Platform::sprites;

Platform::Platform( const Vei2& pos )
	:
	pos( Vec2( pos ) ),
	hitbox( pos,float( size ),float( size ) ),
	mySprite( Random::RangeI( 0,nSprites - 1 ) )
{
}

void Platform::Draw( Graphics& gfx ) const
{
	// gfx.DrawRect( int( pos.x ),int( pos.y ),
	// 	size,size,Colors::Gray );

	gfx.DrawSprite( int( round( pos.x ) ),
		int( round( pos.y ) ),
		sprites[mySprite],SpriteEffect::Copy() );

#if 0
	if( hitbox.IsContainedBy( Graphics
		::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

void Platform::Move( const Vec2& moveAmount )
{
	pos += moveAmount;
	hitbox.MoveTo( pos );
}

void Platform::LoadSprites()
{
	for( int i = 0; i < nSprites; ++i )
	{
		// Use i + 1 because Block1 is first.
		sprites.emplace_back( Surface( "Images/Block" +
			std::to_string( i + 1 ) + ".bmp" )
			.GetExpanded( size,size ) );
	}
}

const Rect& Platform::GetRect() const
{
	return( hitbox );
}

bool Platform::WillDelete() const
{
	return( pos.x + float( size ) < -float( size ) );
}
