///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Map's Token Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include "Pandemic.h"

// Cure -------------------------------------------------------------------------------------------
class Cure abstract
{
private:
	enum State { UNDISCOVERED, KNOWN, ERADICATED };

	Color m_Color;
	State m_State;

public:
	Cure(const Color& color) : m_Color(color), m_State(UNDISCOVERED) {}

	// Mutator/Accessor
	std::string GetState() { return std::to_string(m_State); }
	void SetState(const uint16_t& state) { m_State = (State)state; }

	void CureDiscover() { m_State = KNOWN; }
	void EradicateDisease() { m_State = ERADICATED; }
	bool IsCured() { return (m_State == KNOWN); }
	bool IsNotEradicated() { return (m_State != ERADICATED); }
};

class RedCure final : public Cure { public: RedCure() : Cure(RED) {} };
class YellowCure final : public Cure { public: YellowCure() : Cure(YELLOW) {} };
class BlueCure final : public Cure { public: BlueCure() : Cure(BLUE) {} };
class BlackCure final : public Cure { public: BlackCure() : Cure(BLACK) {} };

class CureMakers final
{
private:
	RedCure m_Red;
	YellowCure m_Yellow;
	BlueCure m_Blue;
	BlackCure m_Black;

public:
	CureMakers() : m_Red(), m_Yellow(), m_Blue(), m_Black() {}

	//Prevent Copy/Assignment
	CureMakers(const CureMakers&) = delete;
	void operator=(const CureMakers&) = delete;

	void CureDiscover(const Color& color);
	void EradicateDisease(const Color& color);
	bool IsCured(const Color& color);
	bool IsNotEradicated(const Color& color);
	bool IsEradicated(const Color& color) { return !IsNotEradicated(color); }
	bool IsAllCuresDiscovered();
	std::string GetSaveOutput() { return (m_Red.GetState() + m_Blue.GetState() + m_Yellow.GetState() + m_Black.GetState()); } //FilePrint
	void InputLoadedGame(const uint16_t& red, const uint16_t& blue, const uint16_t& yellow, const uint16_t& black) { m_Red.SetState(red); m_Blue.SetState(blue); m_Yellow.SetState(yellow); m_Black.SetState(black); }
};

// Cubes ------------------------------------------------------------------------------------------
class DiseaseCube abstract
{
private:
	Color m_Color;

public:
	DiseaseCube(const Color& color) : m_Color(color) {}
	Color GetColor() { return m_Color; }
};

class RedDiseaseCube final : public DiseaseCube { public: RedDiseaseCube() : DiseaseCube(RED) {} };
class YellowDiseaseCube final : public DiseaseCube { public: YellowDiseaseCube() : DiseaseCube(YELLOW) {} };
class BlueDiseaseCube final : public DiseaseCube { public: BlueDiseaseCube() : DiseaseCube(BLUE) {} };
class BlackDiseaseCube final : public DiseaseCube { public: BlackDiseaseCube() : DiseaseCube(BLACK) {} };

class CubePile abstract
{
protected:
	uint16_t m_CubesLeft;

public:
	CubePile() : m_CubesLeft(24) {}

	uint16_t CubesLeft() { return m_CubesLeft; }
	bool IsEmpty() { return (m_CubesLeft == 0); }
	virtual DiseaseCube* TakeCube() = 0;
	void PlaceCube(DiseaseCube* dc) { delete dc; m_CubesLeft += 1; }
};

class RedDiseaseCubePile final : public CubePile
{
public:
	RedDiseaseCubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new RedDiseaseCube(); }
};

class YellowDiseaseCubePile final : public CubePile
{
public:
	YellowDiseaseCubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new YellowDiseaseCube(); }
};

class BlueDiseaseCubePile final : public CubePile
{
public:
	BlueDiseaseCubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new BlueDiseaseCube(); }
};

class BlackDiseaseCubePile final : public CubePile
{
public:
	BlackDiseaseCubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new BlackDiseaseCube(); }
};

class DiseaseCubePile final
{
private:
	RedDiseaseCubePile m_Red;
	YellowDiseaseCubePile m_Yellow;
	BlueDiseaseCubePile m_Blue;
	BlackDiseaseCubePile m_Black;

public:
	DiseaseCubePile() {}

	//Prevent Copy/Assignment
	DiseaseCubePile(const DiseaseCubePile&) = delete;
	void operator=(const DiseaseCubePile&) = delete;

	bool IsAnyEmpty();
	DiseaseCube* TakeCube(const Color& color);
	void PlaceCube(DiseaseCube* dc);
};

// Cities -----------------------------------------------------------------------------------------
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

public:
	City(const CityID& id, const char* name) : m_CityID(id), m_Color(GetCityColor()), m_Name(name), m_NearBy(), m_Cubes() {}
	~City();

	//Prevent Copy/Assignment
	City(const City&) = delete;
	void operator=(const City&) = delete;

	void AddNearByCity(City* nearby) { m_NearBy.emplace_back(nearby); }
	
	uint16_t GetNumberOfCubes() { return (uint16_t)m_Cubes.size(); }
	uint16_t GetNumberOfCubes(const Color& color);
	void AddCube(DiseaseCube* cube) { if (cube == nullptr) { return; } m_Cubes.emplace_back(cube); }

	void RemoveCube() { m_Cubes.erase(m_Cubes.begin(), m_Cubes.begin() + 1); }
	void RemoveAllCubes() { m_Cubes.clear(); }

	Color GetCityColor();
	bool IsaRedCity() { return (m_CityID > RED_MIN) && (m_CityID < RED_MAX); }
	bool IsaYellowCity() { return (m_CityID > YELLOW_MIN) && (m_CityID < YELLOW_MAX); }
	bool IsaBlueCity() { return (m_CityID > BLUE_MIN) && (m_CityID < BLUE_MAX); }
	bool IsaBlackCity() { return (m_CityID > BLACK_MIN) && (m_CityID < BLACK_MAX); }

	CityID GetCityID() { return m_CityID; }
	bool CompareCityID(const uint64_t& id) { return (m_CityID == (CityID)id); }
	std::vector<City*> GetNearByCities() { return m_NearBy; }

	std::string GetCityName() { return m_Name; }

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

class ResearchStations final
{
private:
	std::vector<ResearchCenter> m_Stations;

protected:
	bool validate() { return (m_Stations.size() < 7); }

public:
	ResearchStations() : m_Stations() {};

	//Prevent Copy/Assignment
	ResearchStations(const ResearchStations&) = delete;
	void operator=(const ResearchStations&) = delete;

	uint16_t GetNumberOfCenters() { return (uint16_t)m_Stations.size(); }
	void AddStation(City* city) { if (validate()) m_Stations.emplace_back(ResearchCenter(city)); }
	void RemoveStation(const uint16_t& pos) { m_Stations.erase(m_Stations.begin() + pos); }
	std::vector<ResearchCenter> GetCenters() { return m_Stations; }
};

// Markers ----------------------------------------------------------------------------------------
class InfectionRate final
{
private:
	uint16_t m_position;
	const uint16_t m_array[7] = { 2, 2, 2, 3, 3, 4, 4 };

public:
	InfectionRate() : m_position(0) {}

	//Prevent Copy/Assignment
	InfectionRate(const InfectionRate&) = delete;
	void operator=(const InfectionRate&) = delete;

	uint16_t GetRate() { return m_array[m_position]; }
	void IncreaseRate() { m_position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_position); }
	void InputLoadedGame(const uint16_t& position) { m_position = position; }
};

class OutbreakMarker final
{
private:
	uint16_t m_position;
	const uint16_t m_array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

public:
	OutbreakMarker() : m_position(0) {}

	//Prevent Copy/Assignment
	OutbreakMarker(const OutbreakMarker&) = delete;
	void operator=(const OutbreakMarker&) = delete;

	uint16_t getMarker() { return m_array[m_position]; }
	void IncreaseRate() { m_position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_position); }
	void InputLoadedGame(const uint16_t& position) { m_position = position; }
};
