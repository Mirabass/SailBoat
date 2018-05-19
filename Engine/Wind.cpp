#include "Wind.h"
#define _USE_MATH_DEFINES
#include <math.h>


Wind::Wind(float sectorWidth, Vec2& sectorPosition, Vec2& windSpeedVector)
	:
	sectorWidth(sectorWidth),
	sectorPosition(sectorPosition),
	windSpeedVector(windSpeedVector)
{
	Vec2 sectorTLPosition = { sectorPosition.x * sectorWidth,sectorPosition.y * sectorWidth };
	sector = RectF(sectorTLPosition, sectorWidth, sectorWidth);
 }


Wind::~Wind()
{
}

void Wind::setSector(Vec2& sectorPos,float secWidth)
{
	sector = { sectorPos, secWidth,secWidth };
}

void Wind::setSpeedVector(Vec2& speedVector)
{
	windSpeedVector = speedVector;
}

bool Wind::IsInSector(const Vec2 Position)
{
	return Position.x >= sector.left && Position.y >= sector.top && Position.x <= sector.right && Position.y <= sector.bottom;
}

float Wind::getBearing() const
{
	return float(atan(windSpeedVector.x/windSpeedVector.y)*180.0f/M_PI);
}
