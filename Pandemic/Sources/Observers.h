///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Observer Pattern Interface Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include"Tokens.h"

// Basic Interfaces -------------------------------------------------------------------------------
class ISubject;

class IObserver
{
protected:
	ISubject* m_Subject;

public:
	IObserver(ISubject* sub) : m_Subject(sub) {}

	///Prevent Copy/Assignment
	IObserver(const IObserver&) = delete;
	void operator=(const IObserver&) = delete;

	virtual void Update() = 0;
};

class ISubject
{
protected:
	std::vector<IObserver*> m_observers;

public:
	ISubject() : m_observers() {}

	///Prevent Copy/Assignment
	ISubject(const ISubject&) = delete;
	void operator=(const ISubject&) = delete;

	void RegistarObserver(IObserver* obv) { m_observers.emplace_back(obv); }
	virtual void Notify() { for each(IObserver* obv in m_observers) { if (obv == nullptr) continue; obv->Update(); } }
};

// Player -----------------------------------------------------------------------------------------
class PlayerSubject : public ISubject
{
public:
	PlayerSubject() : ISubject() {}
	///Prevent Copy/Assignment
	PlayerSubject(const PlayerSubject&) = delete;
	void operator=(const PlayerSubject&) = delete;

	struct PlayerCharacteristics
	{
		std::string m_Name;
		std::string m_PawnColor;
		std::string m_Role;
		std::string m_CityName;
		std::vector<std::string> m_CardInfos;

		PlayerCharacteristics(std::string name, std::string pawnColor, std::string role, std::string cityname, std::vector<std::string> cardNames) : m_Name(name), m_PawnColor(pawnColor), m_Role(role), m_CityName(cityname), m_CardInfos(cardNames) {}
		std::string GetPrintOutput() { std::string result = "Player: " + m_Name + " (" + m_Role + " - " + m_PawnColor + ") is in " + m_CityName + ". Holding:\n"; uint16_t counter = 0; for each(std::string info in m_CardInfos) { result += std::to_string(counter++) + ": " + info + "\n"; } return result; }
	};

	virtual PlayerCharacteristics GetCharacteristics() = 0;
};

class PlayerObserver : public IObserver
{
public:
	PlayerObserver(ISubject* sub) : IObserver(sub) {}

	///Prevent Copy/Assignment
	PlayerObserver(const PlayerObserver&) = delete;
	void operator=(const PlayerObserver&) = delete;

	void Update() { std::cout << dynamic_cast<PlayerSubject*>(m_Subject)->GetCharacteristics().GetPrintOutput() << std::endl; }
};

// World --------------------------------------------------------------------------------------------
class MapSubject : public ISubject
{
public:
	MapSubject() : ISubject() {}
	///Prevent Copy/Assignment
	MapSubject(const MapSubject&) = delete;
	void operator=(const MapSubject&) = delete;

	virtual City* GetCityWithID(const uint64_t& id) = 0;
};

class StationsSubject : public ISubject
{
public:
	StationsSubject() : ISubject() {}
	///Prevent Copy/Assignment
	StationsSubject(const StationsSubject&) = delete;
	void operator=(const StationsSubject&) = delete;

	virtual bool IsaCenterIn(const uint64_t& id) = 0;
};

class WorldObserver : public IObserver
{
private:
	ISubject* m_MapSub;
	ISubject* m_StationsSub;
public:
	WorldObserver(ISubject* stations, ISubject* map) : IObserver(nullptr), m_StationsSub(stations), m_MapSub(map) {}

	///Prevent Copy/Assignment
	WorldObserver(const WorldObserver&) = delete;
	void operator=(const WorldObserver&) = delete;

	void Update();
};