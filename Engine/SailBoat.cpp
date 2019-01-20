#include "SailBoat.h"
#define _USE_MATH_DEFINES
#include <math.h>


SailBoat::SailBoat(const Vec2 & pos, const Vec2& velocity, const float& startingMainSailAngle)
	:
	hull(Vec2(float(playerBoatLocationX), float(playerBoatLocationY)), 0.0f),
	rudder(0.0f),
	position(pos),
	sails(-startingMainSailAngle),
	boatVelocityToWater(velocity)
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
	return boatVelocityToWater.GetAngle();
}

void SailBoat::tiltRudder(const int direction, const float dt)
{
	rudder.changeAngle(float(direction), dt);
}

void SailBoat::ReleaseMainSheet(Wind locWind, const float dt)
{
	sails.ReleaseMainSheat(apparentWind,windToBoatAngle, dt);
}


void SailBoat::TightMainSheet(Wind locWind, const float dt)
{
	sails.TightMainSheat(apparentWind, windToBoatAngle,dt);
}

void SailBoat::Update(const float dt, Board& brd, Wind& wind)
{
	boatVelocityToWater.Rotate(speedOfTurning * dt * rudder.getAngle());
	setWindToBoat(wind);
	sails.TackOrJibe(apparentWind,windToBoatAngle ,dt);
	float bearing = boatVelocityToWater.GetAngle();
	float speedToWater = boatVelocityToWater.GetLength();
	position.x += speedToWater * dt * sin((bearing)*float(M_PI)/180.0f);
	position.y += speedToWater * dt * cos((bearing-180)*float(M_PI)/180.0f);
	float appWindBearing = apparentWind.GetAngle();
	windIndicator.setWIangle(bearing - appWindBearing);
	brd.setCompassBearing(bearing);
}

void SailBoat::Draw(Graphics& gfx) const
{
	hull.Draw(gfx);
	SpriteCodex::DrawMast(Vec2(mastPosition.x-26,mastPosition.y-8), gfx);
	rudder.Draw(gfx);
	sails.Draw(gfx);
	windIndicator.Draw(gfx, Vec2(mastPosition.x - 1, mastPosition.y));
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

	TipPoint.Rotate(180 - WIangle);
	leftFrontPoint.Rotate(180 - WIangle);
	rightFrontPoint.Rotate(180 - WIangle);
	backPoint.Rotate(180 - WIangle);
	leftBackPoint.Rotate(180 - WIangle);
	rightBackPoint.Rotate(180 - WIangle);

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

SailBoat::Sails::Sails(float mainSailAngle)
	:
	mainSail(mainSailAngle)
{
}

void SailBoat::Sails::Draw(Graphics & gfx) const
{
	mainSail.Draw(gfx);
}

void SailBoat::setWindToBoat(Wind locWind)
{
	Vec2 trueWind = locWind.getSpeedVector();
	drivingWind = Vec2(0,0) - boatVelocityToWater;
	apparentWind = trueWind + drivingWind;
	windToBoatAngle = apparentWind.GetAngle() - boatVelocityToWater.GetAngle();
	if (windToBoatAngle < 0)
	{
		windToBoatAngle = 360 - windToBoatAngle;
	}
}

void SailBoat::Sails::TightMainSheat(Vec2 appWind, const float windTBA, const float dt)
{
	if (mainSail.CheckWindToMainSail(windTBA))
	{
		if (windTBA < 180)
		{
			if (mainSail.getMainSailAngle() > 5)
			{
				mainSail.TurnBoom(-1, dt);
			}
		}
		else
		{
			if (mainSail.getMainSailAngle() < -5)
			{
				mainSail.TurnBoom(+1, dt);
			}
		}
	}
}

void SailBoat::Sails::TackOrJibe(Vec2 appWind, const float windTBA, const float dt)
{
	if (mainSail.underControl)
	{
		mainSail.underControl = mainSail.CheckWindToMainSail(windTBA);
	}
	if (!mainSail.underControl || tacking || jibbing)
	{
		if (mainSail.underControlFirstly)
		{
			mainSail.setCriticAngle();
		}	
		if (windTBA > 5 || windTBA < 355)
		{
			tacking = true;
			if (windTBA < 180)
			{
				mainSail.Tack(appWind, +1, dt);
			}
			else
			{
				mainSail.Tack(appWind, -1, dt);
			}
		}
		else
		{
			jibbing = true;
			if (windTBA < 180)
			{
				mainSail.Jibe(appWind, +1, dt);
			}
			else
			{
				mainSail.Jibe(appWind, -1, dt);
			}
		}
		if (mainSail.CheckFinishedTackOrJibe()) // nekde je t problem
		{
			tacking = false;
			jibbing = false;
			mainSail.underControl = true;
			mainSail.underControlFirstly = true;
		}
	}
}

void SailBoat::Sails::ReleaseMainSheat(Vec2 appWind, const float windTBA, const float dt)
{
	if (mainSail.CheckWindToMainSail(windTBA))
	{
		if (windTBA < 180)
		{
			if (mainSail.getMainSailAngle() < 85)
			{
				mainSail.TurnBoom(+1, dt);
			}
		}
		else
		{
			if (mainSail.getMainSailAngle() > -85)
			{
				mainSail.TurnBoom(-1, dt);
			}
		}
	}
}

SailBoat::Sails::MainSail::MainSail(float mainSailAngle)
	:
	mainSailAngle(mainSailAngle)
{
	
}

void SailBoat::Sails::MainSail::Draw(Graphics & gfx) const
{
	float sailRadius = 200;
	// prepocet podle bearing uhlu:
	float b_angle = 180 - mainSailAngle;

	// boom:
	Vec2 boomCenter = Vec2(mastPositionX, mastPositionY);
	Vec2 vecOfBoom = { 0,boomLength };
	vecOfBoom.Rotate(b_angle);
	Vec2 boomEnd = boomCenter - vecOfBoom;
	gfx.DrawAbscissa(boomCenter, boomEnd, boomThickness, boomColor);

	// mainSheet:
	Vec2 sheetCenter = Vec2(mastPositionX, playerBoatLocationY + Hull::hullHeight);
	gfx.DrawAbscissa(sheetCenter, boomEnd, mainSheetThickness, mainSheetColor);

	//gfx.DrawCircleCurve(Vec2(mastPositionX,mastPositionY), mainSailLength, sailRadius, b_angle, mainSailThickness, mainSailColor);
}

void SailBoat::Sails::MainSail::TurnBoom(const float direction, const float dt)
{
	mainSailAngle += direction * speedOfControlling * dt;
}

float SailBoat::Sails::MainSail::getMainSailAngle() const
{
	return mainSailAngle;
}

bool SailBoat::Sails::MainSail::CheckWindToMainSail(const float windToBoat)
{
	if (windToBoat <= 180 && mainSailAngle > 0 || windToBoat >= 180 && mainSailAngle < 0)
	{
		return true;
	}
	return false;
}

void SailBoat::Sails::MainSail::Tack(Vec2 appWind, const float direction, const float dt)
{
	speedOfControlling = basicSpeedOfControlling + appWind.GetLength() * speedOfTack;
	TurnBoom(direction, dt);
	speedOfControlling = basicSpeedOfControlling;
}

void SailBoat::Sails::MainSail::Jibe(Vec2 appWind, const float direction, const float dt)
{
	speedOfControlling = basicSpeedOfControlling + appWind.GetLength() * speedOfJibe;
	TurnBoom(direction, dt);
	speedOfControlling = basicSpeedOfControlling;
}

void SailBoat::Sails::MainSail::setCriticAngle()
{
	underControlFirstly = false;
	angleAtCriticPoint = mainSailAngle;
}

bool SailBoat::Sails::MainSail::CheckFinishedTackOrJibe()
{
	return mainSailAngle >= - angleAtCriticPoint - 1 && mainSailAngle <= -angleAtCriticPoint + 1;
}
