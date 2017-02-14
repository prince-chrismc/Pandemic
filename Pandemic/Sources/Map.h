///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Map Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "Pandemic.h"

class Cure
{

protected:
	enum State { UNDISCOVERED, KNOWN, ERADICATED };

private:
	Color m_color;
	State m_state;

public:
	Cure(const Color& color) : m_color(color), m_state(UNDISCOVERED) {}

	void DiscoverCure() { m_state = KNOWN; }
	void EradicateDisease() { m_state = ERADICATED; }

	bool IsCured() { return (m_state == KNOWN); }
};


class DiseaseCube
{
private:
	Color m_color;

public:
	DiseaseCube(const Color& color) : m_color(color) {}
};


class City
{
private:
	Color m_color;
	std::string m_name;
	std::vector<City*> m_NearByCities;
	std::vector<DiseaseCube*> m_DiseasCubes;

public:
	City(const Color& color, const char* name) : m_color(color), m_name(name) {}

	void addNearByCity(City* nearby) { m_NearByCities.emplace(nearby); }
	void addCube(DiseaseCube* cube) { m_DiseasCubes.emplace(cube); }
};


class WorldMap
{
private:
	City m_cities[48];
};