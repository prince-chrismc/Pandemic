#include <sstream>  //std::stringstream
#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include <iostream> //std::cout
#include <ctime> //time
#include "boost\filesystem.hpp" //dir
#include "GameEngine.h"
namespace bfs = boost::filesystem;

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

// MakeFileName -----------------------------------------------------------------------------------
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
	if (now->tm_hour < 10) filename += "0";
	filename += std::to_string(now->tm_hour);
	if (now->tm_min < 10) filename += "0";
	filename += std::to_string(now->tm_min);
	if (now->tm_sec < 10) filename += "0";
	filename += std::to_string(now->tm_sec);
	filename += ".txt";

	return filename;
}
// MakeFileName -----------------------------------------------------------------------------------

// RegisterPlayer ---------------------------------------------------------------------------------
void GameEngine::RegisterPlayer(const std::string & newPlayerName)
{
	m_Players.emplace_back(new Player(newPlayerName, m_Board.m_RoleDeck.DrawCard()));
}
// RegisterPlayer ---------------------------------------------------------------------------------

// PlayerSetup ------------------------------------------------------------------------------------
void GameEngine::PlayersSetup()
{
	std::string input;
	int num;
	do
	{
		std::cout << "How Many Players will be playing? (2-4) "; // get total num of players
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
		std::cout << "Welcome Player " << i + 1 << " Enter your name: "; // get cetain players name
		std::getline(std::cin, input);
		input.erase(std::remove_if(input.begin(), input.end(), [](const unsigned &c) { return !isspace(c) && !isalpha(c); })); // Format input to be valid

		std::string name = input.substr(0, 10); // cut to limit
		RegisterPlayer(name);
	}

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Players.begin(), m_Players.end(), g);

	for each(Player* joeur in m_Players) // draw # of cards based on number of players
	{
		switch (m_Players.size())
		{
		case 2:
			joeur->AddCard(m_Board.m_PlayerDeck.DrawCard());
		case 3:
			joeur->AddCard(m_Board.m_PlayerDeck.DrawCard());
		case 4:
			joeur->AddCard(m_Board.m_PlayerDeck.DrawCard());
			joeur->AddCard(m_Board.m_PlayerDeck.DrawCard());
		default:
			break;
		}
	}
}
// PlayerSetup ------------------------------------------------------------------------------------

// DifficultySetup --------------------------------------------------------------------------------
void GameEngine::DifficultySetup()
{
	std::string input;
	int dif;
	std::cout << "1. Easy 2. Medium 3. Hard\nChoose your difficulty... ";
	std::getline(std::cin, input);
	std::stringstream ss(input);
	ss >> dif;

	m_Board.m_PlayerDeck.IncreaseDifficulty((Difficulty::DIFFICULTY)dif);
}
// DifficultySetup --------------------------------------------------------------------------------

// BoardSetup -------------------------------------------------------------------------------------
void GameEngine::BoardSetup()
{
	InfectCity(3); // infect cities
	InfectCity(3);
	InfectCity(3);
	InfectCity(2);
	InfectCity(2);
	InfectCity(2);
	InfectCity();
	InfectCity();
	InfectCity();

	AddResearchCenter(City::ATLANTA); // add base research center
}
// DifficultySetup --------------------------------------------------------------------------------

// TurnSequence -----------------------------------------------------------------------------------
void GameEngine::TurnSequence(const uint16_t & pos)
{
	std::cout << std::endl;
	TurnActionsPhase(pos);
	TurnDrawPhase(pos);
	TurnInfectPhase();
	//SaveGame();
}
// TurnSequence -----------------------------------------------------------------------------------

// TurnActionsPhase -------------------------------------------------------------------------------
void GameEngine::TurnActionsPhase(const uint16_t & pos)
{
	std::cout << std::endl;
	m_Players.at(pos)->PrintInfo();
	for (size_t i = 0; i < 4; i++)
	{
		MovesPerCity options = CalculatePlayerOpt(pos);

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

			if (selection < 1 || selection > moves.size())
			{
				std::cout << "Invalid option. Please Try again..." << std::endl;
			}
		} while (selection < 1 || selection > moves.size());

		ExecuteMove(pos, moves.at(selection).first, moves.at(selection).second);
	}
}
// TurnActionsPhase -------------------------------------------------------------------------------

// TurnDrawPhase ----------------------------------------------------------------------------------
void GameEngine::TurnDrawPhase(const uint16_t& pos)
{
	for (int i = 0; i < 2; i += 1)
	{
		CheckIfGameOver();
		if (m_Players.at(pos)->m_Hand.size() >= 7) // if hand is full
		{
			m_Players.at(pos)->PrintHand();
			uint16_t selection = 0;
			do
			{
				std::cout << "Which card would you like discard? ";
				std::string input;
				std::getline(std::cin, input); // get discard pos
				std::stringstream ss(input);
				ss >> selection;
			} while (selection < 0 || selection > m_Players.at(pos)->m_Hand.size());

			m_Players.at(pos)->RemoveCardAt(selection); // discard card
		}
		m_Players.at(pos)->AddCard(m_Board.m_PlayerDeck.DrawCard()); // no matter what draw card
	}
	m_Players.at(pos)->PrintHand();
}
// TurnDrawPhase ----------------------------------------------------------------------------------

// TurnInfectPhase --------------------------------------------------------------------------------
void GameEngine::TurnInfectPhase()
{
	for (size_t i = 0; i < m_Board.m_InfectRate.getRate(); i++)
	{
		InfectCity();
		CheckIfGameOver();
	}
}
// TurnInfectPhase --------------------------------------------------------------------------------

// InfectCity -------------------------------------------------------------------------------------
void GameEngine::InfectCity(const uint16_t& cubesToAdd)
{
	InfectionCard* ic = m_Board.m_InfecDeck.DrawCard(); // Draw card
	CityList::CityID cid = (City::CityID)(ic->GetNumID() - InfectionCard::INFECTIONCARD_MIN); // calculate id

	City* city = m_Board.m_Map.GetCityWithID(cid);

	Color c = ic->GetCityColor();
	if (m_Board.m_Cures.IsEradicated(c)) // if eradicated do add cubes
		return;

	delete ic;
	ic = nullptr;


	std::vector<RoleList::Roles> rolesincity;
	for each(Player* joeur in m_Players)
	{
		if (joeur->GetCityID() == city->GetCityID())
			rolesincity.emplace_back(joeur->GetRoleID());
	}

	for each(RoleList::Roles roleid in rolesincity)
	{
		switch (roleid)
		{
		case RoleList::QUARANTINE:
			return;
		case RoleList::MEDIC:
			if (m_Board.m_Cures.IsCured(c))
				return;
		default:
			break;
		}
	}

	for (size_t i = 0; i < cubesToAdd; i++)
	{
		if (city->GetNumberOfCubes() == 3)
		{
			Outbreak(city);
			return;
		}
		else
		{
			city->addCube(m_Board.m_Cubes.TakeCube(city->GetCityColor()));
		}
	}
}
// InfectCity -------------------------------------------------------------------------------------

// Outbreak ---------------------------------------------------------------------------------------
void GameEngine::Outbreak(City * city)
{
	m_Board.m_OutBreak.IncreaseRate();

	for each(City* connected in city->GetNearByCities())
	{
		connected->addCube(m_Board.m_Cubes.TakeCube(city->GetCityColor()));
	}
}
// Outbreak ---------------------------------------------------------------------------------------

// Epidemic ---------------------------------------------------------------------------------------
void GameEngine::Epidemic()
{
	// 1. Increase Infection Rate
	m_Board.m_InfectRate.IncreaseRate();

	// 2. Infect Last Card of InfectionDeck with at most 3 Cubes
	InfectionCard* ic = m_Board.m_InfecDeck.DrawCardForEpidemic();
	Color c = ic->GetCityColor();
	if (m_Board.m_Cures.IsNotEradicated(c))
	{
		City::CityID cid = (City::CityID)(ic->GetNumID() - InfectionCard::INFECTIONCARD_MIN);
		delete ic; ic = nullptr;

		City* city = m_Board.m_Map.GetCityWithID(cid);

		for (uint16_t i = city->GetNumberOfCubes(); i < 3; i += 1)
			city->addCube(m_Board.m_Cubes.TakeCube(city->GetCityColor()));

		// 2.1. Otbreaks if Need be
		if (city->GetNumberOfCubes() > 0)
		{
			Outbreak(city);
		}

		// 3. Intensify reshuffle infect discard and add on top of deck
		m_Board.m_InfecDeck.Intensify();
	}
}
// Epidemic ---------------------------------------------------------------------------------------

// CalculatePlayerOpt -----------------------------------------------------------------------------
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
	if (m_Board.m_Map.GetCityWithID(m_Players.at(pos)->GetCityID())->GetNumberOfCubes() > 0)
	{
		options.insert(std::make_pair(GameEngine::TREATDISEASE, m_Players.at(pos)->GetCityID()));
	}

	// Build Research Center ----------------------------------------------------------------------
	if (m_Players.at(pos)->HasCurrentCityCard())
	{
		options.insert(std::make_pair(GameEngine::BUILDRC, m_Players.at(pos)->GetCityID()));
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
// CalculatePlayerOpt -----------------------------------------------------------------------------

// GetDriveCitiesFor ------------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::GetDriveCitiesFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each(City* city in m_Board.m_Map.GetCitiesConnectedTo(m_Players.at(pos)->GetCityID()))
	{
		result.emplace_back(city->GetCityID());
	}
	return result;
}
// GetDriveCitiesFor ------------------------------------------------------------------------------

// GetFlightCitiesFor -----------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::GetFlightCitiesFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each (PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaCityCard(pc->GetNumID()))
		{
			result.emplace_back((CityList::CityID)(pc->GetNumID() - CityCard::CITYCARD_MIN));
		}
	}
	return result;
}
// GetFlightCitiesFor -----------------------------------------------------------------------------

// GetCharterFlightsFor ---------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::GetCharterFlightsFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	if (m_Players.at(pos)->HasCurrentCityCard())
	{
		for each (City* city in m_Board.m_Map.GetAllCities())
		{
			if (city->GetCityID() == m_Players.at(pos)->GetCityID())
				continue;

			result.emplace_back(city->GetCityID());
		}
	}
	return result;
}
// GetCharterFlightsFor ---------------------------------------------------------------------------

// GetShuttleFlightsFor ---------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::GetShuttleFlightsFor(const uint16_t& pos)
{
	bool IsInACityWithAResearchCEnter = false;
	std::vector<CityList::CityID> flights;
	CityList::CityID cid = m_Players.at(pos)->GetCityID();
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
// GetShuttleFlightsFor ---------------------------------------------------------------------------

// ShareKnowlegdeFor ------------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::ShareKnowlegdeFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;

	// 1. Player is the researcher
	if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos) continue;

			if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())
			{
				result.emplace_back(m_Players.at(index)->GetCityID());
				return result;
			}
		}
	}

	// 2. has current city's matching city card
	if (m_Players.at(pos)->HasCurrentCityCard())
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos) continue;

			if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())
			{
				result.emplace_back(m_Players.at(index)->GetCityID());
				return result;
			}
		}
	}
	return result;
}
// ShareKnowlegdeFor ------------------------------------------------------------------------------

// DiscoverCure -----------------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::DiscoverCure(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
	{
		if (rc.GetCityID() == m_Players.at(pos)->GetCityID())
		{
			int NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
			if (m_Players.at(pos)->m_Hand.size() >= NumOfCardsNeeded)
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
// DiscoverCure -----------------------------------------------------------------------------------

// DetermineCureColor -----------------------------------------------------------------------------
Color GameEngine::DetermineCureColor(const uint16_t& pos)
{
	int NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
	if (m_Players.at(pos)->m_Hand.size() >= NumOfCardsNeeded)
	{
		int red = 0, blue = 0, yellow = 0, black = 0;
		for each (PlayerCard* pc in m_Players.at(pos)->m_Hand)
		{
			if (PlayerCardFactory::IsaCityCard(pc->GetNumID()))
			{
				switch (static_cast<CityCard*>(pc)->GetCityColor())
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
// DetermineCureColor -----------------------------------------------------------------------------

// DeterminePlayerMoves ---------------------------------------------------------------------------
GameEngine::PlayerMoves GameEngine::DeterminePlayerMoves(const MovesPerCity & options)
{
	PlayerMoves moves;
	uint16_t i = 0;

	// Drive --------------------------------------------------------------------------------------
	if (options.count(GameEngine::DRIVE_FERRY) > 0)
	{
		std::cout << std::endl << "A. Drive/Ferry" << std::endl;
		auto low = options.lower_bound(GameEngine::DRIVE_FERRY);
		auto high = options.upper_bound(GameEngine::DRIVE_FERRY);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
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
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	return moves;
}
// DeterminePlayerMoves ---------------------------------------------------------------------------

// MoveOpToString ---------------------------------------------------------------------------------
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
// MoveOpToString ---------------------------------------------------------------------------------

// ExecuteMove ------------------------------------------------------------------------------------
void GameEngine::ExecuteMove(const uint16_t& pos, const MoveOptions & opt, const CityList::CityID & cityID)
{
	std::stringstream ss;
	Color cc;
	City* city = nullptr;
	switch (opt)
	{
	case DRIVE_FERRY:
		ss << std::hex << cityID;
		m_Players.at(pos)->ChangeCity(ss.str());
		m_Players.at(pos)->PrintInfo();
		break;
	case FLIGHT:
		ss << std::hex << cityID;
		m_Players.at(pos)->ChangeCity(ss.str());
		m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID));
		m_Players.at(pos)->PrintInfo();
		m_Players.at(pos)->PrintHand();
		break;
	case CHARTER:
		ss << std::hex << cityID;
		m_Players.at(pos)->ChangeCity(ss.str());
		m_Players.at(pos)->PrintInfo();
		m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(m_Players.at(pos)->GetCityID()));
		m_Players.at(pos)->PrintHand();
	case SHUTTLE:
		ss << std::hex << cityID;
		m_Players.at(pos)->ChangeCity(ss.str());
		m_Players.at(pos)->PrintInfo();
		break;
	case TREATDISEASE:
		city = m_Board.m_Map.GetCityWithID(cityID);
		switch (m_Players.at(pos)->GetRoleID())
		{
		case RoleList::MEDIC:
			city->RemoveAllCubes();
			city->PrintInformation();
			break;
		default:
			city->RemoveCube();
			city->PrintInformation();
			break;
		}
		CheckIfGameOver();
		break;
	case BUILDRC:
		m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(cityID));
		m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID));
		std::cout << "New Research Center in: ";
		m_Board.m_Map.GetCityWithID(cityID)->PrintInformation();
		break;
	case SHARECARD:
		if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
		{
			uint16_t selection = 0;
			do
			{
				std::cout << "Which card would you like to share...";
				m_Players.at(pos)->PrintHand();
				std::string input;
				std::getline(std::cin, input);
				ss << input;
				ss >> selection;
			} while (selection < 0 || selection >= m_Players.at(pos)->m_Hand.size());

			for (size_t index = 0; index < m_Players.size(); index += 1)
			{
				if (index == pos) continue;

				if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())
				{
					m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCardAt(selection));
					m_Players.at(index)->PrintHand();
					m_Players.at(pos)->PrintHand();
					return;
				}
			}
		}
		else
		{
			for (size_t index = 0; index < m_Players.size(); index += 1)
			{
				if (index == pos) continue;

				if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())
				{
					m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCard(cityID));
					m_Players.at(index)->PrintHand();
					m_Players.at(pos)->PrintHand();
					return;
				}
			}
		}
		break;
	case CUREDISEASE:
		cc = DetermineCureColor(pos);
		if (cc != Color::INVALID)
		{
			m_Board.m_Cures.CureDiscover(cc);
			for (size_t i = 0; i < m_Players.at(pos)->m_Hand.size(); i += 1)
			{
				if (PlayerCardFactory::IsaCityCard(m_Players.at(pos)->m_Hand.at(i)->GetNumID()))
					if (static_cast<CityCard*>(m_Players.at(pos)->m_Hand.at(i))->GetCityColor() == cc)
						m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)i));
			}
		}
		break;
	default:
		break;
	}
}
// ExecuteMove ------------------------------------------------------------------------------------

// AddResearchCenter ------------------------------------------------------------------------------
void GameEngine::AddResearchCenter(const CityList::CityID & id)
{
	m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(id));
}
// AddResearchCenter ------------------------------------------------------------------------------

// CheckIfGameOver --------------------------------------------------------------------------------
void GameEngine::CheckIfGameOver()
{
	if (m_Board.m_Cubes.IsAnyEmpty()) throw GameOverException();
	if (m_Board.m_OutBreak.getMarker() == 8) throw GameOverException();
	if (m_Board.m_PlayerDeck.IsDeckEmpty()) throw GameOverException();
}
// CheckIfGameOver --------------------------------------------------------------------------------

// SaveGame ---------------------------------------------------------------------------------------
void GameEngine::SaveGame()
{
	if (!m_PreGameComplete)
	{
		std::cout << "Game Not Initialized" << std::endl;
		return;
	}

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
		myfile << "/ ";
	}
	myfile << "\n";

	// Cures --------------------------------------------------------------------------------------
	myfile << m_Board.m_Cures.GetSaveOutput();
	myfile << "\n";

	// Infection Rate -----------------------------------------------------------------------------
	myfile << m_Board.m_InfectRate.GetSaveOutput();
	myfile << "\n";

	// Outbreak Marker ----------------------------------------------------------------------------
	myfile << m_Board.m_OutBreak.GetSaveOutput();
	myfile << "\n";

	myfile.close();
}
// SaveGame ---------------------------------------------------------------------------------------

// LoadGame ---------------------------------------------------------------------------------------
void GameEngine::LoadGame()
{
	if (m_PreGameComplete)
	{
		std::cout << "WARNING: Game has already started..." << std::endl;
		SaveGame();
		std::cout << "AutoSave Completed" << std::endl;
	}

	int i = 0;
	std::map<int, bfs::directory_entry> files;
	bfs::path p("bin");
	if (bfs::exists(p)) // does p exist
	{
		if (bfs::is_directory(p)) // is p a directory?
		{
			std::cout << "Your Load Options are:\n";
			for (bfs::directory_iterator itor(p); itor != bfs::directory_iterator(); itor++) // for all items in dir
			{
				if (bfs::is_regular_file(itor->path())) //if item is a regular file
				{
					std::cout << i << ": " << itor->path().filename() << std::endl; // print option
					files.emplace(std::make_pair(i++, *itor)); // save options
				}
			}
		}
		else
		{
			std::cout << p << " exists, but is neither a regular file nor a directory\n";
			return;
		}
	}
	else
	{
		std::cout << p << " does not exist\n";
		return;
	}

	int selection = -1;
	do
	{
		std::cout << "Selection: ";
		std::string input;
		std::getline(std::cin, input); // get usesrs choice
		std::stringstream ss(input);
		ss >> selection;
	} while (selection < 0 || selection >= i);

	bfs::ifstream load;
	load.open(files.at(selection).path()); // open correct file

	char* buffer = new char[512];
	load.getline(buffer, 512); // to remove title line that is saved
	delete[] buffer;
	buffer = nullptr;

	// Infection Cards ----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string infec(buffer);
		delete[] buffer;
		buffer = nullptr;

		size_t sep = infec.find("/"); // split save output
		std::string infecdeck = infec.substr(0, sep); // by deck
		std::string infecdiscard = infec.substr(sep + 2); // and discard

		std::deque<InfectionCard::CardsList> deckLoaded;
		for (int i = 0; i < 48; i += 1)
		{
			size_t space = infecdeck.find(" ");
			if (space == std::string::npos) break;
			std::stringstream ss(infecdeck.substr(0, space));
			infecdeck = infecdeck.substr(space + 1);
			uint64_t num = 0;
			ss >> std::hex >> num;
			deckLoaded.emplace_back((InfectionCard::CardsList)num);
		}

		std::deque<InfectionCard::CardsList> discardLoaded;
		for (int i = 0; i < 48; i += 1)
		{
			size_t space = infecdiscard.find(" ");
			if (space == std::string::npos) break;
			std::stringstream ss(infecdiscard.substr(0, space));
			infecdiscard = infecdiscard.substr(space + 1);
			uint64_t num = 0;
			ss >> std::hex >> num;
			discardLoaded.emplace_back((InfectionCard::CardsList)num);
		}

		m_Board.m_InfecDeck.InputLoadedGame(deckLoaded, discardLoaded);
	}

	// Player Cards -------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string play(buffer);
		delete[] buffer;
		buffer = nullptr;

		size_t sep = play.find("/"); // split save output
		std::string playdeck = play.substr(0, sep); // by deck
		std::string playdiscard = play.substr(sep + 2); // and discard

		std::deque<PlayerCard::CardsList> deckLoaded;
		for (int i = 0; i < 59; i += 1)
		{
			size_t space = playdeck.find(" ");
			if (space == std::string::npos) break;
			std::stringstream ss(playdeck.substr(0, space));
			playdeck = playdeck.substr(space + 1);
			uint64_t num = 0;
			ss >> std::hex >> num;
			deckLoaded.emplace_back((PlayerCard::CardsList)num);
		}

		std::deque<PlayerCard::CardsList> discardLoaded;
		for (int i = 0; i < 59; i += 1)
		{
			size_t space = playdiscard.find(" ");
			if (space == std::string::npos) break;
			std::stringstream ss(playdiscard.substr(0, space));
			playdiscard = playdiscard.substr(space + 1);
			uint64_t num = 0;
			ss >> std::hex >> num;
			discardLoaded.emplace_back((PlayerCard::CardsList)num);
		}

		m_Board.m_PlayerDeck.InputLoadedGame(deckLoaded, discardLoaded);
	}

	// Role Cards ---------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string role(buffer);
		delete[] buffer;
		buffer = nullptr;

		std::deque<RoleCard::Roles> deckLoaded;
		for (int i = 0; i < 7; i += 1)
		{
			size_t space = role.find(" ");
			if (space == std::string::npos) break;
			std::stringstream ss(role.substr(0, space));
			role = role.substr(space + 1);
			uint64_t num = 0;
			ss >> std::hex >> num;
			deckLoaded.emplace_back((RoleCard::Roles)num);
		}

		m_Board.m_RoleDeck.InputLoadedGame(deckLoaded);
	}

	// Cities -------------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string cities(buffer);
		delete[] buffer;
		buffer = nullptr;

		for each(City* city in m_Board.m_Map.GetAllCities())
		{
			size_t sep = cities.find("/");
			if (sep == 0)
			{
				cities = cities.substr(sep + 2);
				continue;
			}
			std::string cubecolors = cities.substr(0, sep);
			cities = cities.substr(sep + 2);
			for each(char c in cubecolors)
			{
				switch (c)
				{
				case '0':
					city->addCube(m_Board.m_Cubes.TakeCube(RED));
					break;
				case '1':
					city->addCube(m_Board.m_Cubes.TakeCube(BLUE));
					break;
				case '2':
					city->addCube(m_Board.m_Cubes.TakeCube(YELLOW));
					break;
				case '3':
					city->addCube(m_Board.m_Cubes.TakeCube(BLACK));
					break;
				default:
					break;
				}
			}

		}

	}

	// Players ------------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string players(buffer);
		delete[] buffer;
		buffer = nullptr;

		std::vector<Player*> gamers;
		for (int i = 0; i < 4; i += 1)
		{
			size_t slash = players.find("/");
			if (slash == std::string::npos) break;
			std::string play = players.substr(0, slash);
			players = players.substr(slash + 2);

			size_t space = play.find(" ");
			if (space == std::string::npos) break;
			std::string name = play.substr(0, space); // get players name
			play = play.substr(space + 1);

			space = play.find(" ");
			std::string id = play.substr(0, space); // get players role id
			play = play.substr(space + 1);
			std::stringstream ss(id);
			uint64_t roleid;
			ss >> std::hex >> roleid;
			Player* joeur = new Player(name, new RoleCard((RoleList::Roles)roleid));

			for (int j = 0; j < 7; j += 1)
			{
				ss = std::stringstream();
				space = play.find(" ");
				if (space == std::string::npos) break;
				ss << play.substr(0, space); // get card id
				play = play.substr(space + 1);
				uint64_t cardnum;
				ss >> std::hex >> cardnum;
				joeur->AddCard(PlayerCardFactory::MakeCard(cardnum));
			}

			gamers.emplace_back(joeur);
		}
		m_Players = gamers;
	}

	// Cures --------------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string rate(buffer);
		delete[] buffer;
		buffer = nullptr;

		uint16_t red, blue, yellow, black;
		std::stringstream ss;
		ss << rate.at(0);
		ss >> red;
		ss.clear();
		ss << rate.at(1);
		ss >> blue;
		ss.clear();
		ss << rate.at(2);
		ss >> yellow;
		ss.clear();
		ss << rate.at(3);
		ss >> black;

		m_Board.m_Cures.InputLoadedGame(red, blue, yellow, black);
	}

	// Infection Rate -----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string rate(buffer);
		delete[] buffer;
		buffer = nullptr;

		switch (rate.at(0))
		{
		case '0':
			m_Board.m_InfectRate.InputLoadedGame(0);
			break;
		case '1':
			m_Board.m_InfectRate.InputLoadedGame(1);
			break;
		case '2':
			m_Board.m_InfectRate.InputLoadedGame(2);
			break;
		case '3':
			m_Board.m_InfectRate.InputLoadedGame(3);
			break;
		case '4':
			m_Board.m_InfectRate.InputLoadedGame(4);
			break;
		case '5':
			m_Board.m_InfectRate.InputLoadedGame(5);
			break;
		case '6':
			m_Board.m_InfectRate.InputLoadedGame(6);
			break;
		default:
			m_Board.m_InfectRate.InputLoadedGame(0);
			break;
		}
	}

	// Outbreak Marker ----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string marker(buffer);
		delete[] buffer;
		buffer = nullptr;

		switch (marker.at(0))
		{
		case '0':
			m_Board.m_OutBreak.InputLoadedGame(0);
			break;
		case '1':
			m_Board.m_OutBreak.InputLoadedGame(1);
			break;
		case '2':
			m_Board.m_OutBreak.InputLoadedGame(2);
			break;
		case '3':
			m_Board.m_OutBreak.InputLoadedGame(3);
			break;
		case '4':
			m_Board.m_OutBreak.InputLoadedGame(4);
			break;
		case '5':
			m_Board.m_OutBreak.InputLoadedGame(5);
			break;
		case '6':
			m_Board.m_OutBreak.InputLoadedGame(6);
			break;
		case '7':
			m_Board.m_OutBreak.InputLoadedGame(7);
			break;
		case '8':
			m_Board.m_OutBreak.InputLoadedGame(8);
			break;
		default:
			m_Board.m_OutBreak.InputLoadedGame(0);
			break;
		}
	}
	m_PreGameComplete = true;
}
// LoadGame ---------------------------------------------------------------------------------------

// Initialize -------------------------------------------------------------------------------------
void GameEngine::Initialize()
{
	BoardSetup();
	DifficultySetup();
	PlayersSetup();

	m_PreGameComplete = true;
}
// Initialize -------------------------------------------------------------------------------------

// Launch -----------------------------------------------------------------------------------------
void GameEngine::Launch()
{
	if (!m_PreGameComplete)
	{
		std::cout << "Game Not Initialized" << std::endl;
		return;
	}

	try
	{
		for (int i = 0; /* no limit */; i += 1)
		{
			TurnSequence(i % 2);
			//TurnSequence(i % m_Players.size());
		}
	}
	catch (const GameOverException)
	{
		std::cout << "\n\n Game OVer !!!!!!!!!\n\n";
	}
}
// Launch -----------------------------------------------------------------------------------------
