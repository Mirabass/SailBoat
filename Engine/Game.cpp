/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	sea(10000,10000),
	playerBoat(Vec2(3000,4000), Vec2(0,-40),-5.0f)
{

}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	Wind localWind = sea.getLocalWind(playerBoat.getPosition());
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) // turn rudder left
	{
		playerBoat.tiltRudder(-1,dt);
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) // turn ruder right
	{
		playerBoat.tiltRudder(+1, dt);
	}
	if (wnd.kbd.KeyIsPressed(0x57)) // Key W - release Main Sail
	{
		playerBoat.ReleaseMainSheet(localWind, dt);
	}
	if (wnd.kbd.KeyIsPressed(0x53)) // Key S - tight Main Sail
	{
		playerBoat.TightMainSheet(localWind, dt);
	}
	playerBoat.Update(dt, brd, localWind);
}

void Game::ComposeFrame()
{
	sea.Draw(playerBoat, brd, gfx);
	playerBoat.Draw(gfx);
	brd.Draw(gfx);
}
