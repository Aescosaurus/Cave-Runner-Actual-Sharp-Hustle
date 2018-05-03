#pragma once

#include <vector>
#include "Vec2.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Surface.h"
#include "Button.h"
#include "Font.h"

class LevelEditor
{
public:
	LevelEditor( const Font& ref );
	void Update( const Mouse& mouse,int& nLevels );
	void Draw( Graphics& gfx ) const;
private:
	void Save( int& nLevels );
	void Load();
private:
	static constexpr int width = 30;
	static constexpr int height = 10;
	static constexpr int startX = 0;
	static constexpr int startY = 0;
	const Surface enemy = "Images/Enemy.bmp";
	const std::vector<Surface> imgs =
	{
		Surface( "Images/Block1.bmp" ).GetExpanded( 32,32 ),
		Surface( "Images/Spike1.bmp" ).GetExpanded( 32,32 ),
		Surface( enemy,RectI( { 0,0 },16,16 ) ).GetExpanded( 32,32 )
	};
	Font myFont;
	std::vector<int> tiles;
	int brush = 0;
	Vei2 curMsPos = { 0,0 };

	const Surface blankSurf = Surface( 32,32 );
	ImageButton blank = ImageButton( { 20,360 },{ 50,50 },
		blankSurf,Colors::DarkGray,Colors::LightGray );
	ImageButton block = ImageButton( { 80,360 },{ 50,50 },
		imgs[0],Colors::DarkGray,Colors::LightGray );
	ImageButton spike = ImageButton( { 140,360 },{ 50,50 },
		imgs[1],Colors::DarkGray,Colors::LightGray );
	ImageButton enemyb = ImageButton( { 200,360 },{ 50,50 },
		imgs[2],Colors::DarkGray,Colors::LightGray );
	Button save = Button( { 410,360 },{ 135,55 },"Save",
		Colors::DarkGray,Colors::LightGray,myFont );
	Button load = Button( { 555,360 },{ 135,55 },"NOPE",
		Colors::DarkGray,Colors::LightGray,myFont );
};