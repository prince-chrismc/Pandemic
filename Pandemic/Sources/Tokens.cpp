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

#include <sstream>
#include "Tokens.h"

City::~City()
{
	for each (DiseaseCube* cube in m_Cubes)
	{
		delete cube;
		cube = nullptr;
	}
}

uint16_t City::GetNumberOfCubes(const Color & color)
{
	uint16_t result = 0;
	for each(DiseaseCube* cube in m_Cubes)
	{
		if (cube->GetColor() == color)
			++result;
	}
	return result;
}

bool City::Validates()
{
#ifdef _DEBUG
	if (m_Cubes.size() > 3)
	{ 
		if (GetNumberOfCubes(Color::RED) > 3)
		{
			throw GameErrorException("Red Cubes Exceded Maximum in " + m_Name);
		}
		if (GetNumberOfCubes(Color::BLACK) > 3)
		{
			throw GameErrorException("Black Cubes Exceded Maximum in " + m_Name);
		}
		if (GetNumberOfCubes(Color::YELLOW) > 3)
		{
			throw GameErrorException("Yellow Cubes Exceded Maximum in " + m_Name);
		}
		if (GetNumberOfCubes(Color::BLUE) > 3)
		{
			throw GameErrorException("Blue Cubes Exceded Maximum in " + m_Name);
		}
	}
#endif // _DEBUG
	return true;	
}

std::vector<DiseaseCube*> City::RemoveCubeAsMedic()
{
	std::vector<DiseaseCube*> cubes = m_Cubes; // get all cubes

	//count colors
	uint16_t red = GetNumberOfCubes(Color::RED);
	uint16_t black = GetNumberOfCubes(Color::BLACK);
	uint16_t yellow = GetNumberOfCubes(Color::YELLOW);
	uint16_t blue = GetNumberOfCubes(Color::BLUE);

	m_Cubes.clear(); //empty to refill laterz

	//determing highest
	Color tbrm = Color::INVALID;
	if (red >= black && red >= yellow && red >= blue) // red is biggest?
	{
		tbrm = Color::RED;
	}
	else if (black >= red && black >= yellow && black >= blue) // black is biggest?
	{
		tbrm = Color::BLACK;
	}
	else if (yellow >= black && yellow >= red && yellow >= blue) // yellow is biggest?
	{
		tbrm = Color::YELLOW;
	}
	else if (blue >= black && blue >= yellow && blue >= red) // blue is biggest?
	{
		tbrm = Color::BLUE;
	}

	//get all of those cubes
	for (auto itor = cubes.begin(); itor != cubes.end(); /* no incr */ )
	{
		if ((*itor)->GetColor() == tbrm)
		{
			itor++; // if its the color to be deleted do nothing
			continue;
		}
		else
		{
			m_Cubes.emplace_back(*itor);
			itor = cubes.erase(itor);
		}
	}

	return cubes;
}

std::vector<DiseaseCube*> City::RemoveCubeAsMedic(const Color& color)
{
	std::vector<DiseaseCube*> cubes; // will be all the cubes of the corresponding color

	for (auto itor = m_Cubes.begin(); itor != m_Cubes.end(); /* no incr */)
	{
		if ((*itor)->GetColor() == color)
		{
			cubes.emplace_back(*itor);
			itor = m_Cubes.erase(itor);
		}
		else
		{
			itor++; // if its not the color to be deleted do nothing
			continue;
		}
	}
	return cubes;
}

Color City::GetCityColor()
{
	if (IsaRedCity()) return Color::RED;
	else if (IsaYellowCity()) return Color::YELLOW;
	else if (IsaBlueCity()) return Color::BLUE;
	else if (IsaBlackCity()) return Color::BLACK;
	else return Color::INVALID;
}

std::string City::GetMapOutput()
{
	return "[" + std::to_string(GetNumberOfCubes(Color::RED)) + "," + std::to_string(GetNumberOfCubes(Color::BLUE)) + "," + std::to_string(GetNumberOfCubes(Color::YELLOW)) + "," + std::to_string(GetNumberOfCubes(Color::BLACK)) + "]";
}

void City::PrintInformation()
{
	printf("City: %s has %d DiseaseCubes.\n", m_Name.c_str(), (uint16_t)m_Cubes.size());
}

std::string City::GetSaveOutput()
{
	std::string result = "";

	if (m_Cubes.size() != 0)
	{
		for each (DiseaseCube* cube in m_Cubes)
		{
			result += std::to_string((uint16_t)cube->GetColor()) + " ";
		}
	}

	return result;
}
