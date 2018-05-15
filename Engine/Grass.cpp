#include "Grass.h"
#include "Random.h"

const Surface Grass::img = Surface( "Images/Grass.bmp" )
.GetExpanded( 64,32 );

Grass::Grass( const Vec2& pos )
	:
	pos( pos ),
	dtOffset( Random::RangeF( 0.2f,1.6f ) )
{
}

void Grass::Update( float dt )
{
	a.Update( dt * dtOffset );
}

void Grass::Draw( Graphics& gfx ) const
{
	a.Draw( Vei2( pos ),gfx );
}

void Grass::Move( const Vec2& amount )
{
	pos += amount;
}
