/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sstream>
#include "Cure.h"

void CureMarkers::CureDiscover(const Color & color)
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
	Notify();
}

void CureMarkers::EradicateDisease(const Color& color)
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
	Notify();
}

bool CureMarkers::IsCured(const Color& color)
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

bool CureMarkers::IsNotEradicated(const Color & color)
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

bool CureMarkers::IsEradicated(const Color & color)
{
	switch (color)
	{
	case Color::RED:
		return m_Red.IsEradicated();
	case Color::YELLOW:
		return m_Yellow.IsEradicated();
	case Color::BLUE:
		return m_Blue.IsEradicated();
	case Color::BLACK:
		return m_Black.IsEradicated();
	default:
		return false;
	}
}

CureMarkers::Builder & CureMarkers::Builder::ParseRedCure(std::string loaded)
{
	std::stringstream ss;
	ss << loaded.at(0);
	ss >> m_Red;
	return *this;
}

CureMarkers::Builder & CureMarkers::Builder::ParseBlueCure(std::string loaded)
{
	std::stringstream ss;
	ss << loaded.at(1);
	ss >> m_Blue;
	return *this;
}

CureMarkers::Builder & CureMarkers::Builder::ParseYellowCure(std::string loaded)
{
	std::stringstream ss;
	ss << loaded.at(2);
	ss >> m_Yellow;
	return *this;
}

CureMarkers::Builder & CureMarkers::Builder::ParseBlackCure(std::string loaded)
{
	std::stringstream ss;
	ss << loaded.at(3);
	ss >> m_Black;
	return *this;
}
