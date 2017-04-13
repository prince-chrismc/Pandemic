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

	virtual void Update() = 0;
};

class ISubject
{
protected:
	std::vector<IObserver*> m_observers;

public:
	ISubject() : m_observers() {}

	void RegistarObserver(IObserver* obv) { m_observers.emplace_back(obv); }
	virtual void Notify() { for each(IObserver* obv in m_observers) { if (obv == nullptr) continue; obv->Update(); } }
};

// Player -----------------------------------------------------------------------------------------
class PlayerSubject : public ISubject
{
public:
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
	void Update() { std::cout << dynamic_cast<PlayerSubject*>(m_Subject)->GetCharacteristics().GetPrintOutput() << std::endl; }
};

// World --------------------------------------------------------------------------------------------
class MapSubject : public ISubject
{
public:
	virtual City* GetCityWithID(const uint64_t& id) = 0;
};

class StationsSubject : public ISubject
{
public:
	virtual bool IsaCenterIn(const uint64_t& id) = 0;
};

class WorldObserver : public IObserver
{
private:
	ISubject* m_MapSub;
	ISubject* m_StationsSub;
public:
	WorldObserver(ISubject* stations, ISubject* map) : IObserver(nullptr), m_StationsSub(stations), m_MapSub(map) {}
	void Update();
};