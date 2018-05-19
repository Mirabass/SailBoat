#include "Sea.h"
#include "Board.h"
#include <assert.h>

Sea::Sea()
	:
	nBubbles(seaWidth*seaHeight/10000),
	bubbles(new Bubble[nBubbles]),
	wind(new Wind[nSectors])
{
	for (int i = 0; i < nBubbles; i++)
	{
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> xDist(0, seaWidth);
		std::uniform_int_distribution<int> yDist(0, seaHeight);
		std::uniform_int_distribution<int> sizeDist(1, 4);
		bubbles[i].setPosition({ float(xDist(rng)),float(yDist(rng)) });
		bubbles[i].setSize(sizeDist(rng));
	}
	Vec2 eastern = { -10,0 };
	int i = 0;
	for (int sectorX = 0; sectorX < seaWidth / sectorWidth; sectorX++)
	{
		for (int sectorY = 0; sectorY < seaHeight/sectorWidth; sectorY++)
		{
			wind[i++] = Wind(float(sectorWidth), Vec2(float(sectorX),float(sectorY)), eastern);
		}
	}
}


Sea::~Sea()
{
}

Wind Sea::getLocalWind(const Vec2 Position) const
{
	int local = 0;
	do
	{
		if (wind[local].IsInSector(Position))
		{
			return wind[local];
		}
		local++;
	} while (local < nSectors);
	assert(false);
	return wind[0];
}

void Sea::Draw(SailBoat& playerBoat, Board& brd, Graphics & gfx) const
{
	RectF blueRect = { brd.getTLscreenPos(), brd.getBRscreenPos() };
	gfx.DrawRect(blueRect, seaColor);

	for (int i = 0; i < nBubbles; i++)
	{
		bubbles[i].Draw(playerBoat, gfx);
	}
}

void Sea::Bubble::setPosition(const Vec2 & pos)
{
	position = pos;
}

void Sea::Bubble::setSize(const int s)
{
	size = s;
}

Vec2 Sea::Bubble::getPosition() const
{
	return position;
}

void Sea::Bubble::Draw(SailBoat& playerBoat, Graphics & gfx) const
{
	float boatBearing = playerBoat.getBearing();
	Vec2 boatPosition = playerBoat.getPosition();
	Vec2 boatLocation = playerBoat.getLocation();
	Vec2 location = boatLocation - (boatPosition - position).Rotate(-boatBearing);
	if (location.x > 5 && location.y > 5 && location.x < Graphics::ScreenWidth - 5 && location.y < Graphics::ScreenHeight - 5)
	{
		SpriteCodex::DrawBubble(location, size, gfx);
	}		
}
