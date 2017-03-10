#include <sstream>  //std::stringstream
#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include <iostream> //io
#include <ctime> //time
#include "boost\filesystem.hpp" //dir
#include "GameEngine.h"

GameEngine::~GameEngine()
{
	m_PreGameComplete.unlock();

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

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Players.begin(), m_Players.end(), g);

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


void GameEngine::TurnSequence(const uint16_t & pos)
{
	PlayerOpt options = CalculatePlayerOpt(pos);

	for each(std::pair<MoveOptions, City::CityID> pair in options)
	{
		std::cout << pair.first << " / " << pair.second << std::endl;
	}
}

GameEngine::PlayerOpt GameEngine::CalculatePlayerOpt(const uint16_t & pos)
{
	PlayerOpt options;

	// Drive --------------------------------------------------------------------------------------
	for each(City* city in GetDriveCitiesFor(pos))
	{
		options.insert(std::make_pair(GameEngine::DRIVE_FERRY, city->getCityID()));
	}

	// Flight --------------------------------------------------------------------------------------
	for each(CityList::CityID id in GetFlightCitiesFor(pos))
	{
		options.insert(std::make_pair(GameEngine::FLIGHT, id));
	}

	// Charter ------------------------------------------------------------------------------------
	for each(CityList::CityID id in GetCharterFlightsFor(pos))
	{
		options.insert(std::make_pair(GameEngine::CHARTER, id));
	}

	// Shuttle ------------------------------------------------------------------------------------
	for each(CityList::CityID id in GetShuttleFlightsFor(pos))
	{
		options.insert(std::make_pair(GameEngine::SHUTTLE, id));
	}

	// Treat Diesease -----------------------------------------------------------------------------
	if (m_Board.m_Map.getCityWithID(m_Players.at(pos)->getCityID())->GetNumberOfCubes() > 0)
	{
		options.insert(std::make_pair(GameEngine::TREATDISEASE, m_Players.at(pos)->getCityID()));
	}

	// Build Research Center ----------------------------------------------------------------------
	if (m_Players.at(pos)->hasCurrentCityCard())
	{
		options.insert(std::make_pair(GameEngine::BUILDRC, m_Players.at(pos)->getCityID()));
	}

	// Share Knowledge --------–-------------------------------------------------------------------
	for each(CityList::CityID id in ShareKnowlegdeFor(pos))
	{
		options.insert(std::make_pair(GameEngine::SHARECARD, id));
	}

	// Discover Cure ------------------------------------------------------------------------------
	for each(CityList::CityID id in DiscoverCure(pos))
	{
		options.insert(std::make_pair(GameEngine::CUREDISEASE, id));
	}

	return options;
}

std::vector<CityList::CityID> GameEngine::GetFlightCitiesFor(const uint16_t pos)
{
	std::vector<CityList::CityID> result;
	for each (PlayerCard* pc in m_Players.at(pos)->m_hand)
	{
		if (PlayerCardFactory::IsaCityCard(pc->getNumID()))
		{
			result.emplace_back((CityList::CityID)(pc->getNumID() - CityCard::CITYCARD_MIN));
		}
	}
	return result;
}

std::vector<CityList::CityID> GameEngine::GetCharterFlightsFor(const uint16_t pos)
{
	std::vector<CityList::CityID> result;
	if (m_Players.at(pos)->hasCurrentCityCard())
	{
		for each (City* city in m_Board.m_Map.getAllCities())
		{
			if (city->getCityID() == m_Players.at(pos)->getCityID())
				continue;

			result.emplace_back(city->getCityID());
		}
	}
	return result;
}

std::vector<CityList::CityID> GameEngine::GetShuttleFlightsFor(const uint16_t pos)
{
	bool IsInACityWithAResearchCEnter = false;
	std::vector<CityList::CityID> flights;
	CityList::CityID cid = m_Players.at(pos)->getCityID();
	for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
	{
		if (rc.GetCityID() == cid)
		{
			IsInACityWithAResearchCEnter = true;
			continue;
		}
		else
		{
			flights.emplace_back(rc.GetCityID());
		}
	}

	if (!IsInACityWithAResearchCEnter)
	{
		flights.clear();
	}
	return flights;
}

std::vector<CityList::CityID> GameEngine::ShareKnowlegdeFor(const uint16_t pos)
{
	std::vector<CityList::CityID> result;
	if (m_Players.at(pos)->hasCurrentCityCard())
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos)
				continue;

			if (m_Players.at(pos)->getCityID() == m_Players.at(index)->getCityID())
			{
				result.emplace_back(m_Players.at(index)->getCityID());
				break;
			}
		}
	}
	return result;
}

std::vector<CityList::CityID> GameEngine::DiscoverCure(const uint16_t pos)
{
	std::vector<CityList::CityID> result;
	for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
	{
		if (rc.GetCityID() == m_Players.at(pos)->getCityID())
		{
			int cardsneeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
			if (m_Players.at(pos)->m_hand.size() >= cardsneeded)
			{
				int red = 0, blue = 0, yellow = 0, black = 0;
				for each (PlayerCard* pc in m_Players.at(pos)->m_hand)
				{
					if (PlayerCardFactory::IsaCityCard(pc->getNumID()))
					{
						switch (((CityCard*)pc)->getCityColor())
						{
						case RED: red++; break;
						case BLUE: blue++; break;
						case YELLOW: yellow++; break;
						case BLACK: black++; break;
						}
					}
				}
				if (red >= cardsneeded || blue >= cardsneeded || yellow >= cardsneeded || black >= cardsneeded)
				{
					result.emplace_back(rc.GetCityID());
					break;
				}
			}
		}
	}
	return result;
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

	TurnSequence(0);

}
