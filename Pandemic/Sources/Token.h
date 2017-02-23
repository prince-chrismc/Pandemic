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

	void CureDiscover() { m_state = KNOWN; }
	void EradicateDisease() { m_state = ERADICATED; }
	bool IsCured() { return (m_state == KNOWN); }
};

class RedCure final : public Cure { public: RedCure() : Cure(RED) {} };
class YellowCure final : public Cure { public: YellowCure() : Cure(YELLOW) {} };
class BlueCure final : public Cure { public: BlueCure() : Cure(BLUE) {} };
class BlackCure final : public Cure { public: BlackCure() : Cure(BLACK) {} };

class CureMakers final
{
private:
	RedCure m_red;
	YellowCure m_yellow;
	BlueCure m_blue;
	BlackCure m_black;

public:
	CureMakers() : m_red(), m_yellow(), m_blue(), m_black() {}

	void CureDiscover(const Color& color);
	void EradicateDisease(const Color& color);
	bool IsCured(const Color& color);
};

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
	uint8_t m_cubes;

public:
	CubePile() : m_cubes(24) {}

	bool isEmpty() { return (m_cubes == 0); }
	virtual DiseaseCube* takeCube() = 0;
	void placeCube(DiseaseCube* dc) { delete dc; m_cubes += 1; }
}; 

class RedDiseaseCubePile final : public CubePile 
{ 
public: 
	RedDiseaseCubePile() {}
	DiseaseCube* takeCube() { m_cubes -= 1; return new RedDiseaseCube(); }
};

class YellowDiseaseCubePile final : public CubePile 
{
public: 
	YellowDiseaseCubePile() {}
	DiseaseCube* takeCube() { m_cubes -= 1; return new YellowDiseaseCube(); }
};

class BlueDiseaseCubePile final : public CubePile 
{
public: 
	BlueDiseaseCubePile() {}
	DiseaseCube* takeCube() { m_cubes -= 1; return new BlueDiseaseCube(); }
};

class BlackDiseaseCubePile final : public CubePile 
{ public: 
	BlackDiseaseCubePile() {}
	DiseaseCube* takeCube() { m_cubes -= 1; return new BlackDiseaseCube(); }
};

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
	City(const CityID& id, const char* name) : m_cityID(id), m_color(getCityColor()), m_name(name), m_NearByCities(), m_DiseasCubes() {}

	void addNearByCity(City* nearby) { m_NearByCities.emplace_back(nearby); }
	void addCube(DiseaseCube* cube) { m_DiseasCubes.emplace_back(cube); }

	Color getCityColor();
	bool IsRedCity() { return (m_cityID > RED_MIN) && (m_cityID < RED_MAX); }
	bool IsYellowCity() { return (m_cityID > YELLOW_MIN) && (m_cityID < YELLOW_MAX); }
	bool IsBlueCity() { return (m_cityID > BLUE_MIN) && (m_cityID < BLUE_MAX); }
	bool IsBlackCity() { return (m_cityID > BLACK_MIN) && (m_cityID < BLACK_MAX); }

	bool compareCityID(const uint64_t& id) { return (m_cityID == (CityID)id); }
	std::vector<City*> getNearByCities() { return m_NearByCities; }

	void PrintInformation();
};

// Research Centers -------------------------------------------------------------------------------
class ResearchCenter final /* TODO: Develop object */
{
private:
	City* m_city;

public:
	ResearchCenter(City* city) : m_city(city) {}
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
