#include "Wind.h"


Wind::Wind(float sectorWidth, Vec2 sectorPosition, Vec2 windSpeedVector)
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
