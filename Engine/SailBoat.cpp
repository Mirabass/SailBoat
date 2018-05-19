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

Vec2 SailBoat::getMastPosition() const
{
	return mastPosition;
}

float SailBoat::getBearing() const
{
	return bearing;
}

void SailBoat::tiltRudder(const int direction, const float dt)
{
	rudder.changeAngle(float(direction), dt);
}


void SailBoat::Update(const float dt, Board& brd, Wind& wind)
{
	bearing += speedOfTurning * dt * rudder.getAngle();
	position.x += speedToWater * dt * sin((bearing)*float(M_PI)/180.0f);
	position.y += speedToWater * dt * cos((bearing-180)*float(M_PI)/180.0f);
	float WindBearing = wind.getBearing();
	windIndicator.setWIangle(bearing - WindBearing);
	brd.setCompassBearing(bearing);
}

void SailBoat::Draw(Graphics& gfx) const
{
	hull.Draw(gfx);
	SpriteCodex::DrawMast(Vec2(mastPosition.x-26,mastPosition.y-8), gfx);
	windIndicator.Draw(gfx, Vec2(mastPosition.x-1,mastPosition.y));
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
	int rudderWidth = 4;
	float rudderLength = 20.0f;
	Vec2 rudderCentre = { float(playerBoatLocationX) + float(Hull::hullWidth) / 2,float(playerBoatLocationY + Hull::hullHeight) };
	Vec2 vecOfRudder = { 0,rudderLength };
	vecOfRudder.Rotate(-rudderAngle);
	Vec2 rudderEnd = rudderCentre + vecOfRudder;
	gfx.DrawAbscissa(rudderCentre, rudderEnd, rudderWidth, rudderColor);
}

void SailBoat::WindIndicator::setWIangle(const float direction)
{
	WIangle = direction;
}

void SailBoat::WindIndicator::Draw(Graphics & gfx, Vec2 windIndicatorPosition) const
{
	int WIwidth = 3;
	Vec2 center = { 0,0 };
	Vec2 TipPoint = { 0,-26 };
	Vec2 leftFrontPoint = { -3,-18 };
	Vec2 rightFrontPoint = { +3,-18 };
	Vec2 backPoint = { 0,26 };
	Vec2 leftBackPoint = { -3,34 };
	Vec2 rightBackPoint = { +3,34 };

	TipPoint.Rotate(WIangle);
	leftFrontPoint.Rotate(WIangle);
	rightFrontPoint.Rotate(WIangle);
	backPoint.Rotate(WIangle);
	leftBackPoint.Rotate(WIangle);
	rightBackPoint.Rotate(WIangle);

	center += windIndicatorPosition;
	TipPoint += windIndicatorPosition;
	leftFrontPoint += windIndicatorPosition;
	rightFrontPoint += windIndicatorPosition;
	backPoint += windIndicatorPosition;
	leftBackPoint += windIndicatorPosition;
	rightBackPoint += windIndicatorPosition;

	gfx.DrawAbscissa(TipPoint, leftFrontPoint, WIwidth, windIndicatorColor);
	gfx.DrawAbscissa(TipPoint, rightFrontPoint, WIwidth, windIndicatorColor);
	gfx.DrawAbscissa(TipPoint, backPoint, 2, windIndicatorColor);
	gfx.DrawAbscissa(backPoint, leftBackPoint, WIwidth, windIndicatorColor);
	gfx.DrawAbscissa(backPoint, rightBackPoint, WIwidth, windIndicatorColor);
}
