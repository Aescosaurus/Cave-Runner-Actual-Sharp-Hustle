#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include <vector>
#include "Platform.h"
#include "Anim.h"
#include "Sound.h"

class Enemy
{
public:
	Enemy( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& amount );
	void CheckHits( const std::vector<Platform>& plats );
	void Destroy();

	const Rect& GetRect() const;
	bool IsDead() const;
private:
	void Land();
	void Fall();

	bool HitTestTop( const Rect& rect ) const;
	bool HitTestBot( const Rect& rect ) const;
	bool HitTestLeft( const Rect& rect ) const;
	bool HitTestRight( const Rect& rect ) const;
private:
	static constexpr int size = 32;
	static constexpr int offset = size / 2;
	Vec2 pos;
	Rect hitbox;

	static const Surface spriteSheet;
	Anim move = Anim( 0,0,size * 2,size * 2,2,spriteSheet,0.4f );
	
	static Sound ouch;

	bool dead = false;
	static constexpr float speed = 70.0f;
	static constexpr float gravAcc = 0.15f;
	float grav = 0.0f;
};