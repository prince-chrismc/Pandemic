/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

class GameEngine final
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
	InfectionLog m_Log;
	InfectionLogNotifier m_LogNotifier;
	PlayersContainer m_Players;
	std::vector<PlayerObserver*> m_PlayersObservers;
	IStatistics* m_GameStats;
	StatisticsNotify m_StatsNotify;
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

		/// Role Specials
		OPERATIONS_MOVE_FROM_RESEARCH_CENTER = 0xC00UL,
		CONTINGENCY_PLANNER_DRAW_EVENT,
		CONTINGENCY_PLANNER_USE_EVENT,
		DISPATCHER_MOVE_PAWN_TO_PAWN,

		/// Settings control
		SETTINGS_FREQ = 0xAAAUL,

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
				std::vector<CityList::CityID> CalculateBuildResearchCenterFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateDiscoverCureFor(const uint16_t& pos);
					Color DetermineCureColor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateOperationsExpertMoveFromCenterFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateContingencyPlannerExtraEventCardFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateDispatcherPawnToPawnFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateReseilientPopFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateAirliftFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateForecastFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateQuietNightFor(const uint16_t& pos);
				std::vector<CityList::CityID> CalculateGovernmentGrantFor(const uint16_t& pos);
			PlayerMoves DeterminePlayerMoves(const MovesPerCity& options);
			uint16_t ExecuteMove(const uint16_t& pos, const MoveOptions& opt, const CityList::CityID& cityID);
				uint16_t ExecuteQuit(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteChangeFrequency(const uint16_t& pos, const CityList::CityID& cityID);
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
					const Color ExecuteTreateDiseaseForCured(City* city, const Color& color);
				uint16_t ExecuteBuildResearchCenter(const uint16_t& pos, const CityList::CityID& cityID);
					void AddResearchCenter(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteShareKnowledge(const uint16_t& pos, const CityList::CityID& cityID);
					void ExecuteShareKnowledgeAsResearcher(const uint16_t& pos);
				uint16_t ExecuteCureDisease(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteOperationsExpertMoveToAnyCity(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecutePlannerDrawEventCard(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecutePlannerUseEventCard(const uint16_t& pos, const CityList::CityID& cityID);
				uint16_t ExecuteDispatcherPawnToPawn(const uint16_t& pos, const CityList::CityID& cityID);
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