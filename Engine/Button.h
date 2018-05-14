#pragma once

#include "Vec2.h"
#include <string>
#include "Mouse.h"
#include "Graphics.h"
#include "Rect.h"
#include "Font.h"
#include "Sound.h"

class Button
{
public:
	Button( const Vei2& pos,const Vei2& size,
		std::string msg,Color c1,Color c2,const Font& f );

	void Update( const Mouse& ms );
	void Draw( Graphics& gfx ) const;

	bool IsPressed() const;
protected:
	const Vei2 pos;
	const RectI hitbox;
	const std::string message;
	bool highlighted = false;
	bool canClick = false;
	bool pressed = false;
	const Color c1;
	const Color c2;
	const Font myFont;
	static Sound clickNoise;
};

class ImageButton
{
public:
	ImageButton( const Vei2& pos,const Vei2& size,
		const Surface& drawImg,Color c1,Color c2 );

	void Update( const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	bool IsPressed() const;
private:
	const Vei2 pos;
	const RectI hitbox;
	const Surface& myImg;
	const Color c1;
	const Color c2;
	bool highlighted = false;
	bool canClick = false;
	bool pressed = false;
};