#include "Vec2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

Vec2::Vec2( float x_in,float y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vec2 Vec2::operator+( const Vec2& rhs ) const
{
	return Vec2( x + rhs.x,y + rhs.y );
}

Vec2& Vec2::operator+=( const Vec2& rhs )
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*( float rhs ) const
{
	return Vec2( x * rhs,y * rhs );
}

Vec2& Vec2::operator*=( float rhs )
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-( const Vec2& rhs ) const
{
	return Vec2( x - rhs.x,y - rhs.y );
}

Vec2& Vec2::operator-=( const Vec2& rhs )
{
	return *this = *this - rhs;
}

float Vec2::GetLength() const
{
	return std::sqrt( GetLengthSq() );
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

float Vec2::GetAngle() const
{
	float result;
	float x_abs, y_abs;
	x_abs = abs(x);
	y_abs = abs(y);
	if (x>=0 && y>=0)
	{
		result = 90.0f + atan(y_abs / x_abs)*180.0f / float(M_PI);
	}
	else if (x<0&&y>=0)
	{
		result = 270.0f - atan(y_abs / x_abs)*180.0f / float(M_PI);
	}
	else if (x<0&&y<0)
	{
		result = 270.0f + atan(y_abs / x_abs)*180.0f / float(M_PI);
	}
	else
	{
		result = 90.0f - atan(y_abs / x_abs)*180.0f / float(M_PI);
	}

	return result;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	if( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

Vec2 & Vec2::Rotate(const float angle)
{
	Vec2 rotated;
	rotated.x = this->x * cos(angle*float(M_PI) / 180.0f) - this->y * sin(angle*float(M_PI) / 180.0f);
	rotated.y = this->x * sin(angle*float(M_PI) / 180.0f) + this->y * cos(angle*float(M_PI) / 180.0f);
	*this = rotated;
	return *this;
}
