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

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Map's Token Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include "DiseaseCubes.h"

class City final : public CityList
{
private:
	CityID m_CityID;
	Color m_Color;
	std::string m_Name;
	std::vector<City*> m_NearBy;
	std::vector<DiseaseCube*> m_Cubes;

protected:
	bool ValidateCubes() { return (m_Cubes.size() <= 3); }
	bool IsaRedCity() { return (m_CityID > RED_MIN) && (m_CityID < RED_MAX); }
	bool IsaYellowCity() { return (m_CityID > YELLOW_MIN) && (m_CityID < YELLOW_MAX); }
	bool IsaBlueCity() { return (m_CityID > BLUE_MIN) && (m_CityID < BLUE_MAX); }
	bool IsaBlackCity() { return (m_CityID > BLACK_MIN) && (m_CityID < BLACK_MAX); }

public:
	City(const CityID& id, const char* name) : m_CityID(id), m_Color(GetCityColor()), m_Name(name), m_NearBy(), m_Cubes() {}
	~City();

	///Prevent Copy/Assignment
	City(const City&) = delete;
	void operator=(const City&) = delete;

	void AddNearByCity(City* nearby) { m_NearBy.emplace_back(nearby); } ///strictly for world map
	void RemoveNearByCity(const uint16_t& pos) { m_NearBy.erase(m_NearBy.begin() + pos); } ///strictly for world map
	
	uint16_t GetNumberOfCubes() { return (uint16_t)m_Cubes.size(); }
	uint16_t GetNumberOfCubes(const Color& color);
	void AddCube(DiseaseCube* cube) { if (cube == nullptr) { return; } m_Cubes.emplace_back(cube); Validates(); }
	bool Validates();
	DiseaseCube* RemoveCube() { DiseaseCube* dc = m_Cubes.at(0); m_Cubes.erase(m_Cubes.begin(), m_Cubes.begin() + 1); return dc; }
	std::vector<DiseaseCube*> RemoveCubeForCured(const Color& color) { return RemoveCubeAsMedic(color); }
	std::vector<DiseaseCube*> RemoveCubeAsMedic();
	std::vector<DiseaseCube*> RemoveCubeAsMedic(const Color& color);

	Color GetCityColor();
	CityID GetCityID() { return m_CityID; }
	std::vector<City*> GetNearByCities() { return m_NearBy; }
	std::string GetCityName() { return m_Name; }

	std::string GetMapOutput();

	void PrintInformation();
	std::string GetSaveOutput(); //For FilePrint
};

// Research Centers -------------------------------------------------------------------------------
class ResearchCenter final
{
private:
	City* m_City;

public:
	ResearchCenter(City* city) : m_City(city) {}

	City* GetCity() { return m_City; }
	City::CityID GetCityID() { return m_City->GetCityID(); }
};
