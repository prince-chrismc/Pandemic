///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Engine Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include <exception>
#include "Board.h"
#include "Player.h"
#include "InfectionLog.h"

class GameOverException final : public std::exception {};

class GameEngine final
{
private:
	Board m_Board;
	InfectionLog m_Log;
	std::vector<Player*> m_Players;
	bool m_PreGameComplete;

protected:
	std::string MakeFileName(); // used in save

	// game initialization
	void RegisterPlayer(const std::string& newPlayerName);
	void PlayersSetup();
	void DifficultySetup();
	void BoardSetup();

	// game play
	enum MoveOptions
	{
		INVALID = 0x000UL,
		DRIVE_FERRY = 0x001UL,
		FLIGHT = 0x002UL,
		CHARTER = 0x003UL,
		SHUTTLE = 0x004UL,
		TREATDISEASE = 0x005,
		BUILDRC = 0x006UL,
		SHARECARD = 0x007UL,
		CUREDISEASE = 0x008UL,

		/*
			QUIT = 0x0F0UL,
			REFCARD = 0x0A0UL,
			
			PEAK_PLAYER_DISCARD,
			PEAK_INFECTION_DISCARD,

			CONTIN_PLANNER_DRAW_EVENT,
			DISPATCH_MOVE_OTHERS_PAWN,
			OPERATIONS_BUILD_RESEARCH_CENTER,
			OPERATIONS_MOVE FROM_RESEARCH_CENTER,

			TODO: MORE TO COME
		*/

		MAX = 0xFFFUL
	};
	typedef std::multimap<MoveOptions, City::CityID> MovesPerCity;
	typedef std::map<uint16_t, std::pair<const MoveOptions, CityList::CityID>> PlayerMoves;

	void TurnSequence(const uint16_t& pos);
	void TurnActionsPhase(const uint16_t& pos);
	void TurnDrawPhase(const uint16_t& pos);
	void TurnInfectPhase();
	void InfectCity(const uint16_t& cubesToAdd = 1);
	bool IsQuarentineSpecialistNearBy(City* city);
	void Outbreak(City* city);
	void Epidemic();
	MovesPerCity CalculatePlayerOpt(const uint16_t& pos);
	std::vector<CityList::CityID> GetDriveCitiesFor(const uint16_t& pos);
	std::vector<CityList::CityID> GetFlightCitiesFor(const uint16_t& pos);
	std::vector<CityList::CityID> GetCharterFlightsFor(const uint16_t& pos);
	std::vector<CityList::CityID> GetShuttleFlightsFor(const uint16_t& pos);
	std::vector<CityList::CityID> ShareKnowlegdeFor(const uint16_t& pos);
	std::vector<CityList::CityID> DiscoverCure(const uint16_t& pos);
	Color DetermineCureColor(const uint16_t& pos);
	PlayerMoves DeterminePlayerMoves(const MovesPerCity& options);
	static std::string MoveOpToString(const MoveOptions& opt);
	void ExecuteMove(const uint16_t& pos, const MoveOptions& opt, const CityList::CityID& cityID);
	void AddResearchCenter(const CityList::CityID& id);
	void CheckIfGameOver();


public:
	GameEngine() : m_Board(), m_Players(), m_PreGameComplete(false) {}
	~GameEngine();

	void SaveGame();
	void LoadGame();

	void Initialize();
	void Launch();
};

