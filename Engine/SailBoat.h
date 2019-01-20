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
	void setWindToBoat(Wind locWind);
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
		void ReleaseMainSheat(Vec2 appWind, const float windTBA, const float dt);
		void TightMainSheat(Vec2 appWind, const float windTBA, const float dt);
		void TackOrJibe(Vec2 appWind, const float windTBA, const float dt);
		bool tacking = false;
		bool jibbing = false;
	public:
		class MainSail
		{
		public:
			MainSail(float mainSailAngle);
			void Draw(Graphics& gfx) const;
			void TurnBoom(const float direction, const float dt);
			float getMainSailAngle() const;
			bool CheckWindToMainSail(const float windToBoat);
			bool underControl = true;
			bool underControlFirstly = true;
			void Tack(Vec2 appWind, const float direction, const float dt);
			void Jibe(Vec2 appWind, const float direction, const float dt);
			void setCriticAngle();
			bool CheckFinishedTackOrJibe();
		private:
			const float mainSailThickness = 2.0f;
			const float boomThickness = 6.0f;
			const float boomLength = 100.0f;
			const float mainSheetThickness = 3.0f;
			const float basicSpeedOfControlling = 20.0f;
			const float speedOfTack = 0.5;
			const float speedOfJibe = 0.9;
			Color mainSailColor = Colors::Black;
			Color boomColor = Colors::Black;
			Color mainSheetColor = Colors::Magenta;
			float speedOfControlling = basicSpeedOfControlling;
			float mainSailAngle;
			float angleAtCriticPoint = mainSailAngle;
		};
		class Jib
		{
		public:
		private:
			Color jibColor = Colors::LightGray;
		};
	private:
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
	Vec2 boatVelocityToWater = { 0.0f, -40.0f };
	Vec2 drivingWind = { 0.0f,0.0f };
	Vec2 apparentWind = { 0.0f,0.0f };
	float speedOfTurning = boatVelocityToWater.GetLength() * 0.01f;
	float windToBoatAngle = 0;
};

