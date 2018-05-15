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

	compass.Draw(gfx);
}

Vec2 Board::getTLscreenPos() const
{
	return topLeftPlayScreen;
}

Vec2 Board::getBRscreenPos() const
{
	return bottomRightPlayScreen;
}

void Board::Compass::setCompassBearing(const float bearing)
{
	compassBearing = bearing;
}

void Board::Compass::Draw(Graphics & gfx) const
{

}
