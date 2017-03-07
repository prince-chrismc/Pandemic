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
	bool IsNotEradicated() { return (m_state != ERADICATED); }
	std::string GetState() { return std::to_string(m_state); } //FilePrint
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

	//Prevent Copy/Assignment
	CureMakers(const CureMakers&) = delete;
	void operator=(const CureMakers&) = delete;

	void CureDiscover(const Color& color);
	void EradicateDisease(const Color& color);
	bool IsCured(const Color& color);
	bool IsNotEradicated(const Color& color);
	std::string GetSaveOutput() { return (m_red.GetState() + m_blue.GetState() + m_yellow.GetState() + m_black.GetState()); } //FilePrint
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

	uint8_t cubesLeft() { return m_cubes; }
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

	//Prevent Copy/Assignment
	DiseaseCubePile(const DiseaseCubePile&) = delete;
	void operator=(const DiseaseCubePile&) = delete;

	bool isAnyEmpty();
	DiseaseCube* takeCube(const Color& color);
	void placeCube(DiseaseCube* dc);
	std::string PrintCubesLeft() { return std::to_string(m_red.cubesLeft()) + " " + std::to_string(m_yellow.cubesLeft()) + " " + std::to_string(m_blue.cubesLeft()) + " " + std::to_string(m_black.cubesLeft()); }
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

	//Prevent Copy/Assignment
	City(const City&) = delete;
	void operator=(const City&) = delete;

	void addNearByCity(City* nearby) { m_NearByCities.emplace_back(nearby); }

	uint8_t GetNumberOfCubes() { return (uint8_t)m_DiseasCubes.size(); }
	void addCube(DiseaseCube* cube) { m_DiseasCubes.emplace_back(cube); }

	Color getCityColor();
	bool IsRedCity() { return (m_cityID > RED_MIN) && (m_cityID < RED_MAX); }
	bool IsYellowCity() { return (m_cityID > YELLOW_MIN) && (m_cityID < YELLOW_MAX); }
	bool IsBlueCity() { return (m_cityID > BLUE_MIN) && (m_cityID < BLUE_MAX); }
	bool IsBlackCity() { return (m_cityID > BLACK_MIN) && (m_cityID < BLACK_MAX); }

	CityID getCityID() { return m_cityID; }
	bool compareCityID(const uint64_t& id) { return (m_cityID == (CityID)id); }
	std::vector<City*> getNearByCities() { return m_NearByCities; }

	void PrintInformation();
	std::string GetSaveOutput();
};

// Research Centers -------------------------------------------------------------------------------
class ResearchCenter final /* TODO: Develop object */
{
private:
	City* m_city;

public:
	ResearchCenter(City* city) : m_city(city) {}

	//Prevent Assignment
	void operator=(const ResearchCenter&) = delete;

	City::CityID GetCityID() { return m_city->getCityID(); }
};

class ResearchStations final
{
private:
	std::vector<ResearchCenter> m_stations;

protected:
	bool validate() { return (m_stations.size() < 7); }

public:
	ResearchStations() : m_stations() {};

	//Prevent Copy/Assignment
	ResearchStations(const ResearchStations&) = delete;
	void operator=(const ResearchStations&) = delete;

	uint8_t GetNumberOfCenters() { return (uint8_t)m_stations.size(); }
	void AddStation(City* city) { if(validate()) m_stations.emplace_back(ResearchCenter(city)); }
};

// Markers ----------------------------------------------------------------------------------------
class InfectionRate final
{
private:
	uint8_t m_position;
	const uint8_t m_array[7] = { 2, 2, 2, 3, 3, 4, 4 };

public:
	InfectionRate() : m_position(0) {}

	//Prevent Copy/Assignment
	InfectionRate(const InfectionRate&) = delete;
	void operator=(const InfectionRate&) = delete;

	uint8_t getRate() { return m_array[m_position]; }
	void IncreaseRate() { m_position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_position); }
};

class OutbreakMarker final
{
private:
	uint8_t m_position;
	const uint8_t m_array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

public:
	OutbreakMarker() : m_position(0) {}

	//Prevent Copy/Assignment
	OutbreakMarker(const OutbreakMarker&) = delete;
	void operator=(const OutbreakMarker&) = delete;

	uint8_t getMarker() { return m_array[m_position]; }
	void IncreaseRate() { m_position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_position); }
};
