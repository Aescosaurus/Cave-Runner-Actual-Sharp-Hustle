#include "Player.h"
#include "SpriteEffect.h"

Player::Player( const Vei2& pos )
	:
	pos( Vec2( pos ) ),
	posOrig( pos )
{
}

void Player::Update( const Keyboard& kbd,float dt )
{
	if( kbd.KeyIsPressed( 'A' ) )
	{
		vel -= speed;
	}
	else if( kbd.KeyIsPressed( 'D' ) )
	{
		vel += speed;
	}
	else if( abs( vel ) < 0.3 ) vel = 0.0;

	if( vel > maxSpeed ) vel = maxSpeed;
	if( vel < -maxSpeed ) vel = -maxSpeed;

	pos.x += vel * dt;

	vel *= slowdownFactor;

	grav += gravAcc;
	pos.y += grav * dt;

	if( kbd.KeyIsPressed( 'W' ) && canJump )
	{
		jumping = true;
		canJump = false;
	}

	if( jumping )
	{
		pos.y -= float( jumpPower ) * dt;
	}
}

void Player::Update2( const Keyboard& kbd,float dt )
{
	running.Update( dt );

	grav += gravAcc;
	pos.y += grav * dt;

	if( kbd.KeyIsPressed( 'W' ) && canJump && dt > 0.0f )
	{
		jumping = true;
		canJump = false;
		hasJumped = true;
	}

	if( jumping )
	{
		pos.y -= float( jumpPower ) * dt;
	}

	// if( grav > jumpPower )
	// {
	// 	jumping = false;
	// }

	if( dashTimer > dashCooldown )
	{
		if( kbd.KeyIsPressed( 'D' ) && dt > 0.0f )
		{
			dashTimer = 0.0f;

			DashHandler::AddDash( pos );

			pos.x += float( dashDist );
		}
	}
	else dashTimer += dt;

	DashHandler::Update( dt );

	hitbox.MoveTo( pos + float( size / 4 ) );
}

void Player::Draw( Graphics& gfx ) const
{
	// gfx.DrawRect( int( pos.x ),int( pos.y ),
	// 	size,size,Colors::Red );

	DashHandler::Draw( gfx );
	
	if( grav < float( jumpPower ) * 1.2f )
	{
		running.Draw( Vei2( pos ),gfx );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),
			falling,SpriteEffect
			::Chroma( Colors::Magenta ) );
	}

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

bool Player::CheckHit( const Rect& rect )
{
	bool hasHit = false;
	if( HitTestBot( rect ) )
	{
		pos.y = rect.top - size;
		Land();
		hasHit = true;
	}
	if( HitTestTop( rect ) )
	{
		pos.y = rect.bottom;
		Fall();
		hasHit = true;
	}

	if( HitTestLeft( rect ) )
	{
		pos.x = rect.right;
		hasHit = true;
	}

	if( HitTestRight( rect ) )
	{
		pos.x = rect.left - size;
		hasHit = true;
	}

	return hasHit;
}

void Player::Reset()
{
	pos = posOrig;
	jumping = false;
	grav = 0.0f;
}

const Vec2& Player::GetPos() const
{
	return pos;
}

const Rect& Player::GetRect() const
{
	return hitbox;
}

bool Player::IsJumping()
{
	if( hasJumped )
	{
		hasJumped = false;
		return( true );
	}
	else
	{
		return false;
	}
}

Rect Player::GetDashHitbox() const
{
	return( DashHandler::GetRect() );
}

bool Player::DashIsActive() const
{
	return DashHandler::DashActive();
}

void Player::Land()
{
	grav = 0.0f;
	jumping = false;
	canJump = true;
}

void Player::Fall()
{
	jumping = false;
	grav = 0.0f;
}

bool Player::HitTestTop( const Rect& rect ) const
{
	if( pos.x + offset < rect.right &&
		pos.x + size - offset > rect.left &&
		pos.y < rect.bottom &&
		pos.y + offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestBot( const Rect& rect ) const
{
	if( pos.x + offset < rect.right &&
		pos.x + size - offset > rect.left &&
		pos.y + size - offset < rect.bottom &&
		pos.y + size > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestLeft( const Rect& rect ) const
{
	if( pos.x < rect.right &&
		pos.x + offset > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + size - offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestRight( const Rect& rect ) const
{
	if( pos.x + size - offset < rect.right &&
		pos.x + size > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + size - offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}
