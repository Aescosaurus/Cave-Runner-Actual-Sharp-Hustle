#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Anim.h"
#include "Graphics.h"

class Grass
{
public:
	Grass( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& amount );
private:
	static const Surface img;
	Anim a = Anim( 0,0,32,32,2,img,0.6f );
	Vec2 pos;
	const float dtOffset;
};