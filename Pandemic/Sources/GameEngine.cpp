#include <sstream>  //std::stringstream
#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include <iostream> //std::cout
#include <ctime> //time
#include "boost\filesystem.hpp" //dir
#include "GameEngine.h"
#include "Pandemic.h"
namespace bfs = boost::filesystem;

GameEngine::GameEngine() : m_Board(), m_Players(), m_PreGameComplete(false), m_SkipNextInfectionPhase(false)
{
	std::cout << "\n               -------------- PANDEMIC -------------\nDo you have what it takes to save humanity? As skilled members of a disease - fighting team, you must\nkeep four deadly diseases at bay while discovering their cures.\nYou and your teammates will travel across the globe, treating infections while finding resources for\ncures. You must work together, using your individual strengths, to succeed.The clock is ticking as\noutbreaks and epidemics fuel the spreading plagues.\nCan you find all four cures in time? The fate of humanity is in your hands!\n\n" << std::endl;

	m_Log = new InfectionLog();
	RegistarObserver(m_Log);
}

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

	delete m_Log; m_Log = nullptr;
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
	std::cout << "How many players will there be?" << std::endl;
	uint16_t num = GetUserInput(2, 4);

	for (uint16_t i = 0; i < num; i += 1)
	{
		std::cout << "Welcome Player " << i + 1 << " Enter your name: "; // get cetain players name
		std::string input;
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
	std::cout << "1. Introductory 2. Standard 3. Heroic\nChoose your difficulty... ";
	uint16_t dif = GetUserInput(1, 3);

	m_Board.m_PlayerDeck.IncreaseDifficulty(dif);
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

	m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(City::ATLANTA)); // add base research center
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

// GetUserInput -----------------------------------------------------------------------------------
const uint16_t GameEngine::GetUserInput(const uint16_t & lower, const uint16_t & upper)
{
	uint16_t selection = 0;
	do
	{
		std::cout << "Selcetion: ";
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss(input);
		ss >> selection;

		if (selection < lower || selection > upper)
			std::cout << "Invalid option. Please Try again..." << std::endl;

	} while (selection < lower || selection > upper );

	return selection;
}
// GetUserInput -----------------------------------------------------------------------------------

// TurnActionsPhase -------------------------------------------------------------------------------
void GameEngine::TurnActionsPhase(const uint16_t & pos)
{
	std::cout << std::endl;
	for (size_t i = 0; i < 4; /* no itor, determined by ExecuteMove() */)
	{
		std::cout << m_Board.m_Map.GetMapDiagram() << std::endl;
		m_Players.at(pos)->PrintHand();
		MovesPerCity options = CalculatePlayerOpt(pos);

		std::cout << "Select your desired move from the list below... (#)" << std::endl;
		PlayerMoves moves = DeterminePlayerMoves(options);
		
		uint16_t selection = GetUserInput(1, (uint16_t)moves.size());

		i += ExecuteMove(pos, moves.at(selection).first, moves.at(selection).second);		
	}
}
// TurnActionsPhase -------------------------------------------------------------------------------

// TurnDrawPhase ----------------------------------------------------------------------------------
void GameEngine::TurnDrawPhase(const uint16_t& pos)
{
	for (uint16_t i = 0; i < 2; i += 1)
	{
		CheckIfGameOver();
		if (m_Players.at(pos)->m_Hand.size() > 6) // if hand is full
		{
			m_Players.at(pos)->PrintHand();
			std::cout << "Which card would you like discard? ";
			uint16_t selection = GetUserInput(0 , (uint16_t)m_Players.at(pos)->m_Hand.size() - 1);

			m_Players.at(pos)->RemoveCardAt(selection); // discard card
		}
		PlayerCard* pc = m_Board.m_PlayerDeck.DrawCard();
		if (PlayerCardFactory::IsaEpidemicCard(pc->GetNumID()))
		{
			delete pc; 
			pc = nullptr;
			Epidemic();
		}
		else
		{
			m_Players.at(pos)->AddCard(pc); // no matter what draw card
		}
	}
	m_Players.at(pos)->PrintHand();
}
// TurnDrawPhase ----------------------------------------------------------------------------------

// TurnInfectPhase --------------------------------------------------------------------------------
void GameEngine::TurnInfectPhase()
{
	if (m_SkipNextInfectionPhase) // for event card quiet night
	{
		m_SkipNextInfectionPhase = false;
		return;
	}

	for (size_t i = 0; i < m_Board.m_InfectRate.GetRate(); i++)
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
	delete ic;
	ic = nullptr;

	City* city = m_Board.m_Map.GetCityWithID(cid); // get city
	Color c = city->GetCityColor();
	if (m_Board.m_Cures.IsEradicated(c)) // if eradicated do add cubes
		return;

	std::vector<RoleList::Roles> rolesincity; // lets figure out whos in the city
	for each(Player* joeur in m_Players)
	{
		if (joeur->GetCityID() == city->GetCityID())
			rolesincity.emplace_back(joeur->GetRoleID());
	}

	if (IsQuarentineSpecialistNearBy(city)) // make sure quarantine specialist isnt nearby
		rolesincity.emplace_back(RoleList::QUARANTINE);

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

	uint16_t cubesActuallyAdded = 0;
	for (size_t i = 0; i < cubesToAdd; i++)
	{
		if (city->GetNumberOfCubes(city->GetCityColor()) == 3)
		{
			if(cubesActuallyAdded > 0) 
				Notify(city->GetCityName(), cubesActuallyAdded);

			Outbreak(city);
			return;
		}
		else
		{
			city->AddCube(m_Board.m_Cubes.TakeCube(city->GetCityColor()));
			cubesActuallyAdded += 1;
		}
		CheckIfGameOver();
	}

	Notify(city->GetCityName(), cubesActuallyAdded);
}
// InfectCity -------------------------------------------------------------------------------------

// IsQuarentineSpecialistNearBy -------------------------------------------------------------------
bool GameEngine::IsQuarentineSpecialistNearBy(City * city)
{
	for each(Player* joeur in m_Players)
	{
		if (joeur->GetRoleID() == RoleList::QUARANTINE)
		{
			CityList::CityID cid = joeur->GetCityID();
			for each(City* ville in city->GetNearByCities())
			{
				if (ville->GetCityID() == cid)
					return true;
			}
			break;
		}
	}
	return false;
}
// IsQuarentineSpecialistNearBy -------------------------------------------------------------------

// Outbreak ---------------------------------------------------------------------------------------
void GameEngine::Outbreak(City* city, City* skip)
{
	if (IsQuarentineSpecialistNearBy(city))
		return;

	std::cout << " --- OUTBREAK --- " << city->GetCityName() << std::endl;
	m_Board.m_OutBreak.IncreaseRate();
	std::cout << "Outbreak Marker: " << m_Board.m_OutBreak.GetMarker() << std::endl;

	for each(City* connected in city->GetNearByCities())
	{
		if(skip != nullptr)
			if (connected->GetCityID() == skip->GetCityID())
				continue;

		if (connected->GetNumberOfCubes(city->GetCityColor()) == 3)
		{
			Outbreak(connected, city);
		}
		else
		{
			connected->AddCube(m_Board.m_Cubes.TakeCube(city->GetCityColor()));
			Notify(connected->GetCityName());
		}
	CheckIfGameOver();
	}
}
// Outbreak ---------------------------------------------------------------------------------------

// Epidemic ---------------------------------------------------------------------------------------
void GameEngine::Epidemic()
{
	std::cout << " --- EPIDEMIC --- " << std::endl;
	// 1. Increase Infection Rate
	m_Board.m_InfectRate.IncreaseRate();
	std::cout << "Infection Rate: " << m_Board.m_InfectRate.GetRate() << std::endl;

	// 2. Infect Last Card of InfectionDeck with at most 3 Cubes
	InfectionCard* ic = m_Board.m_InfecDeck.DrawCardForEpidemic();
	Color citycolor = ic->GetCityColor();
	if (m_Board.m_Cures.IsNotEradicated(citycolor))
	{
		City::CityID cid = (City::CityID)(ic->GetNumID() - InfectionCard::INFECTIONCARD_MIN);
		delete ic; ic = nullptr;

		City* city = m_Board.m_Map.GetCityWithID(cid);
		std::cout << "Occurring in: " << city->GetCityName() << std::endl;
		uint16_t i = 0;
		for (; i < 3; i += 1)
		{
			// 2.1. Otbreaks if Need be
			if (city->GetNumberOfCubes(citycolor) == 3)
			{
				Outbreak(city);
				break;
			}

			city->AddCube(m_Board.m_Cubes.TakeCube(citycolor));
			CheckIfGameOver();
		}
		Notify(city->GetCityName(), i);

		// 3. Intensify reshuffle infect discard and add on top of deck
		m_Board.m_InfecDeck.Intensify();
	}
}
// Epidemic ---------------------------------------------------------------------------------------

// CalculatePlayerOpt -----------------------------------------------------------------------------
GameEngine::MovesPerCity GameEngine::CalculatePlayerOpt(const uint16_t & pos)
{
	MovesPerCity options;

	// Quit ---------------------------------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::QUIT, m_Players.at(pos)->GetCityID()));

	// View Reference Card ------------------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::REFCARD, m_Players.at(pos)->GetCityID()));

	// Peak Infection Discard Pile ----------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::PEAK_INFECTION_DISCARD, m_Players.at(pos)->GetCityID()));

	// Peal Player Discard Pile -------------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::PEAK_PLAYER_DISCARD, m_Players.at(pos)->GetCityID()));

	// Drive --------------------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateDriveCitiesFor(pos))
	{
		options.insert(std::make_pair(GameEngine::DRIVE_FERRY, id));
	}

	// Flight --------------------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateFlightCitiesFor(pos))
	{
		options.insert(std::make_pair(GameEngine::FLIGHT, id));
	}

	// Charter ------------------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateCharterFlightsFor(pos))
	{
		options.insert(std::make_pair(GameEngine::CHARTER, id));
	}

	// Shuttle ------------------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateShuttleFlightsFor(pos))
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
	for each(CityList::CityID id in CalculateShareKnowlegdeFor(pos))
	{
		options.insert(std::make_pair(GameEngine::SHARECARD, id));
	}

	// Discover Cure ------------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateDiscoverCureFor(pos))
	{
		options.insert(std::make_pair(GameEngine::CUREDISEASE, id));
	}

	// EventCard Airlift---------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateAirliftFor(pos))
	{
		options.insert(std::make_pair(GameEngine::AIRLIFT, id));
	}

	// EventCard Resiliant Population -------------------------------------------------------------
	for each(CityList::CityID id in CalculateReseilientPopFor(pos))
	{
		options.insert(std::make_pair(GameEngine::RESILLIENT, id));
	}

	// EventCard Forecast -------------------------------------------------------------------------
	for each(CityList::CityID id in CalculateForecastFor(pos))
	{
		options.insert(std::make_pair(GameEngine::FORECAST, id));
	}

	// EventCard QuietNight -----------------------------------------------------------------------
	for each(CityList::CityID id in CalculateQuietNightFor(pos))
	{
		options.insert(std::make_pair(GameEngine::QUIETNIGHT, id));
	}

	// EventCard Government Grant -----------------------------------------------------------------
	for each(CityList::CityID id in CalculateGovernmentGrantFor(pos))
	{
		options.insert(std::make_pair(GameEngine::GOVTGRANT, id));
	}

	return options;
}
// CalculatePlayerOpt -----------------------------------------------------------------------------

// CalculateDriveCitiesFor ------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateDriveCitiesFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each(City* city in m_Board.m_Map.GetCitiesConnectedTo(m_Players.at(pos)->GetCityID()))
	{
		result.emplace_back(city->GetCityID());
	}
	return result;
}
// CalculateDriveCitiesFor ------------------------------------------------------------------------

// CalculateFlightCitiesFor -----------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateFlightCitiesFor(const uint16_t& pos)
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
// CalculateFlightCitiesFor -----------------------------------------------------------------------

// CalculateCharterFlightsFor ---------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateCharterFlightsFor(const uint16_t& pos)
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
// CalculateCharterFlightsFor ---------------------------------------------------------------------

// CalculateShuttleFlightsFor ---------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateShuttleFlightsFor(const uint16_t& pos)
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
// CalculateShuttleFlightsFor ---------------------------------------------------------------------

// CalculateShareKnowlegdeFor ---------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateShareKnowlegdeFor(const uint16_t& pos)
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
// CalculateShareKnowlegdeFor ---------------------------------------------------------------------

// CalculateDiscoverCureFor -----------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateDiscoverCureFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
	{
		if (rc.GetCityID() == m_Players.at(pos)->GetCityID())
		{
			uint16_t NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
			if (m_Players.at(pos)->m_Hand.size() >= NumOfCardsNeeded)
			{
				switch (DetermineCureColor(pos))
				{
				case Color::RED:
				case Color::BLUE:
				case Color::YELLOW:
				case Color::BLACK:
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
// CalculateDiscoverCureFor -----------------------------------------------------------------------

// CalculateReseilientPopFor ----------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateReseilientPopFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))
		{
			if(pc->GetNumID() == EventCard::RESILLIENT)
			{
				for each(InfectionCard::CardsList icID in m_Board.m_InfecDeck.GetDiscardPile())
				{
					result.emplace_back((CityList::CityID)(icID - InfectionCard::INFECTIONCARD_MIN));
				}
				return result;
			}
		}
	}

	return result;
}
// CalculateReseilientPopFor ----------------------------------------------------------------------

// CalculateAirliftFor ----------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateAirliftFor(const uint16_t & pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))
		{
			if (pc->GetNumID() == EventCard::AIRLIFT)
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				return result;
			}
		}
	}

	return result;
}
// CalculateAirliftFor ----------------------------------------------------------------------------

// CalculateForecastFor ---------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateForecastFor(const uint16_t & pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))
		{
			if (pc->GetNumID() == EventCard::FORECAST)
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				return result;
			}
		}
	}

	return result;
}
// CalculateForecastFor ---------------------------------------------------------------------------

// CalculateQuietNightFor -------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateQuietNightFor(const uint16_t & pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))
		{
			if (pc->GetNumID() == EventCard::QUIETNIGHT)
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				return result;
			}
		}
	}

	return result;
}
// CalculateQuietNightFor -------------------------------------------------------------------------

// CalculateGovernmentGrantFor --------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateGovernmentGrantFor(const uint16_t & pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand)
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))
		{
			if (pc->GetNumID() == EventCard::GOVTGRANT)
			{
				for each(City* city in m_Board.m_Map.GetAllCities())
				{
					CityList::CityID cid = city->GetCityID();
					result.emplace_back(cid);
					for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
					{
						if (rc.GetCityID() == cid)
						{
							result.erase(result.end()-1);
							break;
						}
					}
				}
				return result;
			}
		}
	}
	return result;
}
// CalculateGovernmentGrantFor --------------------------------------------------------------------

// DetermineCureColor -----------------------------------------------------------------------------
Color GameEngine::DetermineCureColor(const uint16_t& pos)
{
	uint16_t NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure();
	if (m_Players.at(pos)->m_Hand.size() >= NumOfCardsNeeded)
	{
		uint16_t red = 0, blue = 0, yellow = 0, black = 0;
		for each (PlayerCard* pc in m_Players.at(pos)->m_Hand)
		{
			if (PlayerCardFactory::IsaCityCard(pc->GetNumID()))
			{
				switch (static_cast<CityCard*>(pc)->GetCityColor())
				{
				case Color::RED: red++; break;
				case Color::BLUE: blue++; break;
				case Color::YELLOW: yellow++; break;
				case Color::BLACK: black++; break;
				}
			}
		}
		if (red >= NumOfCardsNeeded)
			return Color::RED;
		else if (blue >= NumOfCardsNeeded)
			return Color::BLUE;
		else if (yellow >= NumOfCardsNeeded)
			return Color::YELLOW;
		else if (black >= NumOfCardsNeeded)
			return Color::BLACK;
	}
	return Color::INVALID;
}
// DetermineCureColor -----------------------------------------------------------------------------

// DeterminePlayerMoves ---------------------------------------------------------------------------
GameEngine::PlayerMoves GameEngine::DeterminePlayerMoves(const MovesPerCity & options)
{
	PlayerMoves moves;
	uint8_t itor = 'A';
	uint16_t i = 0;

	// Quit ---------------------------------------------------------------------------------------
	if (options.count(GameEngine::QUIT) > 0)
	{
		std::cout << std::endl << itor++ << ". Quit" << std::endl;
		auto low = options.lower_bound(GameEngine::QUIT);
		auto high = options.upper_bound(GameEngine::QUIT);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			std::cout << "  " << i << " - Quit Game and Auto Save" << std::endl;
		}
	}

	// View Reference Card ------------------------------------------------------------------------
	if (options.count(GameEngine::REFCARD) > 0)
	{
		std::cout << std::endl << itor++ << ". Reference Card" << std::endl;
		auto low = options.lower_bound(GameEngine::REFCARD);
		auto high = options.upper_bound(GameEngine::REFCARD);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			std::cout << "  " << i << " - View reference card" << std::endl;
		}
	}

	// Peak Infection Discard Pile ----------------------------------------------------------------
	if (options.count(GameEngine::PEAK_INFECTION_DISCARD) > 0)
	{
		std::cout << std::endl << itor++ << ". Infection Discard Pile" << std::endl;
		auto low = options.lower_bound(GameEngine::PEAK_INFECTION_DISCARD);
		auto high = options.upper_bound(GameEngine::PEAK_INFECTION_DISCARD);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			std::cout << "  " << i << " - Peak the infection deck's discard pile" << std::endl;
		}
	}

	// Peal Player Discard Pile -------------------------------------------------------------------
	if (options.count(GameEngine::PEAK_PLAYER_DISCARD) > 0)
	{
		std::cout << std::endl << itor++ << ". Player Discard Pile" << std::endl;
		auto low = options.lower_bound(GameEngine::PEAK_PLAYER_DISCARD);
		auto high = options.upper_bound(GameEngine::PEAK_PLAYER_DISCARD);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			std::cout << "  " << i << " - Peak the player deck's discard pile" << std::endl;
		}
	}

	// Drive --------------------------------------------------------------------------------------
	if (options.count(GameEngine::DRIVE_FERRY) > 0)
	{
		std::cout << std::endl << itor++ << ". Drive/Ferry" << std::endl;
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
		std::cout << std::endl << itor++ << ". Direct Flight" << std::endl;
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
		std::cout << std::endl << itor++ << ". Charter Flight" << std::endl;
		auto low = options.lower_bound(GameEngine::CHARTER);
		auto high = options.upper_bound(GameEngine::CHARTER);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - From " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Shuttle Flight -----------------------------------------------------------------------------
	if (options.count(GameEngine::SHUTTLE) > 0)
	{
		std::cout << std::endl << itor++ << ". Shuttle Flight" << std::endl;
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
		std::cout << std::endl << itor++ << ". Treat Disease" << std::endl;
		auto low = options.lower_bound(GameEngine::TREATDISEASE);
		auto high = options.upper_bound(GameEngine::TREATDISEASE);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - In " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// Build Research Center ----------------------------------------------------------------------
	if (options.count(GameEngine::BUILDRC) > 0)
	{
		std::cout << std::endl << itor++ << ". Build Research Center" << std::endl;
		auto low = options.lower_bound(GameEngine::BUILDRC);
		auto high = options.upper_bound(GameEngine::BUILDRC);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - In " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	// Share Knowledge --------–-------------------------------------------------------------------
	if (options.count(GameEngine::SHARECARD) > 0)
	{
		std::cout << std::endl << itor++ << ". Share Knowledge" << std::endl;
		auto low = options.lower_bound(GameEngine::SHARECARD);
		auto high = options.upper_bound(GameEngine::SHARECARD);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - In " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}
	// Discover Cure ------------------------------------------------------------------------------
	if (options.count(GameEngine::CUREDISEASE) > 0)
	{
		std::cout << std::endl << itor++ << ". Discover a Cure" << std::endl;
		auto low = options.lower_bound(GameEngine::CUREDISEASE);
		auto high = options.upper_bound(GameEngine::CUREDISEASE);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}


	// EventCard Airlift---------------------------------------------------------------------------
	if (options.count(GameEngine::AIRLIFT) > 0)
	{
		std::cout << std::endl << itor++ << ". Airlift" << std::endl;
		auto low = options.lower_bound(GameEngine::AIRLIFT);
		auto high = options.upper_bound(GameEngine::AIRLIFT);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - From " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// EventCard Resiliant Population -------------------------------------------------------------
	if (options.count(GameEngine::RESILLIENT) > 0)
	{
		std::cout << std::endl << itor++ << ". Resiliant Population" << std::endl;
		auto low = options.lower_bound(GameEngine::RESILLIENT);
		auto high = options.upper_bound(GameEngine::RESILLIENT);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - To " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// EventCard Forecast -------------------------------------------------------------------------
	if (options.count(GameEngine::FORECAST) > 0)
	{
		std::cout << std::endl << itor++ << ". Forecast" << std::endl;
		auto low = options.lower_bound(GameEngine::FORECAST);
		auto high = options.upper_bound(GameEngine::FORECAST);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - From " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// EventCard QuietNight -----------------------------------------------------------------------
	if (options.count(GameEngine::QUIETNIGHT) > 0)
	{
		std::cout << std::endl << itor++ << ". Quiet Night" << std::endl;
		auto low = options.lower_bound(GameEngine::QUIETNIGHT);
		auto high = options.upper_bound(GameEngine::QUIETNIGHT);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			City* city = m_Board.m_Map.GetCityWithID(it->second);
			std::cout << "  " << i << " - From " << city->GetCityName() << " containing " << city->GetNumberOfCubes() << " disease cubes." << std::endl;
		}
	}

	// EventCard Government Grant -----------------------------------------------------------------
	if (options.count(GameEngine::GOVTGRANT) > 0)
	{
		std::cout << std::endl << itor++ << ". Government Grant" << std::endl;
		auto low = options.lower_bound(GameEngine::GOVTGRANT);
		auto high = options.upper_bound(GameEngine::GOVTGRANT);

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

// ExecuteMove ------------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteMove(const uint16_t& pos, const MoveOptions & opt, const CityList::CityID & cityID)
{
	switch (opt)
	{
	case QUIT:
		return ExecuteQuit(pos, cityID);
	case REFCARD:
		return ExecuteViewRefCard(pos, cityID);
	case PEAK_INFECTION_DISCARD:
		return ExecutePeakInfectionDiscard(pos, cityID);
	case PEAK_PLAYER_DISCARD:
		return ExecutePeakPlayerDiscard(pos, cityID);
	case DRIVE_FERRY:
		return ExecuteDriveFerry(pos, cityID);
	case FLIGHT:
		return ExecuteDirectFlight(pos, cityID);
	case CHARTER:
		return ExecuteCharterFlight(pos, cityID);
	case SHUTTLE:
		return ExecuteShuttleFlight(pos, cityID);
	case TREATDISEASE:
		return ExecuteTreateDisease(pos, cityID);
	case BUILDRC:
		return ExecuteBuildResearchCenter(pos, cityID);
	case SHARECARD:
		return ExecuteShareKnowledge(pos, cityID);
	case CUREDISEASE:
		return ExecuteCureDisease(pos, cityID);
	case AIRLIFT:
		return ExecuteAirLift(pos, cityID);
	case RESILLIENT:
		return ExecuteResillentPopulation(pos, cityID);
	case FORECAST:
		return ExecuteForecast(pos, cityID);
	case QUIETNIGHT:
		return ExecuteQuietNight(pos, cityID);
	case GOVTGRANT:
		return ExecuteGovernmentGrant(pos, cityID);
	default:
		return 1;
	}
}
// ExecuteMove ------------------------------------------------------------------------------------

// ExecuteQuit ------------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteQuit(const uint16_t & pos, const CityList::CityID & cityID)
{
	pos; // unused, keept for normalization
	cityID; // unused, keept for normalization
	std::cout << "Are you sure? Yes=1 No=0" << std::endl;
	uint16_t selection = GetUserInput(0, 1);
	if (selection == 0)
	{
		//SaveGame();
		throw GameQuitException();
	}
	return 0;
}
// ExecuteQuit ------------------------------------------------------------------------------------

// ExecuteViewRefCard -----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteViewRefCard(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	std::cout << m_Players.at(pos)->m_RefCard.GetCardInfo() << std::endl;
	return 0;
}
// ExecuteViewRefCard -----------------------------------------------------------------------------

// ExecutePeakInfectionDiscard --------------------------------------------------------------------
uint16_t GameEngine::ExecutePeakInfectionDiscard(const uint16_t & pos, const CityList::CityID & cityID)
{
	pos; // unused, keept for normalization
	cityID; // unused, keept for normalization
	auto discard = m_Board.m_InfecDeck.GetDiscardPile();
	size_t counter = discard.size();
	std::cout << std::endl << "Infection deck (recent to oldest)" << std::endl;
	for(auto itor = discard.crbegin(); itor != discard.crend(); itor++)
	{
		std::cout << counter-- << ": " << Card::GetCardName(*itor) << std::endl;
	}
	std::cout << std::endl;
	return 0;
}
// ExecutePeakInfectionDiscard --------------------------------------------------------------------

// ExecutePeakPlayerDiscard -----------------------------------------------------------------------
uint16_t GameEngine::ExecutePeakPlayerDiscard(const uint16_t & pos, const CityList::CityID & cityID)
{
	pos; // unused, keept for normalization
	cityID; // unused, keept for normalization
	auto discard = m_Board.m_PlayerDeck.GetDiscardPile();
	size_t counter = discard.size();
	std::cout << std::endl << "Infection deck (recent to oldest)" << std::endl;
	for (auto itor = discard.crbegin(); itor != discard.crend(); itor++)
	{
		std::cout << counter-- << ": " << Card::GetCardName(*itor) << std::endl;
	}
	std::cout << std::endl;
	return 0;
}
// ExecutePeakPlayerDiscard -----------------------------------------------------------------------

// ExecuteDriveFerry ------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteDriveFerry(const uint16_t & pos, const CityList::CityID & cityID)
{
	std::stringstream ss;
	ss << std::hex << cityID;
	m_Players.at(pos)->ChangeCity(ss.str());
	m_Players.at(pos)->PrintInfo();
	return 1;
}
// ExecuteDriveFerry ------------------------------------------------------------------------------

// ExecuteDirectFlight ----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteDirectFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID));
	std::stringstream ss;
	ss << std::hex << cityID;
	m_Players.at(pos)->ChangeCity(ss.str());
	m_Players.at(pos)->PrintInfo();
	m_Players.at(pos)->PrintHand();
	return 1;
}
// ExecuteDirectFlight ----------------------------------------------------------------------------

// ExecuteCharterFlight ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteCharterFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(m_Players.at(pos)->GetCityID()));
	std::stringstream ss;
	ss << std::hex << cityID;
	m_Players.at(pos)->ChangeCity(ss.str());
	m_Players.at(pos)->PrintInfo();
	m_Players.at(pos)->PrintHand();
	return 1;
}
// ExecuteCharterFlight ---------------------------------------------------------------------------

// ExecuteShuttleFlight ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteShuttleFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	std::stringstream ss;
	ss << std::hex << cityID;
	m_Players.at(pos)->ChangeCity(ss.str());
	m_Players.at(pos)->PrintInfo();
	return 1;
}
// ExecuteShuttleFlight ---------------------------------------------------------------------------

// ExecuteTreateDisease ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteTreateDisease(const uint16_t & pos, const CityList::CityID & cityID)
{

	City* city = m_Board.m_Map.GetCityWithID(cityID);
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
	return 1;
}
// ExecuteTreateDisease ---------------------------------------------------------------------------

// ExecuteBuildResearchCenter ---------------------------------------------------------------------
uint16_t GameEngine::ExecuteBuildResearchCenter(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID));
	AddResearchCenter(pos, cityID);
	return 1;
}
// ExecuteBuildResearchCenter ---------------------------------------------------------------------

// AddResearchCenter ------------------------------------------------------------------------------
void GameEngine::AddResearchCenter(const uint16_t& pos, const CityList::CityID& cityID)
{
	pos; // unused but kept for formality
	if (m_Board.m_Centers.GetCenters().size() < 7)
	{
		m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(cityID));
		std::cout << "New Research Center in: " << m_Board.m_Map.GetCityWithID(cityID)->GetCityName() << std::endl;
	}
	else
	{
		std::cout << "Remove Existing Center..." << std::endl;
		uint16_t j = 0;
		for each(ResearchCenter rc in m_Board.m_Centers.GetCenters())
		{
			std::cout << j++ << ": ";
			rc.GetCity()->PrintInformation();
		}
		uint16_t selection = GetUserInput(0, j - 1);

		m_Board.m_Centers.RemoveStation(selection);
		m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(cityID));
		std::cout << "New Research Center in: " << m_Board.m_Map.GetCityWithID(cityID)->GetCityName() << std::endl;
	}
}
// AddResearchCenter ------------------------------------------------------------------------------

// ExecuteShareKnowledge --------------------------------------------------------------------------
uint16_t GameEngine::ExecuteShareKnowledge(const uint16_t & pos, const CityList::CityID & cityID)
{
	if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
	{
		ExecuteShareKnowledgeAsResearcher(pos);
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
				return 1;
			}
		}
	}
	return 1;
}
// ExecuteShareKnowledge --------------------------------------------------------------------------

// ExecuteShareKnowledgeAsResearcher --------------------------------------------------------------
void GameEngine::ExecuteShareKnowledgeAsResearcher(const uint16_t & pos)
{
	m_Players.at(pos)->PrintHand();
	std::cout << "Which card would you like to share..." << std::endl;
	uint16_t selection = GetUserInput(0 , (uint16_t)m_Players.at(pos)->m_Hand.size()-1);

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
// ExecuteShareKnowledgeAsResearcher --------------------------------------------------------------

// ExecuteCureDisease -----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteCureDisease(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization

	Color cc = DetermineCureColor(pos);
	if (cc != Color::INVALID)
	{
		m_Board.m_Cures.CureDiscover(cc);
		for (size_t k = 0; k < m_Players.at(pos)->m_Hand.size(); k += 1)
		{
			if (PlayerCardFactory::IsaCityCard(m_Players.at(pos)->m_Hand.at(k)->GetNumID()))
				if (static_cast<CityCard*>(m_Players.at(pos)->m_Hand.at(k))->GetCityColor() == cc)
					m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)k));
			/*
				TODO: this should be counted... its possible to delete extra cards...
				- deletion should be choosen by player...
			*/
		}
	}
	CheckIfGameWon();

	return 1;
}
// ExecuteCureDisease -----------------------------------------------------------------------------

// ExecuteAirLift ---------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteAirLift(const uint16_t& pos, const CityList::CityID& cityID)
{
	cityID; // unused, keept for normalization

	for (size_t l = 0; l < m_Players.at(pos)->m_Hand.size(); l += 1)
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(l)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(l)->GetNumID() == EventCard::AIRLIFT)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)l));
				break;
			}
	}
	std::map<uint16_t, CityList::CityID> secondary;

	std::cout << "Note: All players involved must agree!" << std::endl;
	std::cout << "Select the player to move..." << std::endl; // who do  you want to move
	uint16_t i = 0;
	for each(Player* joeur in m_Players)
	{
		std::cout << i++ << ": ";
		joeur->PrintInfo();
	}

	uint16_t selection = GetUserInput(0,i-1);

	uint16_t j = 0;
	std::cout << "Which city would you like to move " << m_Players.at(selection)->m_Name << " to..." << std::endl;
	for each(City* ville in m_Board.m_Map.GetAllCities())
	{
		if (ville->GetCityID() == m_Players.at(selection)->GetCityID())
			continue;

		std::cout << j << ": ";
		ville->PrintInformation();
		secondary.insert(std::make_pair(j++, ville->GetCityID())); // map of every other city + pick number
	}

	uint16_t pick = GetUserInput(0,j-1);

	std::stringstream ss;
	ss << std::hex << secondary.at(pick);
	m_Players.at(selection)->ChangeCity(ss.str()); // move them to desired city
	m_Players.at(selection)->PrintInfo();

	return 0;
}
// ExecuteAirLift ---------------------------------------------------------------------------------

// ExecuteResillentPopulation ---------------------------------------------------------------------
uint16_t GameEngine::ExecuteResillentPopulation(const uint16_t & pos, const CityList::CityID & cityID)
{
	for (size_t m = 0; m < m_Players.at(pos)->m_Hand.size(); m += 1)
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(m)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(m)->GetNumID() == EventCard::RESILLIENT)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)m));
				break;
			}
	}
	m_Board.m_InfecDeck.ResiliantPopulation((InfectionCard::CardsList)(cityID + InfectionCard::INFECTIONCARD_MIN));
	return 0;
}
// ExecuteResillentPopulation ---------------------------------------------------------------------

// ExecuteForecast --------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteForecast(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	for (size_t n = 0; n < m_Players.at(pos)->m_Hand.size(); n += 1)
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(n)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(n)->GetNumID() == EventCard::FORECAST)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)n));
				break;
			}
	}
	std::cout << "Change forecast..." << std::endl;
	uint16_t selectionA = 0;
	std::deque<InfectionCard*> forecast = m_Board.m_InfecDeck.GetForecast();
	do
	{
		std::cout << "NOTE: Enter 0 as a selection to quit." << std::endl;
		std::cout << " - TOP - " << std::endl;
		for (uint16_t a = 6; a > 0; a -= 1)
		{
			std::cout << a << ": " << forecast.at(a - 1)->GetCardInfo() << std::endl;
		}
		std::cout << " - BOTTOM - " << std::endl;

		std::cout << "Which card would you like to move? ";
		selectionA = GetUserInput(0, 6);

		if (selectionA == 0)
			break;

		std::cout << "Which card would you like to swap with? ";
		uint16_t selectionB = GetUserInput(1, 6);

		InfectionCard* move = forecast.at(selectionA - 1);
		InfectionCard* swap = forecast.at(selectionB - 1);
		forecast.at(selectionA - 1) = swap;
		forecast.at(selectionB - 1) = move;
	} while (selectionA != 0);

	m_Board.m_InfecDeck.SetForecast(forecast);

	return 0;
}
// ExecuteForecast --------------------------------------------------------------------------------

// ExecuteQuietNight ------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteQuietNight(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	for (size_t o = 0; o < m_Players.at(pos)->m_Hand.size(); o += 1)
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(o)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(o)->GetNumID() == EventCard::QUIETNIGHT)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)o));
				break;
			}
	}

	m_SkipNextInfectionPhase = true;

	return 0;
}
// ExecuteQuietNight ------------------------------------------------------------------------------

// ExecuteGovernmentGrant -------------------------------------------------------------------------
uint16_t GameEngine::ExecuteGovernmentGrant(const uint16_t & pos, const CityList::CityID & cityID)
{
	for (size_t o = 0; o < m_Players.at(pos)->m_Hand.size(); o += 1)
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(o)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(o)->GetNumID() == EventCard::GOVTGRANT)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)o));
				break;
			}
	}
	AddResearchCenter(pos, cityID);
	return 0;
}
// ExecuteGovernmentGrant -------------------------------------------------------------------------

// CheckIfGameOver --------------------------------------------------------------------------------
void GameEngine::CheckIfGameOver()
{
	if (m_Board.m_Cubes.IsAnyEmpty()) throw GameOverException("a cube pile is empty!");
	if (m_Board.m_OutBreak.GetMarker() == 8) throw GameOverException("maximum outbreaks has been reached");
	if (m_Board.m_PlayerDeck.IsDeckEmpty()) throw GameOverException("the player deck is empty!");
}
// CheckIfGameOver --------------------------------------------------------------------------------

// CheckIfGameWon ---------------------------------------------------------------------------------
void GameEngine::CheckIfGameWon()
{
	if (m_Board.m_Cures.IsAllCuresDiscovered()) throw GameWonException("all Cures have been discovered!");
}
// CheckIfGameWon ---------------------------------------------------------------------------------

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

	// Research Centers ---------------------------------------------------------------------------
	myfile << m_Board.m_Centers.GetSaveOutput();
	myfile << "\n";

	// Infection Log ------------------------------------------------------------------------------
	myfile << m_Log->GetSaveOutput();
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
		//SaveGame();
		std::cout << "AutoSave Completed" << std::endl;
	}

	uint16_t i = 0;
	std::map<uint16_t, bfs::directory_entry> files;
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

	if (files.size() == 0) // fail if no load options
	{
		std::cout << "No Load options avaliable." << std::endl;
		return;
	}

	uint16_t selection = GetUserInput(0, i - 1);

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

		InfectionDeck::Builder infecdeckbuilder;
		infecdeckbuilder.ParseDeck(infecdeck).ParseDiscard(infecdiscard);

		m_Board.m_InfecDeck.InputLoadedGame(infecdeckbuilder.GetDeck(), infecdeckbuilder.GetDiscard());
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

		PlayerDeck::Builder playerdeckbuilder;
		playerdeckbuilder.ParseDeck(playdeck).ParseDiscard(playdiscard);

		m_Board.m_PlayerDeck.InputLoadedGame(playerdeckbuilder.GetDeck(), playerdeckbuilder.GetDiscard());
	}

	// Role Cards ---------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string role(buffer);
		delete[] buffer;
		buffer = nullptr;

		RoleDeck::Builder roledeckbuilder;
		roledeckbuilder.ParseDeck(role);

		m_Board.m_RoleDeck.InputLoadedGame(roledeckbuilder.GetDeck());
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
					city->AddCube(m_Board.m_Cubes.TakeCube(Color::RED));
					break;
				case '1':
					city->AddCube(m_Board.m_Cubes.TakeCube(Color::BLUE));
					break;
				case '2':
					city->AddCube(m_Board.m_Cubes.TakeCube(Color::YELLOW));
					break;
				case '3':
					city->AddCube(m_Board.m_Cubes.TakeCube(Color::BLACK));
					break;
				default:
					break;
				}
			}
			CheckIfGameOver();
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
		for (uint16_t r = 0; r < 4; r += 1)
		{
			size_t slash = players.find("/");
			if (slash == std::string::npos) break;
			std::string play = players.substr(0, slash);
			players = players.substr(slash + 2);

			Player::Builder playerbuilder;
			playerbuilder.ParsePlayer(play);

			gamers.emplace_back(playerbuilder.GetPlayer());
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

		CureMakers::Builder curesbuilder;
		curesbuilder.ParseBlackCure(rate).ParseBlueCure(rate).ParseRedCure(rate).ParseYellowCure(rate);

		m_Board.m_Cures.InputLoadedGame(curesbuilder.GetRedCure(), curesbuilder.GetBlueCure(), curesbuilder.GetYellowCure(), curesbuilder.GetBlackCure());
	}

	// Infection Rate -----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string rate(buffer);
		delete[] buffer;
		buffer = nullptr;

		InfectionRate::Builder infecratebuilder;
		infecratebuilder.ParseInfectionRate(rate);

		m_Board.m_InfectRate.InputLoadedGame(infecratebuilder.GetPosition());
		
	}

	// Outbreak Marker ----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string marker(buffer);
		delete[] buffer;
		buffer = nullptr;

		OutbreakMarker::Builder outbreakmarkerbuilder;
		outbreakmarkerbuilder.ParseOutbreakMarker(marker);

		m_Board.m_OutBreak.InputLoadedGame(outbreakmarkerbuilder.GetPosition());
	}

	//ResearchCenters -----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string centers(buffer);
		delete[] buffer;
		buffer = nullptr;

		std::vector<ResearchCenter> m_centers;
		for (uint16_t r = 0; r < 6; r += 1)
		{
			size_t slash = centers.find("/");
			if (slash == std::string::npos) break;
			std::string city = centers.substr(0, slash);
			centers = centers.substr(slash + 2);
			std::stringstream ss(city);
			uint64_t num = 0;
			ss >> std::hex >> num;
			m_centers.emplace_back(m_Board.m_Map.GetCityWithID((CityList::CityID)num));
		}
		m_Board.m_Centers.InputLoadedGame(m_centers);
	}

	// Infection Log ------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string log(buffer);
		delete[] buffer;
		buffer = nullptr;

		InfectionLog::Builder infectlognuilder;
		m_Log->InputLoadedGame(infectlognuilder.GetLog());
	}

	m_PreGameComplete = true;
}
// LoadGame ---------------------------------------------------------------------------------------


void GameEngine::Notify(std::string name, uint16_t cubes)
{
	for each(InfectionLog* obv in m_observers)
	{
		if (obv == nullptr) continue;
		obv->Update(name, cubes);
	}
}

// Initialize -------------------------------------------------------------------------------------
void GameEngine::Initialize()
{
	BoardSetup();			 //DO NOT TOUCH ORDER !
	PlayersSetup();			 //DO NOT TOUCH ORDER !
	DifficultySetup();		 //DO NOT TOUCH ORDER !

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
		for (uint16_t i = 0; /* no limit */; i += 1)
		{
			std::cout << "\n\nGet ready " << m_Players.at(i % (uint16_t)m_Players.size())->GetName() << " you're up next!\nPress 'enter' to continue...";
			std::cin.get();
			TurnSequence(i % (uint16_t)m_Players.size());
		}
	}
	catch (const GameOverException& e)
	{
		std::cout << "\n\n ---- GAME OVER! ----\n  You lost due to: " << e.what() << std::endl;
	}
	catch (const GameWonException& e)
	{
		std::cout << "\n\n ---- Congradulations! ----\n  You won due to: " << e.what() << std::endl;
	}
	catch (const GameQuitException& e)
	{
		std::cout << "\n\n ---- Good Bye! ----\n  " << e.what() << std::endl;
	}
	
}
// Launch -----------------------------------------------------------------------------------------
