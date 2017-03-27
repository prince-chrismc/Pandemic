#include "DiseaseCubes.h"

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

void DiseaseCubePile::PlaceCube(DiseaseCube* dc)
{
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
}
