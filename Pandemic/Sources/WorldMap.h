///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Wold Map Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Token.h"

class WorldMap final //The Connected Cities
{
private:
	City* m_cities[48];

public:
	WorldMap();
	~WorldMap();

	//Prevent Copy/Assignment
	WorldMap(const WorldMap&) = delete;
	void operator=(const WorldMap&) = delete;
	
	City* getCityWithID(const City::CityID& id);
	std::vector<City*> getCitiesConnectedTo(const City::CityID& id);
	void PrintCitiesStatus();
	
	std::string GetSaveOutput();
};
