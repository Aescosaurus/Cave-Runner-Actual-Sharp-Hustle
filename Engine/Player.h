#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Platform.h"
#include "Anim.h"
#include "DashHandler.h"

class Player
{
public:
	Player( const Vei2& pos );

	void Update( const Keyboard& kbd,float dt );
	void Update2( const Keyboard& kbd,float dt );
	void Draw( Graphics& gfx ) const;

	// Call once for everything you want to collide with.
	bool CheckHit( const Rect& rect );
	// Call with a vector of items to collide with.
	template<typename T>
	bool CheckHits( const std::vector<T>& items )
	{
		bool hasHit = false;

		for( const T& item : items )
		{
			if( CheckHit( item.GetRect() ) ) hasHit = true;
		}

		return hasHit;
	}
	void Reset();

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
	bool IsJumping();
	Rect GetDashHitbox() const;
	bool DashIsActive() const;
private:
	void Land();
	void Fall();

	bool HitTestTop( const Rect& rect ) const;
	bool HitTestBot( const Rect& rect ) const;
	bool HitTestLeft( const Rect& rect ) const;
	bool HitTestRight( const Rect& rect ) const;
private:
	Vec2 pos;
	const Vec2 posOrig;
	static constexpr int size = 32;
	Rect hitbox = { pos,float( size / 2 ),float( size / 2 ) };
	// For hit test math.
	static constexpr int offset = size / 2;

	const Surface falling = Surface( "Images/Faller.bmp" )
		.GetExpanded( 32,32 );
	const Surface sheet = Surface( "Images/Runner.bmp" )
		.GetExpanded( 64,32 );
	Anim running = Anim( 0,0,32,32,2,sheet,0.12f );

	float vel = 0.0f;
	static constexpr float speed = 50.0f;
	static constexpr float maxSpeed = speed * 2.5f;
	static constexpr float slowdownFactor = 0.96f;

	static constexpr float gravAcc = 20.9f;
	float grav = 0.0f;
	static constexpr int jumpPower = 525;
	bool jumping = false;
	bool canJump = false;
	bool hasJumped = false;

	static constexpr int dashDist = 32 * 2;
	static constexpr float dashCooldown = 0.75f;
	float dashTimer = 0.0f;
};