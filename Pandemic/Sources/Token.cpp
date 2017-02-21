#include "Token.h"

CubePile::~CubePile()
{
	for (size_t pos = 0; pos < m_pile.size(); pos += 1)
	{
		if (m_pile.at(pos) != NULL)
		{
			delete m_pile.at(pos);
			m_pile.at(pos) = NULL;
		}
	}
	m_pile.clear();
}

RedDiseaseCubePile::RedDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(new RedDiseaseCube());
	}
}

YellowDiseaseCubePile::YellowDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(new YellowDiseaseCube());
	}
}

BlueDiseaseCubePile::BlueDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(new BlueDiseaseCube());
	}
}

BlackDiseaseCubePile::BlackDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(new BlackDiseaseCube());
	}
}

bool DiseaseCubePile::isAnyEmpty()
{
	return m_red.isEmpty() || m_yellow.isEmpty() || m_blue.isEmpty() || m_black.isEmpty();
}

DiseaseCube* DiseaseCubePile::takeCube(const Color & color)
{
	DiseaseCube* dc = NULL;
	switch (color)
	{
	case RED:
		dc = m_red.takeCube();
		break;
	case YELLOW:
		dc = m_yellow.takeCube();
		break;
	case BLUE:
		dc = m_blue.takeCube();
		break;
	case BLACK:
		dc = m_black.takeCube();
		break;
	}

	return dc;
}

void DiseaseCubePile::placeCube(DiseaseCube * dc)
{
	switch (dc->getColor())
	{
	case RED:
		m_red.placeCube(dc);
		break;
	case YELLOW:
		m_yellow.placeCube(dc);
		break;
	case BLUE:
		m_blue.placeCube(dc);
		break;
	case BLACK:
		m_black.placeCube(dc);
		break;
	}
}

Color City::getCityColor()
{
	if (IsRedCity()) return RED;
	else if (IsYellowCity()) return YELLOW;
	else if (IsBlueCity()) return BLUE;
	else if (IsBlackCity()) return BLACK;
	else return INVALID;
}

void City::PrintInformation()
{
	printf("City: %s has %d DiseaseCubes.\n", m_name.c_str(), (int)m_DiseasCubes.size() );
}

void CureMakers::CureDiscover(const Color & color)
{
	switch (color)
	{
	case RED:
		m_red.CureDiscover();
		break;
	case YELLOW:
		m_yellow.CureDiscover();
		break;
	case BLUE:
		m_blue.CureDiscover();
		break;
	case BLACK:
		m_black.CureDiscover();
		break;
	}
}

void CureMakers::EradicateDisease(const Color & color)
{
	switch (color)
	{
	case RED:
		m_red.EradicateDisease();
		break;
	case YELLOW:
		m_yellow.EradicateDisease();
		break;
	case BLUE:
		m_blue.EradicateDisease();
		break;
	case BLACK:
		m_black.EradicateDisease();
		break;
	}
}

bool CureMakers::IsCured(const Color & color)
{
	switch (color)
	{
	case RED:
		return m_red.IsCured();
	case YELLOW:
		return m_yellow.IsCured();
	case BLUE:
		return m_blue.IsCured();
	case BLACK:
		return m_black.IsCured();
	}
}
