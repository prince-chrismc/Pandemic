#include "Token.h"

RedDiseaseCubePile::RedDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(&RedDiseaseCube());
	}
}

YellowDiseaseCubePile::YellowDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(&YellowDiseaseCube());
	}
}

BlueDiseaseCubePile::BlueDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(&BlueDiseaseCube());
	}
}

BlackDiseaseCubePile::BlackDiseaseCubePile()
{
	for (size_t i = 0; i < 24; i++)
	{
		m_pile.emplace_back(&BlackDiseaseCube());
	}
}

bool DiseaseCubePile::isAnyEmpty()
{
	return m_red.isEmpty() || m_yellow.isEmpty() || m_blue.isEmpty() || m_black.isEmpty();
}

DiseaseCube * DiseaseCubePile::takeCube(const Color & color)
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

Color City::getCityColor(const uint64_t & id)
{
	if (IsRedCity(id)) return RED;
	else if (IsYellowCity(id)) return YELLOW;
	else if (IsBlueCity(id)) return BLUE;
	else if (IsBlackCity(id)) return BLACK;
	else return INVALID;
}
