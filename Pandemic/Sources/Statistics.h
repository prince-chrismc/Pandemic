///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Statistics Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <ctime>

enum class Priority { INVALID = 0x00UL, MINOR = 0x10UL, ACTION = 0x21UL, PHASE = 0x26UL, TURN = 0x2CUL, MAJOR = 0xFFUL};

// Observers --------------------------------------------------------------------------------------
class StatisticsObserver abstract
{
public:
	virtual bool Update(const Priority& p) = 0;
};

class StatisticsSubject
{
protected:
	std::vector<StatisticsObserver*> m_Observers;

public:
	StatisticsSubject() : m_Observers() {}
	void Notify(const Priority& p) { for each(StatisticsObserver* obv in m_Observers) { if (obv == nullptr) continue; obv->Update(p); } }
	virtual void RegistarObserver(StatisticsObserver* obv) { m_Observers.emplace_back(obv); }
};

class StatisticsNotify final : public StatisticsSubject 
{
public:
	StatisticsNotify() : StatisticsSubject() {}
};

class PlayerStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual float GetAverageNumberOfCards() = 0;
	virtual uint16_t GetNumberOfPlayers() = 0;
};

class WorldMapStatisticsSubject abstract : public StatisticsSubject
{
public:
	virtual uint16_t GetNumberOfInfectedCities() = 0;
	virtual uint16_t GetNumberOfCubeOnBoard() = 0;
};

class ResearchStatisticsSubject abstract : public StatisticsSubject
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

// Display Settings -------------------------------------------------------------------------------
class IGameStatsDisplay abstract
{
public:
	virtual bool IsPriorityHighEnough(const Priority& p) = 0;
};

class GameStatsPerAction final : public IGameStatsDisplay
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p == Priority::ACTION; }
};

class GameStatsPerPhase final : public IGameStatsDisplay
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p == Priority::PHASE; }
};

class GameStatsPerTurn final : public IGameStatsDisplay
{
public:
	bool IsPriorityHighEnough(const Priority& p) { return p == Priority::TURN; }
};

// Decorator --------------------------------------------------------------------------------------
/// basid decorator interface
class IStatistics abstract : public StatisticsObserver
{
public:
	virtual bool Print() = 0;
	virtual void ChangeFrequency(IGameStatsDisplay* deco) = 0;
};

/// main object
class GameStatistics final : public IStatistics
{
private:
	IGameStatsDisplay* m_Display;
	StatisticsSubject* m_Notifier; // main one that will call with varrying priorities
	StatisticsSubject* m_PlayersContainer;
	StatisticsSubject* m_WorldMap;
	StatisticsSubject* m_ResearchStations;
	StatisticsSubject* m_PlayerDeck;
	StatisticsSubject* m_InfectionDeck;

protected:
	virtual bool Print();

public:
	class Statistics
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

		std::string GetPrintOutput() { return "Game Statistics:\n - Cards/Player: " + std::to_string(m_CardsPerPlayer) + "\n - Number of Infected Cities: " + std::to_string(m_NumInfectedCities) + "\n - Number of cubes on the board: " + std::to_string(m_CubesOnTheBoard) + "\n - Reseach Stations Left to Play: " + std::to_string(m_ResearchCentersNotUsed) + "\n - Player Cards Left: " + std::to_string(m_PlayerCardsLeft) + "\n - Infection Cards Left: " + std::to_string(m_InfectionCardsLeft); }

		class Builder
		{
		private:
			float    m_CardsPerPlayer;
			uint16_t m_NumInfectedCities;
			uint16_t m_CubesOnTheBoard;
			uint16_t m_ResearchCentersNotUsed;
			uint16_t m_PlayerCardsLeft;
			uint16_t m_InfectionCardsLeft;

		protected:
			Builder() : m_CardsPerPlayer(0.0f), m_NumInfectedCities(0), m_CubesOnTheBoard(0), m_ResearchCentersNotUsed(0), m_PlayerCardsLeft(0), m_InfectionCardsLeft(0) {}

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

	GameStatistics(StatisticsSubject* playerscontainer, StatisticsSubject* worldmap, StatisticsSubject* stations, StatisticsSubject* playerdeck, StatisticsSubject* infectiondeck, StatisticsSubject* notifier, IGameStatsDisplay* display) : m_PlayersContainer(playerscontainer), m_WorldMap(worldmap), m_ResearchStations(stations), m_PlayerDeck(playerdeck), m_InfectionDeck(infectiondeck), m_Notifier(notifier), m_Display(display) {}
	~GameStatistics() { if (m_Display != nullptr) delete m_Display; }

	///Prevent Copy/Assignment
	GameStatistics(const GameStatistics&) = delete;
	void operator=(const GameStatistics&) = delete;

	void ChangeFrequency(IGameStatsDisplay* deco);
	uint16_t GetNumberOfInfectedCities() { return dynamic_cast<WorldMapStatisticsSubject*>(m_WorldMap)->GetNumberOfInfectedCities(); }

	bool Update(const Priority& p) { if (m_Display != nullptr) if (m_Display->IsPriorityHighEnough(p)) return Print(); return false; }
};


class GameStatisticsDecorator : public IStatistics
{
protected:
	IStatistics* m_Stats;

public:
	GameStatisticsDecorator(IStatistics* stats) : m_Stats(stats) {}

	virtual bool Print() = 0;
	bool Update(const Priority& p) { if (m_Stats->Update(p)) return Print(); return false; }
	void ChangeFrequency(IGameStatsDisplay* deco) { m_Stats->ChangeFrequency(deco); }
};

class GameStatisticsExtended : public GameStatisticsDecorator
{
public:
	GameStatisticsExtended(IStatistics* stats) : GameStatisticsDecorator(stats) {}

	class Statistics
	{
	private:
		float m_InfectedCitiesPercentage;

	public:
		Statistics(uint16_t infectedcities) : m_InfectedCitiesPercentage(infectedcities / (float)48.0 * (float)100.0) {}

		std::string GetPrintOutput() { return "\n - Percent of cities infected: " + std::to_string(m_InfectedCitiesPercentage); }
		
		class Builder
		{
		private:
			uint16_t m_NumInfectedCities;

			Builder() : m_NumInfectedCities(0) {}

		public:
			///Prevent Copy/Assignment
			Builder(const Builder&) = delete;
			void operator=(const Builder&) = delete;

			static Builder& GetInstance() { static Builder builder; return builder; }

			Builder& InputNumInfectedCities(uint16_t infectedcities) { m_NumInfectedCities = infectedcities; return *this; }

			Statistics GetStatistics() { return Statistics(m_NumInfectedCities); }
		};
	};

	bool Print();
};

class GameStatisticsClocked : public GameStatisticsDecorator
{
private:
	const clock_t m_CurrentSessionStartTime = clock();
public:
	GameStatisticsClocked(IStatistics* stats) : GameStatisticsDecorator(stats) {}

	std::string GetPrintOutput();

	bool Print();
};