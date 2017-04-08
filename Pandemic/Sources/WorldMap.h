///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Wold Map Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Tokens.h"

class WorldMap final //The Connected Cities
{
private:
	std::vector<City*> m_Cities;
	bool m_costumized;

public:
	WorldMap();
	~WorldMap();

	// Garbage code because it ruins the game.. PS untested LOL
	void UserDriverCostumization();
	bool Validate();

	//Prevent Copy/Assignment
	WorldMap(const WorldMap&) = delete;
	void operator=(const WorldMap&) = delete;
	
	City* GetCityWithID(const City::CityID& id);
	std::vector<City*> GetCitiesConnectedTo(const City::CityID& id);
	std::vector<City*> GetAllCities() { return m_Cities; }
	
	std::string GetMapDiagram();

	std::string GetSaveOutput();
};
