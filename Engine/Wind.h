#pragma once
#include "RectF.h"
#include "Vec2.h"

class Wind
{
public:
	Wind() = default;
	Wind(float sectorWidth, Vec2 sectorPosition, Vec2 windSpeedVector);
	~Wind();
public:

private:
	float sectorWidth;
	Vec2 sectorPosition;
	RectF sector;
	Vec2 windSpeedVector;
};
