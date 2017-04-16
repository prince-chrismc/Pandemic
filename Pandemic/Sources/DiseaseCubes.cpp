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

const Color& DiseaseCubePile::PlaceCube(DiseaseCube* dc)
{
	Color result = dc->GetColor();
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
