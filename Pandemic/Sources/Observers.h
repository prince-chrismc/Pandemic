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
	std::vector<IObserver*> m_Observers;

public:
	ISubject() : m_Observers() {}

	///Prevent Copy/Assignment
	ISubject(const ISubject&) = delete;
	void operator=(const ISubject&) = delete;

	void RegistarObserver(IObserver* obv) { m_Observers.emplace_back(obv); }
	virtual void Notify() { for each(IObserver* obv in m_Observers) { if (obv == nullptr) continue; obv->Update(); } }
};

// Player -----------------------------------------------------------------------------------------
class PlayerSubject abstract : public ISubject
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

class PlayerObserver final : public IObserver
{
public:
	PlayerObserver(ISubject* sub) : IObserver(sub) {}

	///Prevent Copy/Assignment
	PlayerObserver(const PlayerObserver&) = delete;
	void operator=(const PlayerObserver&) = delete;

	void Update() { std::cout << dynamic_cast<PlayerSubject*>(m_Subject)->GetCharacteristics().GetPrintOutput() << std::endl; }
};

// World --------------------------------------------------------------------------------------------
class MapSubject abstract : public ISubject
{
public:
	virtual City* GetCityWithID(const uint64_t& id) = 0;
};

class StationsSubject abstract : public ISubject
{
public:
	virtual bool IsaCenterIn(const uint64_t& id) = 0;
};

class WorldObserver final : public IObserver
{
private:
	ISubject* m_MapSub;
	ISubject* m_StationsSub;
	bool m_PreventUpdateDueToCostumeMap;
public:
	WorldObserver(StationsSubject* stations, MapSubject* map) : IObserver(nullptr), m_StationsSub(stations), m_MapSub(map), m_PreventUpdateDueToCostumeMap(false) {}

	///Prevent Copy/Assignment
	WorldObserver(const WorldObserver&) = delete;
	void operator=(const WorldObserver&) = delete;

	void Update();
	void PreventUpdate(bool prevent) { m_PreventUpdateDueToCostumeMap = prevent; }
};

// Cure -------------------------------------------------------------------------------------------
class CureSubject abstract : public ISubject
{
public:
	virtual bool IsCured(const Color& color) = 0;
	virtual bool IsEradicated(const Color& color) = 0;
};

class CureObserver final : public IObserver
{
public:
	CureObserver(ISubject* sub) : IObserver(sub) {}

	///Prevent Copy/Assignment
	CureObserver(const CureObserver&) = delete;
	void operator=(const CureObserver&) = delete;

	void Update();
};
