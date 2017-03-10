///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Engine Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <mutex>
#include <map>
#include "Board.h"
#include "Player.h"

class GameEngine final
{
private:
	Board m_Board;
	std::vector<Player*> m_Players;
	std::mutex m_PreGameComplete;

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
			TODO: MORE TO COME
		*/

		MAX = 0xFFFUL
	};
	typedef std::multimap<MoveOptions, City::CityID> MovesPerCity;
	typedef std::map<int, std::pair<const MoveOptions, CityList::CityID>> PlayerMoves;

	void TurnSequence(const uint16_t & pos);
	MovesPerCity CalculatePlayerOpt(const uint16_t& pos);
	std::vector<CityList::CityID> GetDriveCitiesFor(const uint16_t pos);
	std::vector<CityList::CityID> GetFlightCitiesFor(const uint16_t pos);
	std::vector<CityList::CityID> GetCharterFlightsFor(const uint16_t pos);
	std::vector<CityList::CityID> GetShuttleFlightsFor(const uint16_t pos);
	std::vector<CityList::CityID> ShareKnowlegdeFor(const uint16_t pos);
	std::vector<CityList::CityID> DiscoverCure(const uint16_t pos);
	PlayerMoves DeterminePlayerMoves(const MovesPerCity& options);
	static std::string MoveOpToString(const MoveOptions& opt);
	void ExecuteMove(const uint16_t pos, const MoveOptions& opt, const CityList::CityID& cityID);

public:
	GameEngine() : m_Board(), m_Players(), m_PreGameComplete() { m_PreGameComplete.lock(); }
	~GameEngine();
	
	void SaveGame();
	void LoadGame();

	void Initialize();
	void Launch();

	// Temp fuction for game play
	Player* GetPlayer(const uint8_t pos) { return m_Players.at(pos); }

};

