#include "DiseaseCubes.h"

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
