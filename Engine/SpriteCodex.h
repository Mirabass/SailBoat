#pragma once
#include "Vec2.h"
#include "Graphics.h"

class SpriteCodex
{
public:
	SpriteCodex();
	~SpriteCodex();

	static void DrawBubble(const Vec2& centre, const int size, Graphics& gfx);
	static void DrawCircle(const Vec2& centre, const float radius, Graphics& gfx);
	static void DrawHull(const Vec2& topleft,const float rotation, Graphics& gfx);
	static void DrawRudder(const int hullHeight, const int hullWidth, const int playerBoatLocationX, const int playerBoatLocationY,
		const float rudderAngle, Graphics& gfx);

	
};

