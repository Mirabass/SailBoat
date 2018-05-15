#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Board.h"

class SailBoat
{
public:
	SailBoat() = default;
	SailBoat(const Vec2& pos);
	~SailBoat();
	Vec2 getPosition() const;
	Vec2 getLocation() const;
	float getBearing() const;
	void tiltRudder(const int direction, const float dt);
	void Update(const float dt, Board& brd);
	void Draw(Graphics& gfx) const;

	class Hull
	{
	public:
		Hull(Vec2 loc, float rotation);
		Vec2 getLocation() const;
		void Draw(Graphics& gfx) const;
	public:
		static constexpr int hullWidth = 101;
		static constexpr int hullHeight = 182;
	private:
		Vec2 location;
		float rotation;
	};
	class Rudder
	{
	public:
		Rudder(float rudderAngle);
		void changeAngle(const float direction, const float dt);
		float getAngle() const;
		void Draw(Graphics& gfx) const;
	private:
		float speedOfTilting = 100.0f;
		float rudderAngle;
	};
public:
	static constexpr int playerBoatLocationX = int(Board::playScreenWidth/2) - int(Hull::hullWidth/2);
	static constexpr int playerBoatLocationY = 259 + int(Hull::hullHeight/2);

private:
	Hull hull;
	Rudder rudder;
	Vec2 position;
	float speedToWater = 100.0f;
	float speedOfTurning = speedToWater * 0.01f;
	float bearing = 0.0f;
};

