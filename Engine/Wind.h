#pragma once
#include "RectF.h"
#include "Vec2.h"

class Wind
{
public:
	Wind() = default;
	Wind(float sectorWidth, Vec2& sectorPosition, Vec2& windSpeedVector);
	~Wind();
public:
	void setSector(Vec2& sectorPos, float secWidth);
	void setSpeedVector(Vec2& speedVector);
	Vec2 getSpeedVector() const;
	bool IsInSector(const Vec2 Position);
	float getBearing() const;
private:
	float sectorWidth;
	Vec2 sectorPosition;
	RectF sector;
	Vec2 windSpeedVector;
};

