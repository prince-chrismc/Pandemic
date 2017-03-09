#include <sstream>
#include <iostream> //io
#include <ctime> //time
#include "boost\filesystem.hpp" //dir
#include "GameEngine.h"

GameEngine::~GameEngine()
{
	for (size_t pos = 0; pos < m_Players.size(); pos += 1)
	{
		if (m_Players.at(pos) != nullptr)
		{
			delete m_Players.at(pos);
			m_Players.at(pos) = nullptr;
		}
	}
	m_Players.clear();
}

std::string GameEngine::MakeFileName()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::string filename = "bin/Pandemic-";
	filename += std::to_string(now->tm_year + 1900);
	if (now->tm_mon + 1 < 10) filename += "0";
	filename += std::to_string(now->tm_mon + 1);
	if (now->tm_mday < 10) filename += "0";
	filename += std::to_string(now->tm_mday);
	filename += "-";
	filename += std::to_string(now->tm_hour);
	filename += std::to_string(now->tm_min);
	filename += std::to_string(now->tm_sec);
	filename += ".txt";

	return filename;
}

void GameEngine::RegisterPlayer(const std::string & newPlayerName)
{
	m_Players.emplace_back(new Player(newPlayerName, m_Board.m_RoleDeck.DrawCard()));
}

void GameEngine::PlayersSetup()
{
	std::string input;
	int num;
	do
	{
		std::cout << "How Many Players will be playing? (2-4) ";
		std::getline(std::cin, input);
		std::stringstream ss(input);
		ss >> num;
		if (num >= 2 && num <= 4) 
			break;
		else 
			std::cout << "Invalid input. Try again..." << std::endl;
	} while (num < 2 || num > 4);

	input = "";
	for (int i = 0; i < num; i += 1)
	{
		std::cout << "Welcome Player " << i + 1 << " Enter your name: ";
		std::getline(std::cin, input);
		input.erase(std::remove_if(input.begin(), input.end(), [](const unsigned &c) { return !isspace(c) && !isalpha(c); }));
		
		std::string name = input.substr(0, 10);
		RegisterPlayer(name);
	}

	for each(Player* joeur in m_Players)
	{
		switch (m_Players.size())
		{
		case 2:
			joeur->addCard(m_Board.DrawPlayerCard());
		case 3:
			joeur->addCard(m_Board.DrawPlayerCard());
		case 4:
			joeur->addCard(m_Board.DrawPlayerCard());
			joeur->addCard(m_Board.DrawPlayerCard());
		default:
			break;
		}
	}
}

void GameEngine::DifficultySetup()
{
	std::string input;
	int dif;
	std::cout << "1. Easy 2. Medium 3. Hard\nChoose your difficulty... ";
	std::getline(std::cin, input);
	std::stringstream ss(input);
	ss >> dif;

	m_Board.m_PlayerDeck.IncreaseDifficulty((Difficulty)dif);
}

void GameEngine::BoardSetup()
{
	m_Board.InfectCity(3);
	m_Board.InfectCity(3);
	m_Board.InfectCity(3);
	m_Board.InfectCity(2);
	m_Board.InfectCity(2);
	m_Board.InfectCity(2);
	m_Board.InfectCity();
	m_Board.InfectCity();
	m_Board.InfectCity();

	m_Board.AddResearchCenter(City::ATLANTA);
}

void GameEngine::SaveGame()
{
	// Get Timestamp ------------------------------------------------------------------------------
	std::string filename = MakeFileName();

	// Create File --------------------------------------------------------------------------------
	std::ofstream myfile;
	myfile.open(filename);
	myfile << filename << "\n";

	// Infection Cards ----------------------------------------------------------------------------
	myfile << m_Board.m_InfecDeck.GetSaveOutput();
	myfile << "\n";

	// Player Cards -------------------------------------------------------------------------------
	myfile << m_Board.m_PlayerDeck.GetSaveOutput();
	myfile << "\n";

	// Role Cards ---------------------------------------------------------------------------------
	myfile << m_Board.m_RoleDeck.GetSaveOutput();
	myfile << "\n";

	// Cities -------------------------------------------------------------------------------------
	myfile << m_Board.m_Map.GetSaveOutput();
	myfile << "\n";

	// Players ------------------------------------------------------------------------------------
	for each (Player* play in m_Players)
	{
		myfile << play->GetSaveOutput();
		myfile << " / ";
	}

	// Cures --------------------------------------------------------------------------------------
	myfile << m_Board.m_Cures.GetSaveOutput();
	myfile << "\n";

	// Cubes ---------------------------- Is done by adding them to cities -----------------------
	//myfile << m_cubepiles.PrintCubesLeft();
	//myfile << "\n";

	// Infection Rate -----------------------------------------------------------------------------
	myfile << m_Board.m_InfectRate.GetSaveOutput();
	myfile << "\n";

	// Outbreak Marker ----------------------------------------------------------------------------
	myfile << m_Board.m_OutBreak.GetSaveOutput();
	myfile << "\n";

	myfile.close();
}

void GameEngine::LoadGame()
{
	/* TODO: Implement */
}

void GameEngine::Initialize()
{
	PlayersSetup();
	DifficultySetup();
	BoardSetup();

	m_PreGameComplete.unlock();
}

void GameEngine::Launch()
{
	/* TODO: Implement */
	if (!m_PreGameComplete.try_lock())
	{
		std::cout << "Game Not Initialized" << std::endl; 
		return;
	}

	while (true) /* needs validate game still alive funct */
	{
		for (int i = 0; i < (int)m_Players.size(); i += 1)
		{
			Player* joeur = m_Players.at(i);
			joeur->getCityID();
		}
	}


}
