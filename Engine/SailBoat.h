#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Board.h"
#include "Colors.h"
#include "Wind.h"

class SailBoat
{
public:
	SailBoat() = default;
	SailBoat(const Vec2& pos);
	~SailBoat();
	Vec2 getPosition() const;
	Vec2 getLocation() const;
	Vec2 getMastPosition() const;
	float getBearing() const;
	void tiltRudder(const int direction, const float dt);
	void ReleaseMainSheet(Wind locWind, const float dt);
	void TightMainSheet(Wind locWind, const float dt);
	void Update(const float dt, Board& brd, Wind& wind);
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
		Color rudderColor = Colors::Green;
		float speedOfTilting = 100.0f;
		float rudderAngle;
	};
	class WindIndicator
	{
	public:
		void setWIangle(const float direction);
		void Draw(Graphics& gfx, Vec2 MastPosition) const;
	private:
		Color windIndicatorColor = Colors::Red;
		float WIangle;
	};
	class Sails
	{
	public:
		Sails(float mainSailAngle);
		void Draw(Graphics& gfx) const;
		void setWindToBoat(Vec2 boatVelocity, Wind locWind);
		void ReleaseMainSheat(const float dt);
		void TightMainSheat(const float dt);
	public:
		class MainSail
		{
		public:
			MainSail(float mainSailAngle);
			void Draw(Graphics& gfx) const;
			void TurnBoom(const float direction, const float dt);
			float getMainSailAngle() const;
		private:
			Color mainSailColor = Colors::Black;
			const float mainSailThickness = 2.0f;
			Color boomColor = Colors::Black;
			const float boomThickness = 6.0f;
			const float boomLength = 100.0f;
			Color mainSheetColor = Colors::Magenta;
			const float mainSheetThickness = 3.0f;
			float speedOfControlling = 40.0f;
			float mainSailAngle = 180.0f;
		};
		class Jib
		{
		public:
		private:
			Color jibColor = Colors::LightGray;
		};
	private:
		float windToBoatAngle = 0.0f;
		MainSail mainSail;
		Jib jib;
	};
public:
	static constexpr int playerBoatLocationX = int(Board::playScreenWidth/2) - int(Hull::hullWidth/2) + int(Board::borderWidth);
	static constexpr int playerBoatLocationY = 259 + int(Hull::hullHeight/2);
	static constexpr int mastPositionX = playerBoatLocationX + Hull::hullWidth / 2;
	static constexpr int mastPositionY = playerBoatLocationY + int(Hull::hullHeight / 2.6);

private:
	Hull hull;
	Rudder rudder;
	Vec2 position;
	WindIndicator windIndicator;
	Vec2 mastPosition = { mastPositionX, mastPositionY };
	Sails sails;
	Vec2 boatVelocityToWater = { 0.0f, -100.0f };
	float speedOfTurning = boatVelocityToWater.GetLength() * 0.01f;
};

