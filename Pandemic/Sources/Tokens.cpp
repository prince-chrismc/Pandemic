#include "Tokens.h"

bool DiseaseCubePile::IsAnyEmpty()
{
	return m_Red.IsEmpty() || m_Yellow.IsEmpty() || m_Blue.IsEmpty() || m_Black.IsEmpty();
}

DiseaseCube* DiseaseCubePile::TakeCube(const Color& color)
{
	DiseaseCube* dc = nullptr;
	switch (color)
	{
	case RED:
		dc = m_Red.TakeCube();
		break;
	case YELLOW:
		dc = m_Yellow.TakeCube();
		break;
	case BLUE:
		dc = m_Blue.TakeCube();
		break;
	case BLACK:
		dc = m_Black.TakeCube();
		break;
	}
	return dc;
}

void DiseaseCubePile::PlaceCube(DiseaseCube* dc)
{
	switch (dc->GetColor())
	{
	case RED:
		m_Red.PlaceCube(dc);
		break;
	case YELLOW:
		m_Yellow.PlaceCube(dc);
		break;
	case BLUE:
		m_Blue.PlaceCube(dc);
		break;
	case BLACK:
		m_Black.PlaceCube(dc);
		break;
	}
}

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
	if (IsaRedCity()) return RED;
	else if (IsaYellowCity()) return YELLOW;
	else if (IsaBlueCity()) return BLUE;
	else if (IsaBlackCity()) return BLACK;
	else return INVALID;
}

void City::PrintInformation()
{
	printf("City: %s has %d DiseaseCubes.\n", m_Name.c_str(), (int)m_Cubes.size());
}

std::string City::GetSaveOutput()
{
	std::string result = "";

	if (m_Cubes.size() != 0)
	{
		for each (DiseaseCube* cube in m_Cubes)
		{
			result += std::to_string(cube->GetColor()) + " ";
		}
	}

	return result;
}

void CureMakers::CureDiscover(const Color & color)
{
	switch (color)
	{
	case RED:
		m_Red.CureDiscover();
		break;
	case YELLOW:
		m_Yellow.CureDiscover();
		break;
	case BLUE:
		m_Blue.CureDiscover();
		break;
	case BLACK:
		m_Black.CureDiscover();
		break;
	}
}

void CureMakers::EradicateDisease(const Color& color)
{
	switch (color)
	{
	case RED:
		m_Red.EradicateDisease();
		break;
	case YELLOW:
		m_Yellow.EradicateDisease();
		break;
	case BLUE:
		m_Blue.EradicateDisease();
		break;
	case BLACK:
		m_Black.EradicateDisease();
		break;
	}
}

bool CureMakers::IsCured(const Color& color)
{
	switch (color)
	{
	case RED:
		return m_Red.IsCured();
	case YELLOW:
		return m_Yellow.IsCured();
	case BLUE:
		return m_Blue.IsCured();
	case BLACK:
		return m_Black.IsCured();
	default:
		return false;
	}
}

bool CureMakers::IsNotEradicated(const Color & color)
{
	switch (color)
	{
	case RED:
		return m_Red.IsNotEradicated();
	case YELLOW:
		return m_Yellow.IsNotEradicated();
	case BLUE:
		return m_Blue.IsNotEradicated();
	case BLACK:
		return m_Black.IsNotEradicated();
	default:
		return false;
	}
}

bool CureMakers::IsAllCuresDiscovered()
{
	return m_Red.IsCured() && m_Yellow.IsCured() && m_Blue.IsCured() && m_Black.IsCured();
}
