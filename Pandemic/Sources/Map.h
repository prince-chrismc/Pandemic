///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Map Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "Pandemic.h"

class Cure abstract
{
protected:
	enum State { UNDISCOVERED, KNOWN, ERADICATED };

	Color m_color;
	State m_state;

public:
	Cure(const Color& color) : m_color(color), m_state(UNDISCOVERED) {}

	void DiscoverCure() { m_state = KNOWN; }
	void EradicateDisease() { m_state = ERADICATED; }

	bool IsCured() { return (m_state == KNOWN); }
};

class RedCure final : public Cure { public: RedCure() : Cure(RED) {} };
class YellowCure final : public Cure { public: YellowCure() : Cure(YELLOW) {} };
class BlueCure final : public Cure { public: BlueCure() : Cure(BLUE) {} };
class BlackCure final : public Cure { public: BlackCure() : Cure(BLACK) {} };

class DiseaseCube abstract
{
private:
	Color m_color;

public:
	DiseaseCube(const Color& color) : m_color(color) {}
};

class RedDiseaseCube final : public DiseaseCube { public: RedDiseaseCube() : DiseaseCube(RED) {} };
class YellowDiseaseCube final : public DiseaseCube { public: YellowDiseaseCube() : DiseaseCube(YELLOW) {} };
class BlueDiseaseCube final : public DiseaseCube { public: BlueDiseaseCube() : DiseaseCube(BLUE) {} };
class BlackDiseaseCube final : public DiseaseCube { public: BlackDiseaseCube() : DiseaseCube(BLACK) {} };


class City final : public CityList
{
private:
	CityID m_cityID;
	Color m_color;
	std::string m_name;
	std::vector<City*> m_NearByCities;
	std::vector<DiseaseCube*> m_DiseasCubes;

public:
	City(const CityID& id, const Color& color, const char* name) : m_cityID(id), m_color(color), m_name(name) {}

	void addNearByCity(City* nearby) { m_NearByCities.emplace_back(nearby); }
	void addCube(DiseaseCube* cube) { m_DiseasCubes.emplace_back(cube); }
};


class InfectionRate final
{
private:
	uint8_t m_position;
	const uint8_t m_array[7] = { 2, 2, 2, 3, 3, 4, 4 };

public:
	InfectionRate() : m_position(0) {}
	uint8_t getRate() { return m_array[m_position]; }
	void increaseRate() { m_position += 1; }
};

class OutbreakMarker final
{
private:
	uint8_t m_position;
	const uint8_t m_array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

public:
	OutbreakMarker() : m_position(0) {}
	uint8_t getMarker() { return m_array[m_position]; }
	void increaseRate() { m_position += 1; }
};

class WorldMap final
{
private:
	City* m_cities[48];
	InfectionRate m_infect;
	OutbreakMarker m_outbreeak;
	Cure* m_cures[4];
	DiseaseCube* m_cubes[96];
};