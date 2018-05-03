#include "Enemy.h"

const Surface Enemy
::spriteSheet = Surface( "Images/Enemy.bmp" )
.GetExpanded( size * 4,size * 2 );

Enemy::Enemy( const Vec2& pos )
	:
	pos( pos ),
	hitbox( pos,float( size ),float( size ) )
{
}

void Enemy::Update( float dt )
{
	pos.x -= speed * dt;

	grav += gravAcc;
	pos.y += grav;

	hitbox.MoveTo( pos );

	move.Update( dt );
}

void Enemy::Draw( Graphics& gfx ) const
{
	move.Draw( Vei2( pos ) - Vei2( size / 8,size ),gfx );

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics
		::GetScreenRect() ) && pos.x > 0.0f )
	{
		// gfx.DrawRect( int( pos.x ),int( pos.y ),
		// 	size,size,Colors::Red );
		gfx.DrawHitbox( hitbox );
	}
#endif
}

void Enemy::Move( const Vec2& amount )
{
	pos += amount;
}

void Enemy::CheckHits( const std::vector<Platform>& plats )
{
	for( const auto& plat : plats )
	{
		const Rect& rect = plat.GetRect();

		if( HitTestBot( rect ) )
		{
			pos.y = rect.top - size;
			Land();
		}
		if( HitTestTop( rect ) )
		{
			pos.y = rect.bottom;
			Fall();
		}

		if( HitTestLeft( rect ) )
		{
			pos.x = rect.right;
		}

		if( HitTestRight( rect ) )
		{
			pos.x = rect.left - size;
		}
	}
}

void Enemy::Destroy()
{
	dead = true;
	// Spawn particles and stuff here.
}

bool Enemy::HitTestTop( const Rect& rect ) const
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

bool Enemy::HitTestBot( const Rect& rect ) const
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

bool Enemy::HitTestLeft( const Rect& rect ) const
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

bool Enemy::HitTestRight( const Rect& rect ) const
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

const Rect& Enemy::GetRect() const
{
	return( hitbox );
}

bool Enemy::IsDead() const
{
	return( pos.x + float( size ) < 0.0f || dead );
}

void Enemy::Land()
{
	grav = 0.0f;
}

void Enemy::Fall()
{
	// Do nothing haha.
}
