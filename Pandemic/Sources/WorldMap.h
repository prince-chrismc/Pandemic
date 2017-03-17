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
	City* m_Cities[48];

public:
	WorldMap();
	~WorldMap();

	//Prevent Copy/Assignment
	WorldMap(const WorldMap&) = delete;
	void operator=(const WorldMap&) = delete;
	
	City* GetCityWithID(const City::CityID& id);
	std::vector<City*> GetCitiesConnectedTo(const City::CityID& id);
	std::vector<City*> GetAllCities();
	void PrintCitiesStatus();
	
	std::string GetSaveOutput();
};
