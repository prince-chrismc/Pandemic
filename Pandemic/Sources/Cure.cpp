#include "Cure.h"

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