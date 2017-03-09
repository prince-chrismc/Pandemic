///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Game Engine Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <mutex>
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

