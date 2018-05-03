#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include "Surface.h"
#include <vector>
#include "Codex.h"

class Platform
{
public:
	Platform( const Vei2& pos );

	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& moveAmount );
	static void LoadSprites();

	const Rect& GetRect() const;
	bool WillDelete() const;
private:
	Vec2 pos;
	static constexpr int nSprites = 2;
	static std::vector<Surface> sprites;
	int mySprite;
	static constexpr int size = 32;
	Rect hitbox;
};