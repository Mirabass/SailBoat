#include "SailBoat.h"
#define _USE_MATH_DEFINES
#include <math.h>


SailBoat::SailBoat(const Vec2 & pos)
	:
	hull(Vec2(float(playerBoatLocationX), float(playerBoatLocationY)), 0.0f),
	rudder(0.0f),
	position(pos)
{

}


SailBoat::~SailBoat()
{
}

Vec2 SailBoat::getPosition() const
{
	return position;
}

Vec2 SailBoat::getLocation() const
{
	return hull.getLocation();
}

float SailBoat::getBearing() const
{
	return bearing;
}

void SailBoat::tiltRudder(const int direction, const float dt)
{
	rudder.changeAngle(float(direction), dt);
}

void SailBoat::Update(const float dt, Board& brd)
{
	bearing += speedOfTurning * dt * rudder.getAngle();
	position.x += speedToWater * dt * sin((bearing)*M_PI/180.0f);
	position.y += speedToWater * dt * cos((bearing-180)*M_PI/180.0f);
	brd.setCompassBearing(bearing);
}

void SailBoat::Draw(Graphics& gfx) const
{
	hull.Draw(gfx);
	rudder.Draw(gfx);
}

SailBoat::Hull::Hull(Vec2 loc, float rot)
	:
	location(loc),
	rotation(rot)
{
}

Vec2 SailBoat::Hull::getLocation() const
{
	return location;
}

void SailBoat::Hull::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawHull(location, rotation, gfx);
}

SailBoat::Rudder::Rudder(float rudderAngle)
	:
	rudderAngle(rudderAngle)
{
}

void SailBoat::Rudder::changeAngle(const float direction, const float dt)
{
	rudderAngle += direction * speedOfTilting * dt;
	
	if (rudderAngle < -75)
	{
		rudderAngle = -75;
	}
	else if (rudderAngle > 75)
	{
		rudderAngle = 75;
	}
}

float SailBoat::Rudder::getAngle() const
{
	return rudderAngle;
}

void SailBoat::Rudder::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawRudder(Hull::hullHeight, Hull::hullWidth, playerBoatLocationX, playerBoatLocationY, rudderAngle, gfx);
}
