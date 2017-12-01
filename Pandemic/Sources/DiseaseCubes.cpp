/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "DiseaseCubes.h"

bool DiseaseCubePile::IsFull(const Color & color)
{
	switch (color)
	{
	case Color::RED:
		return m_Red.CubesLeft() == 24;
	case Color::YELLOW:
		return m_Yellow.CubesLeft() == 24;
	case Color::BLUE:
		return m_Blue.CubesLeft() == 24;
	case Color::BLACK:
		return m_Black.CubesLeft() == 24;
	}
	return false;
}

DiseaseCube* DiseaseCubePile::TakeCube(const Color& color)
{
	DiseaseCube* dc = nullptr;
	switch (color)
	{
	case Color::RED:
		dc = m_Red.TakeCube();
		break;
	case Color::YELLOW:
		dc = m_Yellow.TakeCube();
		break;
	case Color::BLUE:
		dc = m_Blue.TakeCube();
		break;
	case Color::BLACK:
		dc = m_Black.TakeCube();
		break;
	}
	return dc;
}

const Color DiseaseCubePile::PlaceCube(DiseaseCube* dc)
{
	const Color result = dc->GetColor();
	switch (dc->GetColor())
	{
	case Color::RED:
		m_Red.PlaceCube(dc);
		break;
	case Color::YELLOW:
		m_Yellow.PlaceCube(dc);
		break;
	case Color::BLUE:
		m_Blue.PlaceCube(dc);
		break;
	case Color::BLACK:
		m_Black.PlaceCube(dc);
		break;
	}
	return result;
}
