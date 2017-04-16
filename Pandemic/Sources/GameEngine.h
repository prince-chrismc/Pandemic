///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Engine Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include "Board.h"
#include "Player.h"
#include "InfectionLog.h"

class GameEngine final : private ISubject
{
public:
	GameEngine();
	~GameEngine();

	void Initialize();
	void Launch();

	///Prevent Copy/Assignment
	GameEngine(const GameEngine&) = delete;
	void operator=(const GameEngine&) = delete;

private:
	Board m_Board;
	InfectionLog* m_Log;
	std::vector<Player*> m_Players;
	std::vector<PlayerObserver*> m_PlayersObservers;
	std::string m_Filename;
	bool m_PreGameComplete;
	bool m_SkipNextInfectionPhase;
	uint16_t m_TurnCounter;

protected:
	std::string MakeFileName(); 

	/// game initialization
	void RegisterPlayer(const std::string& newPlayerName);
	void PlayersSetup();
	void DifficultySetup();
	void BoardSetup();
	
	void SaveGame();
	void LoadGame();

	/// Subject to the InfectionLog
	void Notify(std::string name, uint16_t cubes = 1);

	// game play ----------------------------------------------------------------------------------
	enum MoveOptions
	{
		/// game actions
		INVALID = 0x000UL,
		DRIVE_FERRY = 0x001UL,
		FLIGHT = 0x002UL,
		CHARTER = 0x003UL,
		SHUTTLE = 0x004UL,
		TREATDISEASE = 0x005,
		BUILDRC = 0x006UL,
		SHARECARD = 0x007UL,
		CUREDISEASE = 0x008UL,

		/// Event cards
		RESILLIENT = 0x200UL,
		AIRLIFT = 0x201UL,
		FORECAST = 0x202UL,
		QUIETNIGHT = 0x203UL,
		GOVTGRANT = 0x204UL,

		/// basics
		QUIT = 0x0F0UL,
		REFCARD = 0x0A0UL,
		PEAK_PLAYER_DISCARD,
		PEAK_INFECTION_DISCARD,
		/*

			CONTIN_PLANNER_DRAW_EVENT,
			DISPATCH_MOVE_OTHERS_PAWN,
			OPERATIONS_BUILD_RESEARCH_CENTER,
			OPERATIONS_MOVE_FROM_RESEARCH_CENTER,

			TODO: MORE TO COME
		*/

		MAX = 0xFFFUL
	};

	// Game Play Functions ------------------------------------------------------------------------
	typedef std::multimap<MoveOptions, City::CityID> MovesPerCity;
	typedef std::map<uint16_t, std::pair<const MoveOptions, CityList::CityID>> PlayerMoves;

	void TurnSequence(const uint16_t& pos);
		const uint16_t GetUserInput(const uint16_t& lower, const uint16_t& upper);
		void TurnActionsPhase(const uint16_t& pos);
			MovesPerCity CalculatePlayerOpt(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateDriveCitiesFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateFlightCitiesFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateCharterFlightsFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateShuttleFlightsFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateShareKnowlegdeFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateDiscoverCureFor(const uint16_t& pos);
					Color DetermineCureColor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateReseilientPopFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateAirliftFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateForecastFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateQuietNightFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateGovernmentGrantFor(const uint16_t& pos);
			PlayerMoves DeterminePlayerMoves(const MovesPerCity& options);
			uint16_t ExecuteMove(const uint16_t& pos, const MoveOptions& opt, const CityList::CityID& cityID);
				uint16_t ExecuteQuit(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteViewRefCard(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecutePeakInfectionDiscard(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecutePeakPlayerDiscard(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteDriveFerry(const uint16_t& pos, const CityList::CityID& cityID);
					void ExecuteMedicEnteredCity(const CityList::CityID& cityID);
				uint16_t ExecuteDirectFlight(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteCharterFlight(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteShuttleFlight(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteTreateDisease(const uint16_t& pos, const CityList::CityID& cityID);
					const Color ExecuteTreateDiseaseAsMedic(City* city);
				uint16_t ExecuteBuildResearchCenter(const uint16_t& pos, const CityList::CityID& cityID);
					void AddResearchCenter(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteShareKnowledge(const uint16_t& pos, const CityList::CityID& cityID);
					void ExecuteShareKnowledgeAsResearcher(const uint16_t& pos);
				uint16_t ExecuteCureDisease(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteAirLift(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteResillentPopulation(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteForecast(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteQuietNight(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteGovernmentGrant(const uint16_t& pos, const CityList::CityID& cityID);
				void CheckIfGameOver();
				void CheckIfGameWon();
		void TurnDrawPhase(const uint16_t& pos);
		void TurnInfectPhase();
			void InfectCity(const uint16_t& cubesToAdd = 1);
			bool IsQuarentineSpecialistNearBy(City* city);
			void Outbreak(City* city, std::vector<City*> skip = std::vector<City*>());
			void Epidemic();
	// Game Play Functions ------------------------------------------------------------------------
};

class GameOverException final : public GameException 
{
public:
	GameOverException(const std::string& reason) : GameException(reason) {}
};

class GameWonException final : public GameException
{
public:
	GameWonException(const std::string& reason) : GameException(reason) {}
};

class GameQuitException final : public GameException
{
public:
	GameQuitException() : GameException("Thank you for playing, come back soon!") {}
};