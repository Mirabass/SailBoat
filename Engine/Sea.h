#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>
#include "SailBoat.h"

class Sea
{
public:
	Sea();
	~Sea();

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
private:
	static constexpr int seaWidth = 10000;
	static constexpr int seaHeight = 10000;
	static constexpr Color seaColor = { 0,0,102 };
	std::random_device rd;
	const int nBubbles;
	Bubble* bubbles = nullptr;
};

