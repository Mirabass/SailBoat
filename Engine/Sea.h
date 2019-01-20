#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>
#include "SailBoat.h"
#include "Wind.h"

class Sea
{
public:
	Sea(const int& seaWidth, const int& seaHeight);
	~Sea();

	Wind getLocalWind(const Vec2 Position) const;
	void Draw(SailBoat& playerBoat, Board& brd,Graphics& gfx) const;

public:
	class Bubble
	{
	public:
		void setPosition(const Vec2& pos);
		void setSize(const int s);
		Vec2 getPosition() const;
		void Draw(SailBoat& playerBoat, Graphics& gfx) const;
	private:
		Vec2 position;
		int size;
	};
public:
	int seaWidth;
	int seaHeight;
private:
	static constexpr int sectorWidth = 100;
	const int nSectors = seaWidth / sectorWidth * seaHeight / sectorWidth;
	static constexpr Color seaColor = { 0,0,102 };
	std::random_device rd;
	const int nBubbles;
	Bubble* bubbles = nullptr;
	Wind* wind = nullptr;
};

