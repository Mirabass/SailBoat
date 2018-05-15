#pragma once
#include "Colors.h"
#include "Graphics.h"

class Board
{
public:
	Board();
	~Board();
	void Draw(Graphics& gfx) const;
	Vec2 getTLscreenPos() const;
	Vec2 getBRscreenPos() const;
private:
	static constexpr Color oldPaper = { 248,236,194 };
	static constexpr float borderWidth = 5;
public:
	static constexpr float playScreenHeight = float(Graphics::ScreenHeight) - 2 * borderWidth;
	static constexpr float playScreenWidth = (4.0f / 3 * playScreenHeight);
private:
	Vec2 topLeftPlayScreen = { borderWidth,borderWidth };
	Vec2 bottomRightPlayScreen = { borderWidth + playScreenWidth , borderWidth + playScreenHeight };
private:
	class Compass
	{
	public:
		Compass() = default;
		void setCompassBearing(const float bearing);
		void Draw(Graphics& gfx) const;
	private:
		float compassBearing;
	};
private:
	Compass compass;
};

