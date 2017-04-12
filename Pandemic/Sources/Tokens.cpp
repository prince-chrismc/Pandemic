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
			return false;
		}
		if (GetNumberOfCubes(Color::BLACK) > 3)
		{
			throw GameErrorException("Black Cubes Exceded Maximum in " + m_Name);
			return false;
		}
		if (GetNumberOfCubes(Color::YELLOW) > 3)
		{
			throw GameErrorException("Yellow Cubes Exceded Maximum in " + m_Name);
			return false;
		}
		if (GetNumberOfCubes(Color::BLUE) > 3)
		{
			throw GameErrorException("Blue Cubes Exceded Maximum in " + m_Name);
			return false;
		}
	}
#endif // _DEBUG
	return true;	
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

std::string ResearchStations::GetSaveOutput()
{
	std::string result = "";

	for each(ResearchCenter rc in m_Stations)
	{
		std::stringstream ss;
		ss << std::hex << rc.GetCityID();
		result += ss.str();
	}

	return result;
}
