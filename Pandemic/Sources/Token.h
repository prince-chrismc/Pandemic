///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Map's Token Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Pandemic.h"

// Cure -------------------------------------------------------------------------------------------
class Cure abstract
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

class RedCure final : public Cure { public: RedCure() : Cure(RED) {} };
class YellowCure final : public Cure { public: YellowCure() : Cure(YELLOW) {} };
class BlueCure final : public Cure { public: BlueCure() : Cure(BLUE) {} };
class BlackCure final : public Cure { public: BlackCure() : Cure(BLACK) {} };

// Cubes ------------------------------------------------------------------------------------------
class DiseaseCube abstract
{
private:
	Color m_color;

public:
	DiseaseCube(const Color& color) : m_color(color) {}
	Color getColor() { return m_color; }
};

class RedDiseaseCube final : public DiseaseCube { public: RedDiseaseCube() : DiseaseCube(RED) {} };
class YellowDiseaseCube final : public DiseaseCube { public: YellowDiseaseCube() : DiseaseCube(YELLOW) {} };
class BlueDiseaseCube final : public DiseaseCube { public: BlueDiseaseCube() : DiseaseCube(BLUE) {} };
class BlackDiseaseCube final : public DiseaseCube { public: BlackDiseaseCube() : DiseaseCube(BLACK) {} };

class CubePile abstract
{
protected:
	std::vector<DiseaseCube*> m_pile;

public:
	CubePile() {}

	bool isEmpty() { return (m_pile.size() == 0); }
	DiseaseCube* takeCube() { DiseaseCube* dc = m_pile.back(); m_pile.pop_back(); return dc; }
	void placeCube(DiseaseCube* dc) { m_pile.emplace_back(dc); }

}; 

class RedDiseaseCubePile final : public CubePile { public: RedDiseaseCubePile(); };
class YellowDiseaseCubePile final : public CubePile { public: YellowDiseaseCubePile(); };
class BlueDiseaseCubePile final : public CubePile { public: BlueDiseaseCubePile(); };
class BlackDiseaseCubePile final : public CubePile { public: BlackDiseaseCubePile(); };

class DiseaseCubePile final
{
private:
	RedDiseaseCubePile m_red;
	YellowDiseaseCubePile m_yellow;
	BlueDiseaseCubePile m_blue;
	BlackDiseaseCubePile m_black;

public:
	DiseaseCubePile() {}

	bool isAnyEmpty();
	DiseaseCube* takeCube(const Color& color);
	void placeCube(DiseaseCube* dc);
};

// Cities -----------------------------------------------------------------------------------------
class City final : public CityList
{
private:
	CityID m_cityID;
	Color m_color;
	std::string m_name;
	std::vector<City*> m_NearByCities;
	std::vector<DiseaseCube*> m_DiseasCubes;

public:
	City(const CityID& id, const char* name) : m_cityID(id), m_color(getCityColor(id)), m_name(name) {}

	void addNearByCity(City* nearby) { m_NearByCities.emplace_back(nearby); }
	void addCube(DiseaseCube* cube) { m_DiseasCubes.emplace_back(cube); }
	Color getCityColor(const uint64_t& id);
	bool IsRedCity(const uint64_t& id) { return (id > RED_MIN) && (id < RED_MAX); }
	bool IsYellowCity(const uint64_t& id) { return (id > YELLOW_MIN) && (id < YELLOW_MAX); }
	bool IsBlueCity(const uint64_t& id) { return (id > BLUE_MIN) && (id < BLUE_MAX); }
	bool IsBlackCity(const uint64_t& id) { return (id > BLACK_MIN) && (id < BLACK_MAX); }
};

// Markers ----------------------------------------------------------------------------------------
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
