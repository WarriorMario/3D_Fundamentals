/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
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
#include "Ray.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = 1.0f / 60.0f;
}

void Game::ComposeFrame()
{
	// Camera and screen
	Vec3 camPos = Vec3(0, 0, 0);
	Vec3 viewDir = Vec3(0, 0, 1);
	float screenDistance = 1.0f;

	Vec3 screenCenter = camPos + viewDir*screenDistance;
	Vec3 p0 = screenCenter + Vec3(-1, -1, 0);
	Vec3 p1 = screenCenter + Vec3(1, -1, 0);
	Vec3 p2 = screenCenter + Vec3(-1, 1, 0);

	// Create a ray for every pixel on the screen
	for (int y = 0; y < Graphics::ScreenHeight; ++y)
	{
		for (int x = 0; x < Graphics::ScreenWidth; ++x)
		{
			float u = (float)x / Graphics::ScreenWidth;
			float v = (float)y / Graphics::ScreenHeight;
			Vec3 pointOnScreen = p0 + (p1 - p0)*u + (p2 - p0)*v;
			Vec3 rayDirection = pointOnScreen - camPos;
			Ray ray = Ray(camPos, rayDirection.GetNormalized(), 10000000.0f);
		}
	}
}