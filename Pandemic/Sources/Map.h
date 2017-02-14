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


class City final
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


class InfectionRate final
{
private:
	uint8_t m_position;
	uint8_t m_array[7] = { 2, 2, 2, 3, 3, 4, 4 };

public:
	InfectionRate() : m_position(0) {}
	uint8_t getRate() { return m_array[m_position]; }
	void increaseRate() { m_position += 1; }
};

class OutbreakMarker final
{
private:
	uint8_t m_position;
	uint8_t m_array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

public:
	OutbreakMarker() : m_position(0) {}
	uint8_t getMarker() { return m_array[m_position]; }
	void increaseRate() { m_position += 1; }
};

class WorldMap final
{
private:
	City m_cities[48];
	InfectionRate m_infect;
	OutbreakMarker m_outbreeak;
};