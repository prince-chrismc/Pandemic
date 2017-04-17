///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Statistics Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Observers.h"

enum class Priority { INVALID = 0x00UL, MINOR = 0x10UL, ACTION = 0x21UL, PHASE = 0x26UL, TURN = 0x2CUL, MAJOR = 0xFFUL};

// Subjects -------------------------------------------------------------------------------------
class StatisticsObserver abstract : public  IObserver
{
public:
	StatisticsObserver() : IObserver(nullptr) {}
	virtual void Update(const Priority& p) = 0;
};

class StatisticsSubject abstract : public ISubject
{
public:
	void Notify(const Priority& p) { for each(StatisticsObserver* obv in m_observers) { if (obv == nullptr) continue; obv->Update(p); } }
};

class StatisticsNotify final : public StatisticsSubject {};

class PlayerStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual float GetAverageNumberOfCards() = 0;
};

class WorldMapStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual uint16_t GetNumberOfInfectedCities() = 0;
	virtual uint16_t GetNumberOfCubeOnBoard() = 0;
};

class ResearchStationsStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual uint16_t GetNumberOfUnusedCenters() = 0;
};

class PlayerDeckStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual uint16_t GetNumberOfCardRemaining() = 0;
};

class InfectionDeckStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual uint16_t GetNumberOfCardRemaining() = 0;
};

// Decorators -------------------------------------------------------------------------------------
class IGameStatsDecorator abstract
{
public:
	virtual bool IsPriorityHighEnough(const Priority& p) = 0;
};

class GameStatsPerAction final : public IGameStatsDecorator
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p >= Priority::ACTION; }
};

class GameStatsPerPhase final : public IGameStatsDecorator
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p >= Priority::PHASE; }
};

class GameStatsPerTurn final : public IGameStatsDecorator
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p >= Priority::TURN; }
};

// Observer 
class GameStatistics final : public StatisticsObserver
{
private:
	IGameStatsDecorator* m_Decorator;
	StatisticsSubject* m_Notifier; // main one that will call with varrying priorities
	StatisticsSubject* m_PlayersContainer;
	StatisticsSubject* m_WorldMap;
	StatisticsSubject* m_ResearchStations;
	StatisticsSubject* m_PlayerDeck;
	StatisticsSubject* m_InfectionDeck;

	void Print() { std::cout << GameStatistics::Statistics::Builder::GetInstance().InputCardsPerPlayer(dynamic_cast<PlayerStatisticsSubject*>(m_PlayersContainer)->GetAverageNumberOfCards()).InputCubesOnTheBoard(dynamic_cast<WorldMapStatisticsSubject*>(m_WorldMap)->GetNumberOfCubeOnBoard()).InputNumInfectedCities(dynamic_cast<WorldMapStatisticsSubject*>(m_WorldMap)->GetNumberOfInfectedCities()).InputResearchCentersNotUsed(dynamic_cast<ResearchStationsStatisticsSubject*>(m_ResearchStations)->GetNumberOfUnusedCenters()).InputPlayerCardsLeft(dynamic_cast<PlayerDeckStatisticsSubject*>(m_PlayerDeck)->GetNumberOfCardRemaining()).InputInfectionCardsLeft(dynamic_cast<InfectionDeckStatisticsSubject*>(m_InfectionDeck)->GetNumberOfCardRemaining()).GetStatistics().GetPrintOutput() << std::endl; }

public:
	class Statistics final
	{
	private:
		float    m_CardsPerPlayer;
		uint16_t m_NumInfectedCities;
		uint16_t m_CubesOnTheBoard;
		uint16_t m_ResearchCentersNotUsed;
		uint16_t m_PlayerCardsLeft;
		uint16_t m_InfectionCardsLeft;

	public:
		Statistics(float cardsper, uint16_t infectedcities, uint16_t cubesplaced, uint16_t rcunused, uint16_t pcardsleft, uint16_t icardsleft) : m_CardsPerPlayer(cardsper), m_NumInfectedCities(infectedcities), m_CubesOnTheBoard(cubesplaced), m_ResearchCentersNotUsed(rcunused), m_PlayerCardsLeft(pcardsleft), m_InfectionCardsLeft(icardsleft) {}
		std::string GetPrintOutput() { std::string result = "Game Statistics:\n - Cards/Player: " + std::to_string(m_CardsPerPlayer) + "\n - Number of Infected Cities: " + std::to_string(m_NumInfectedCities) + "\n - Number of cubes on the board: " + std::to_string(m_CubesOnTheBoard) + "\n - Reseach Stations Left to Play: " + std::to_string(m_ResearchCentersNotUsed) + "\n - Player Cards Left: " + std::to_string(m_PlayerCardsLeft) + "\n - Infection Cards Left: " + std::to_string(m_InfectionCardsLeft); }

		class Builder final
		{
		private:
			float    m_CardsPerPlayer;
			uint16_t m_NumInfectedCities;
			uint16_t m_CubesOnTheBoard;
			uint16_t m_ResearchCentersNotUsed;
			uint16_t m_PlayerCardsLeft;
			uint16_t m_InfectionCardsLeft;

			Builder() : m_CardsPerPlayer(0.0), m_NumInfectedCities(0), m_CubesOnTheBoard(0), m_ResearchCentersNotUsed(0), m_PlayerCardsLeft(0), m_InfectionCardsLeft(0) {}

		public:
			///Prevent Copy/Assignment
			Builder(const Builder&) = delete;
			void operator=(const Builder&) = delete;

			static Builder& GetInstance() { static Builder builder; return builder; }
			Builder& InputCardsPerPlayer(float cardsper) { m_CardsPerPlayer = cardsper; return *this; }
			Builder& InputNumInfectedCities(uint16_t infectedcities) { m_NumInfectedCities = infectedcities; return *this; }
			Builder& InputCubesOnTheBoard(uint16_t cubesplaced) { m_CubesOnTheBoard = cubesplaced; return *this; }
			Builder& InputResearchCentersNotUsed(uint16_t rcunused) { m_ResearchCentersNotUsed = rcunused; return *this; }
			Builder& InputPlayerCardsLeft(uint16_t pcardsleft) { m_PlayerCardsLeft = pcardsleft; return *this; }
			Builder& InputInfectionCardsLeft(uint16_t icardsleft) { m_InfectionCardsLeft = icardsleft; return *this; }
			
			Statistics GetStatistics() { return Statistics(m_CardsPerPlayer, m_NumInfectedCities, m_CubesOnTheBoard, m_ResearchCentersNotUsed, m_PlayerCardsLeft, m_InfectionCardsLeft); }
		};
	};

	GameStatistics(StatisticsSubject* playerscontainer, StatisticsSubject* worldmap, StatisticsSubject* stations, StatisticsSubject* playerdeck, StatisticsSubject* infectiondeck, StatisticsSubject* notifier) : m_PlayersContainer(playerscontainer), m_WorldMap(worldmap), m_ResearchStations(stations), m_PlayerDeck(playerdeck), m_InfectionDeck(infectiondeck), m_Notifier(notifier), m_Decorator(nullptr) {}
	~GameStatistics() { if (m_Decorator != nullptr) delete m_Decorator; }

	void ChangeFrequency(IGameStatsDecorator* deco) { if (m_Decorator != nullptr) delete m_Decorator; m_Decorator = deco; }

	void Update(const Priority& p) { if(m_Decorator != nullptr) if (m_Decorator->IsPriorityHighEnough(p)) Print(); }
};
