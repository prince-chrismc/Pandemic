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

Color City::GetCityColor()
{
	if (IsaRedCity()) return Color::RED;
	else if (IsaYellowCity()) return Color::YELLOW;
	else if (IsaBlueCity()) return Color::BLUE;
	else if (IsaBlackCity()) return Color::BLACK;
	else return Color::INVALID;
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
