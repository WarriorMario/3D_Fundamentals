/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Colors.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once
class FColor;
class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( const Color& col )
		:
		dword( col.dword )
	{}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}
	constexpr Color(const FColor& col);
	Color& operator =( Color color )
	{
		dword = color.dword;
		return *this;
	}
	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};

class FColor
{
public:
	float a;
	float r;
	float g;
	float b;
	constexpr FColor() : a(),r(),g(),b() {}
	constexpr FColor(float a, float r, float g, float b) 
		: 
		a(a),
		r(r),
		g(g),
		b(b)
	{}
	constexpr FColor(const FColor& col)
		:
		a(col.a),
		r(col.r),
		g(col.g),
		b(col.b)
	{}
	constexpr FColor(const Color& col)
		:
		a(((float)((col.dword & 0xff000000) >> 24)) / 255.0f),
		r(((float)((col.dword & 0x00ff0000) >> 16)) / 255.0f),
		g(((float)((col.dword & 0x0000ff00) >> 8)) / 255.0f),
		b(((float)((col.dword & 0x000000ff))) / 255.0f)
	{}


	FColor operator+(const FColor &rhs)const
	{
		return FColor(*this) += rhs;
	}
	FColor& operator+=(const FColor &rhs)
	{
		a += rhs.a;
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}
	FColor operator*(const FColor &rhs)const
	{
		return FColor(*this) *= rhs;
	}
	FColor& operator*=(const FColor &rhs)
	{
		a *= rhs.a;
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
		return *this;
	}
	FColor operator*(float rhs)const
	{
		return FColor(*this) *= rhs;
	}
	FColor& operator*=(float rhs)
	{
		a *= rhs;
		r *= rhs;
		g *= rhs;
		b *= rhs;
		return *this;
	}

	void Clamp()
	{
		a = a <= 0.0f ? 0.0f : a >= 1.0f ? 1.0f : a;
		r = r <= 0.0f ? 0.0f : r >= 1.0f ? 1.0f : r;
		g = g <= 0.0f ? 0.0f : g >= 1.0f ? 1.0f : g;
		b = b <= 0.0f ? 0.0f : b >= 1.0f ? 1.0f : b;
	}
};

constexpr Color::Color(const FColor& col)
	:
	Color(
	(unsigned char)(col.a * 255.0f),
	(unsigned char)(col.r * 255.0f),
	(unsigned char)(col.g * 255.0f),
	(unsigned char)(col.b * 255.0f))
{}

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeRGB( 255u,255u,255u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	static constexpr Color Red = MakeRGB( 255u,0u,0u );
	static constexpr Color Green = MakeRGB( 0u,255u,0u );
	static constexpr Color Blue = MakeRGB( 0u,0u,255u );
	static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	static constexpr Color Cyan = MakeRGB( 0u,255u,255u );
	static constexpr Color Magenta = MakeRGB( 255u,0u,255u );
}