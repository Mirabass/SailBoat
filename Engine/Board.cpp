#include "Board.h"
#include "RectF.h"
#include "SailBoat.h"

Board::Board()
{
}


Board::~Board()
{
}

void Board::Draw(Graphics& gfx) const
{
	RectF topBorder = {0,playScreenWidth+borderWidth,0,borderWidth };
	RectF bottomBorder = { 0,playScreenWidth + borderWidth, playScreenHeight + borderWidth,float(Graphics::ScreenHeight )};
	RectF leftBorder = { 0,borderWidth,0,float(Graphics::ScreenHeight )};
	RectF tools = { playScreenWidth + borderWidth,float(Graphics::ScreenWidth),0,float(Graphics::ScreenHeight) };
	gfx.DrawRect(topBorder, oldPaper);
	gfx.DrawRect(bottomBorder, oldPaper);
	gfx.DrawRect(leftBorder, oldPaper);
	gfx.DrawRect(tools, oldPaper);

	compass.Draw(gfx, topLeftToolsScreen);
}

Vec2 Board::getTLscreenPos() const
{
	return topLeftPlayScreen;
}

Vec2 Board::getBRscreenPos() const
{
	return bottomRightPlayScreen;
}

void Board::setCompassBearing(const float TrueBearing)
{
	compass.setCompassBearing(-TrueBearing);
}

void Board::Compass::setCompassBearing(const float CompassNorth)
{
	compassNorth = CompassNorth;
}

void Board::Compass::Draw(Graphics & gfx, Vec2 topLeftToolsScreen) const
{
	Vec2 CompassPos = topLeftToolsScreen + Vec2((Graphics::ScreenWidth - topLeftToolsScreen.x)/2,110);
	float blackStripeRadiusTop = 92.0f;
	float blackStripeRadiusBottom = 74.0f;
	gfx.DrawCircle(CompassPos.x, CompassPos.y, 98, Colors::Gray);
	gfx.DrawCircle(CompassPos.x, CompassPos.y, blackStripeRadiusTop, Colors::Black);
	gfx.DrawCircle(CompassPos.x, CompassPos.y, blackStripeRadiusBottom, Colors::Gray);
	gfx.DrawCircle(CompassPos.x, CompassPos.y, 6, Colors::Cyan);
	Vec2 pointerPos = { 0,-(blackStripeRadiusTop + blackStripeRadiusBottom) / 2 };
	pointerPos.Rotate(compassNorth);
	pointerPos = CompassPos + pointerPos;
	gfx.DrawCircle(pointerPos.x, pointerPos.y, (blackStripeRadiusTop - blackStripeRadiusBottom) / 4, Colors::Red);
}
