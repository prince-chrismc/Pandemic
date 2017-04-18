///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Wold Map Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Observers.h"
#include "Statistics.h"

class WorldMap final : public virtual MapSubject, public virtual WorldMapStatisticsSubject //The Connected Cities
{
private:
	std::vector<City*> m_Cities;
	bool m_Costumized;

	City* GetCityWithID(const uint64_t& id) { return GetCityWithID((City::CityID)id); }

public:
	WorldMap();
	~WorldMap();

	void UserDriverCostumization();
	bool Validate();

	///Prevent Copy/Assignment
	WorldMap(const WorldMap&) = delete;
	void operator=(const WorldMap&) = delete;
	
	City* GetCityWithID(const City::CityID& id);
	std::vector<City*> GetCitiesConnectedTo(const City::CityID& id);
	std::vector<City*> GetAllCities() { return m_Cities; }
	
	std::string GetSaveOutput();

	uint16_t GetNumberOfInfectedCities();
	uint16_t GetNumberOfCubeOnBoard();
};

/// This class was moved here due to header dependencies with observes and tockens
class ResearchStations final : public virtual StationsSubject, public virtual ResearchStatisticsSubject
{
private:
	std::vector<ResearchCenter> m_Stations;

protected:
	bool validate() { return (m_Stations.size() < 7); }

public:
	ResearchStations() : m_Stations() {};

	///Prevent Copy/Assignment
	ResearchStations(const ResearchStations&) = delete;
	void operator=(const ResearchStations&) = delete;

	uint16_t GetNumberOfCenters() { return (uint16_t)m_Stations.size(); }
	void AddStation(City* city) { if (validate()) { m_Stations.emplace_back(ResearchCenter(city)); StationsSubject::Notify(); ResearchStatisticsSubject::Notify(Priority::MINOR); } }
	void RemoveStation(const uint16_t& pos) { m_Stations.erase(m_Stations.begin() + pos); StationsSubject::Notify(); ResearchStatisticsSubject::Notify(Priority::MINOR); }
	bool IsaCenterIn(const uint64_t& id);
	uint16_t GetNumberOfUnusedCenters() { return uint16_t(6 - m_Stations.size()); }
	std::vector<ResearchCenter> GetAllCenters() { return m_Stations; }

	std::string GetSaveOutput();
	void InputLoadedGame(std::vector<ResearchCenter> stations) { m_Stations = stations; }
};
