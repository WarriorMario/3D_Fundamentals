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
#include "Mat3.h"
#include "Light.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	spheres = {
		Sphere(Vec3(1e5,0, -2500)  ,1e5,Color(255,0,0)), //Right wall
		Sphere(Vec3(-1e5 ,0, -2500),1e5,Color(0,255,0)), //Left  wall 
		Sphere(Vec3(0,0,1e5 + 100),1e5,Color(0,0,255)),// Back wall
		Sphere(Vec3(0, -1e5, -2500),1e5,Color(200,55,0)),// Bottom wall 
		Sphere(Vec3(0,1e5,2500),1e5,Color(55,200,0)),// Top wall
		Sphere(Vec3(0,0,-1e5 - 100),1e5,Color(0,55,0)),// Front wall
		Sphere(Vec3(-20,15,70),11,Color(255,255,255)),// S0
		Sphere(Vec3(20,-15,75),13,Color(200,55,200))// S1
	};
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
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta_x = wrap_angle(theta_x - dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta_y = wrap_angle(theta_y - dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta_x = wrap_angle(theta_x + dTheta * dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta_y = wrap_angle(theta_y + dTheta * dt);
	}

	const Mat3 rot =
		Mat3::RotationX(theta_x)*
		Mat3::RotationY(theta_y);
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		pos += Vec3(0, 0, 1)*rot;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		pos += Vec3(0, 0, -1)*rot;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		pos += Vec3(-1, 0, 0)*rot;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		pos += Vec3(1, 0, 0)*rot;
	}
}

void Game::ComposeFrame()
{
	// Camera and screen
	Vec3 camPos = pos;
	const Mat3 rot =
		Mat3::RotationX(theta_x)*
		Mat3::RotationY(theta_y);
	Vec3 viewDir = Vec3(0, 0, 1)*rot;
	float screenDistance = 1.0f;

	Vec3 screenCenter = camPos + viewDir*screenDistance;
	Vec3 p0 = screenCenter + Vec3(-1, 1, 0)*rot;
	Vec3 p1 = screenCenter + Vec3(1, 1, 0)*rot;
	Vec3 p2 = screenCenter + Vec3(-1, -1, 0)*rot;
	
	Light light = Light(Vec3(20, 25, 25), Colors::White);

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
			// Intersect all spheres
			int hitIndex = -1;
			for (int i = 0; i < spheres.size(); ++i)
			{
				if (ray.RaySphereIntersection(spheres[i]) == true)
				{
					hitIndex = i;
				}
			}
			if (hitIndex != -1)
			{
				Vec3 hitPoint = ray.origin + ray.direction*ray.length;
				Vec3 normal = (hitPoint - spheres[hitIndex].position);
				normal.Normalize();
				Vec3 lightRayDirection = (light.position - hitPoint);
				lightRayDirection.Normalize();
				float d = Dot(normal, lightRayDirection);
				if (d < 0.0f)
				{
					d = 0.0f;
				}
				gfx.PutPixel(x, y, spheres[hitIndex].color * light.color * d);
			}
		}
	}
}