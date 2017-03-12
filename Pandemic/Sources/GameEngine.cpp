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
	/* TODO: GE needs to do this to factor in players +/- cure status */
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
	TurnActionsPhase(pos);
}

void GameEngine::TurnActionsPhase(const uint16_t & pos)
{
	for (size_t i = 0; i < 5; i++)
	{
		MovesPerCity options = CalculatePlayerOpt(pos);

		//for test purposes
		for each(std::pair<MoveOptions, City::CityID> pair in options)
		{
			std::cout << pair.first << " / " << std::hex << pair.second << std::endl;
		}

		std::cout << "Select your desired move from the list below... (#)" << std::endl;
		PlayerMoves moves = DeterminePlayerMoves(options);
		uint16_t selection;
		do
		{
			std::cout << "Selcetion: ";
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss(input);
			ss >> selection;

			if (selection < 1 || selection >= moves.size())
			{
				std::cout << "Invalid option. Please Try again..." << std::endl;
			}
		} while (selection < 1 || selection >= moves.size());

		ExecuteMove(pos, moves.at(selection).first, moves.at(selection).second);
	}
}

GameEngine::MovesPerCity GameEngine::CalculatePlayerOpt(const uint16_t & pos)
{
	MovesPerCity options;

	// Drive --------------------------------------------------------------------------------------
	for each(CityList::CityID id in GetDriveCitiesFor(pos))
	{
		options.insert(std::make_pair(GameEngine::DRIVE_FERRY, id));
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

std::vector<CityList::CityID> GameEngine::GetDriveCitiesFor(const uint16_t pos)
{
	std::vector<CityList::CityID> result;
	for each(City* city in m_Board.m_Map.getCitiesConnectedTo(m_Players.at(pos)->getCityID()))
	{
		result.emplace_back(city->getCityID());
	}
	return result;
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

	// 1. Player is the researcher
	if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
	{
		for each(Player* joeur in m_Players)
		{
			if (m_Players.at(pos)->getCityID() == joeur->getCityID())
			{
				result.emplace_back(joeur->getCityID());
				return result;
			}
		}
	}

	// 2. has current city's matching city card
	if (m_Players.at(pos)->hasCurrentCityCard())
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos)
				continue;

			if (m_Players.at(pos)->getCityID() == m_Players.at(index)->getCityID())
			{
				result.emplace_back(m_Players.at(index)->getCityID());
				return result;
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
			int NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
			if (m_Players.at(pos)->m_hand.size() >= NumOfCardsNeeded)
			{
				switch (DetermineCureColor(pos))
				{
				case RED:
				case BLUE:
				case YELLOW:
				case BLACK:
					result.emplace_back(rc.GetCityID());
				default:
					break;
				}
				break;
			}
		}
	}
	return result;
}

Color GameEngine::DetermineCureColor(const uint16_t pos)
{
	int NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
	if (m_Players.at(pos)->m_hand.size() >= NumOfCardsNeeded)
	{
		int red = 0, blue = 0, yellow = 0, black = 0;
		for each (PlayerCard* pc in m_Players.at(pos)->m_hand)
		{
			if (PlayerCardFactory::IsaCityCard(pc->getNumID()))
			{
				switch (static_cast<CityCard*>(pc)->getCityColor())
				{
				case RED: red++; break;
				case BLUE: blue++; break;
				case YELLOW: yellow++; break;
				case BLACK: black++; break;
				}
			}
		}
		if (red >= NumOfCardsNeeded)
			return RED;
		else if (blue >= NumOfCardsNeeded)
			return BLUE;
		else if (yellow >= NumOfCardsNeeded)
			return YELLOW;
		else if (black >= NumOfCardsNeeded)
			return BLACK;
	}
	return Color::INVALID;
}

GameEngine::PlayerMoves GameEngine::DeterminePlayerMoves(const MovesPerCity & options)
{
	PlayerMoves moves;
	int i = 0;

	// Drive --------------------------------------------------------------------------------------
	if (options.count(GameEngine::DRIVE_FERRY) > 0)
	{
		std::cout << std::endl << "A. Drive/Ferry" << std::endl;
		auto low = options.lower_bound(GameEngine::DRIVE_FERRY);
		auto high = options.upper_bound(GameEngine::DRIVE_FERRY);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Direct Flight ------------------------------------------------------------------------------
	if (options.count(GameEngine::FLIGHT) > 0)
	{
		std::cout << std::endl << "B. Direct Flight" << std::endl;
		auto low = options.lower_bound(GameEngine::FLIGHT);
		auto high = options.upper_bound(GameEngine::FLIGHT);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Charter Flight -----------------------------------------------------------------------------
	if (options.count(GameEngine::CHARTER) > 0)
	{
		std::cout << std::endl << "C. Charter Flight" << std::endl;
		auto low = options.lower_bound(GameEngine::CHARTER);
		auto high = options.upper_bound(GameEngine::CHARTER);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Shuttle Flight -----------------------------------------------------------------------------
	if (options.count(GameEngine::SHUTTLE) > 0)
	{
		std::cout << std::endl << "C. Shuttle Flight" << std::endl;
		auto low = options.lower_bound(GameEngine::SHUTTLE);
		auto high = options.upper_bound(GameEngine::SHUTTLE);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Treat Diesease -----------------------------------------------------------------------------
	if (options.count(GameEngine::TREATDISEASE) > 0)
	{
		std::cout << std::endl << "E. Treat Disease" << std::endl;
		auto low = options.lower_bound(GameEngine::TREATDISEASE);
		auto high = options.upper_bound(GameEngine::TREATDISEASE);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Build Research Center ----------------------------------------------------------------------
	if (options.count(GameEngine::BUILDRC) > 0)
	{
		std::cout << std::endl << "F. Build Research Center" << std::endl;
		auto low = options.lower_bound(GameEngine::BUILDRC);
		auto high = options.upper_bound(GameEngine::BUILDRC);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	// Share Knowledge --------–-------------------------------------------------------------------
	if (options.count(GameEngine::SHARECARD) > 0)
	{
		std::cout << std::endl << "G. Share Knowledge" << std::endl;
		auto low = options.lower_bound(GameEngine::SHARECARD);
		auto high = options.upper_bound(GameEngine::SHARECARD);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	// Discover Cure ------------------------------------------------------------------------------
	if (options.count(GameEngine::CUREDISEASE) > 0)
	{
		std::cout << std::endl << "H. Discover a Cure" << std::endl;
		auto low = options.lower_bound(GameEngine::CUREDISEASE);
		auto high = options.upper_bound(GameEngine::CUREDISEASE);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.getCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	return moves;
}

std::string GameEngine::MoveOpToString(const MoveOptions & opt)
{
	switch (opt)
	{
	case DRIVE_FERRY:
		return "Drive/Ferry";
	case 	FLIGHT:
		return "Direct Flight";
	case 	CHARTER:
		return "Charter Flight";
	case 	SHUTTLE:
		return "Shuttle Flight";
	case 	TREATDISEASE:
		return "Treat Disease";
	case 	BUILDRC:
		return "Build Research Station";
	case 	SHARECARD:
		return "Share Knowledge";
	case 	CUREDISEASE:
		return "Cure Disease";
	default:
		return "";
	}
}

void GameEngine::ExecuteMove(const uint16_t pos, const MoveOptions & opt, const CityList::CityID & cityID)
{
	std::stringstream ss;
	Color cc;
	switch (opt)
	{
	case DRIVE_FERRY:
	case FLIGHT:
	case CHARTER:
	case SHUTTLE:
	case TREATDISEASE:
		ss << std::hex << cityID;
		m_Players.at(pos)->ChangeCity(ss.str());
		break;
	case BUILDRC:
		for(size_t i = 0; i < m_Players.at(pos)->m_hand.size(); i += 1)
		{
			if (m_Players.at(pos)->m_hand.at(i)->getNumID() == m_Players.at(pos)->getCityID())
			{
				m_Board.m_Centers.AddStation(m_Board.m_Map.getCityWithID(m_Players.at(pos)->getCityID()));
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->rmCard(i));
				break;
			}
		}
		break;
	case SHARECARD:
		if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
		{
			uint16_t selection = 0;
			do 
			{
				std::cout << "Which card would you like to share...";
				m_Players.at(pos)->printHand();
				std::string input;
				std::getline(std::cin, input);
				ss << input;
				ss >> selection;
			} while (selection < 0 || selection >= m_Players.at(pos)->m_hand.size());

			for (size_t index = 0; index < m_Players.size(); index += 1)
			{
				if (index == pos)
					continue;

				if (m_Players.at(pos)->getCityID() == m_Players.at(index)->getCityID())
				{
					m_Players.at(index)->addCard(m_Players.at(pos)->rmCard(selection));
					return;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < m_Players.at(pos)->m_hand.size(); i += 1)
			{
				if (m_Players.at(pos)->m_hand.at(i)->getNumID() == m_Players.at(pos)->getCityID())
				{
					for (size_t index = 0; index < m_Players.size(); index += 1)
					{
						if (index == pos)
							continue;

						if (m_Players.at(pos)->getCityID() == m_Players.at(index)->getCityID())
						{
							m_Players.at(index)->addCard(m_Players.at(pos)->rmCard(i));
							return;
						}
					}
				}
			}
		}
		break;
	case CUREDISEASE:
		cc = DetermineCureColor(pos);
		if (cc != Color::INVALID)
		{
			m_Board.m_Cures.CureDiscover(cc);
			for (size_t i = 0; i < m_Players.at(pos)->m_hand.size(); i += 1)
			{
				if(PlayerCardFactory::IsaCityCard(m_Players.at(pos)->m_hand.at(i)->getNumID()))
					if (static_cast<CityCard*>(m_Players.at(pos)->m_hand.at(i))->getCityColor() == cc)
						m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->rmCard(i));
			}
		}
		break;
	default:
		break;
	}
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
