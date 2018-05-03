#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Spike
{
public:
	Spike( const Vec2& pos );

	void Update( const Vec2& plPos,float dt );
	void Draw( Graphics& gfx ) const;

	static void LoadSurfs();
	void Move( const Vec2& amount );
	void OnPlayerJump( float dt );
	void Destroy();

	const Rect& GetRect() const;
	bool IsDead() const;
private:
	static constexpr int size = 32;
	int mySurf;
	static constexpr int nSurfs = 2;
	static std::vector<Surface> surfs;
	Vec2 pos;
	Rect hitbox;
	bool dead = false;

	static constexpr float gravAcc = 0.3f;
	float grav = 0.0f;
	bool falling = false;
};