#pragma once

#include "Surface.h"
#include "Vec2.h"
#include "Codex.h"
#include "Graphics.h"

class Dash
{
public:
	Dash( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	const Rect& GetRect() const;
	bool IsActive() const;
private:
	static constexpr float lifetime = 0.15f;
	float timer = 0.0f;
	Vei2 pos;
	static const Surface surf;
	Rect hitbox;
};

class DashHandler
{
public:
	static void Update( float dt );
	static void Draw( Graphics& gfx );

	static void AddDash( const Vec2& pos );

	static Rect GetRect();
	static bool DashActive();
private:
	static Dash curDash;
};