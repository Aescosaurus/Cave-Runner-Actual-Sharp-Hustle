#include "Button.h"
#include "SpriteEffect.h"

Button::Button( const Vei2& pos,const Vei2& size,
	std::string msg,Color c1,Color c2,const Font& f )
	:
	pos( pos ),
	hitbox( pos,size.x,size.y ),
	message( msg ),
	c1( c1 ),
	c2( c2 ),
	myFont( f )
{
}

void Button::Update( const Mouse& ms )
{
	highlighted = hitbox.ContainsPoint( ms.GetPos() );

	if( ms.LeftIsPressed() && highlighted && canClick )
	{
		pressed = true;
	}
	else pressed = false;

	if( !ms.LeftIsPressed() ) canClick = true;
	else canClick = false;
}

void Button::Draw( Graphics& gfx ) const
{
	if( highlighted )
	{
		gfx.DrawRectDim( hitbox.left,hitbox.top,
			hitbox.right,hitbox.bottom,
			c2 );
	}
	else
	{
		gfx.DrawRectDim( hitbox.left,hitbox.top,
			hitbox.right,hitbox.bottom,
			c1 );
	}

	myFont.DrawText( message,pos + Vei2( 5,10 ),
		Colors::White,gfx );
}

bool Button::IsPressed() const
{
	return pressed;
}

ImageButton::ImageButton( const Vei2& pos,const Vei2& size,
	const Surface& drawImg,Color c1,Color c2 )
	:
	pos( pos ),
	hitbox( pos,size.x,size.y ),
	c1( c1 ),
	c2( c2 ),
	myImg( drawImg )
{
}

void ImageButton::Update( const Mouse& mouse )
{
	highlighted = hitbox.ContainsPoint( mouse.GetPos() );

	if( mouse.LeftIsPressed() && highlighted && canClick )
	{
		pressed = true;
	}
	else pressed = false;

	if( !mouse.LeftIsPressed() ) canClick = true;
	else canClick = false;
}

void ImageButton::Draw( Graphics& gfx ) const
{
	if( highlighted )
	{
		gfx.DrawRectDim( hitbox.left,hitbox.top,
			hitbox.right,hitbox.bottom,
			c2 );
	}
	else
	{
		gfx.DrawRectDim( hitbox.left,hitbox.top,
			hitbox.right,hitbox.bottom,
			c1 );
	}

	gfx.DrawSprite( pos.x + 9,pos.y + 9,myImg,
		SpriteEffect::Chroma( Colors::Magenta ) );
}

bool ImageButton::IsPressed() const
{
	return pressed;
}
