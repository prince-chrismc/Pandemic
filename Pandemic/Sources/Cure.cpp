#include "Cure.h"

void CureMakers::CureDiscover(const Color & color)
{
	switch (color)
	{
	case Color::RED:
		m_Red.CureDiscover();
		break;
	case Color::YELLOW:
		m_Yellow.CureDiscover();
		break;
	case Color::BLUE:
		m_Blue.CureDiscover();
		break;
	case Color::BLACK:
		m_Black.CureDiscover();
		break;
	}
}

void CureMakers::EradicateDisease(const Color& color)
{
	switch (color)
	{
	case Color::RED:
		m_Red.EradicateDisease();
		break;
	case Color::YELLOW:
		m_Yellow.EradicateDisease();
		break;
	case Color::BLUE:
		m_Blue.EradicateDisease();
		break;
	case Color::BLACK:
		m_Black.EradicateDisease();
		break;
	}
}

bool CureMakers::IsCured(const Color& color)
{
	switch (color)
	{
	case Color::RED:
		return m_Red.IsCured();
	case Color::YELLOW:
		return m_Yellow.IsCured();
	case Color::BLUE:
		return m_Blue.IsCured();
	case Color::BLACK:
		return m_Black.IsCured();
	default:
		return false;
	}
}

bool CureMakers::IsNotEradicated(const Color & color)
{
	switch (color)
	{
	case Color::RED:
		return m_Red.IsNotEradicated();
	case Color::YELLOW:
		return m_Yellow.IsNotEradicated();
	case Color::BLUE:
		return m_Blue.IsNotEradicated();
	case Color::BLACK:
		return m_Black.IsNotEradicated();
	default:
		return false;
	}
}