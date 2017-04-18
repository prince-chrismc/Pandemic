#include <sstream>  //std::stringstream
#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include <iostream> //std::cout
#include "boost\filesystem.hpp" //dir
#include "GameEngine.h"
namespace bfs = boost::filesystem;

GameEngine::GameEngine() : m_Board(), m_Players(), m_PlayersObservers(), m_LogNotifier(), m_Log(&m_LogNotifier), m_StatsNotify(), m_GameStats(new GameStatisticsClocked(new GameStatisticsExtended(new GameStatistics(&m_Players, &m_Board.m_Map, &m_Board.m_Centers, &m_Board.m_PlayerDeck, &m_Board.m_InfecDeck, &m_StatsNotify, new GameStatsPerAction())))), m_Filename(MakeFileName()), m_PreGameComplete(false), m_SkipNextInfectionPhase(false), m_TurnCounter(0)
{
	// print basic game opening message
	std::cout << "\n               -------------- PANDEMIC -------------\nDo you have what it takes to save humanity? As skilled members of a disease - fighting team, you must\nkeep four deadly diseases at bay while discovering their cures.\nYou and your teammates will travel across the globe, treating infections while finding resources for\ncures. You must work together, using your individual strengths, to succeed.The clock is ticking as\noutbreaks and epidemics fuel the spreading plagues.\nCan you find all four cures in time? The fate of humanity is in your hands!\n\n" << std::endl;

	m_LogNotifier.RegistarObserver(&m_Log); // to notify on infections
	m_Players.RegistarObserver(m_GameStats);
	m_Board.m_Map.WorldMapStatisticsSubject::RegistarObserver(m_GameStats);
	m_Board.m_Centers.ResearchStatisticsSubject::RegistarObserver(m_GameStats);
	m_Board.m_PlayerDeck.RegistarObserver(m_GameStats);
	m_Board.m_InfecDeck.RegistarObserver(m_GameStats);
	m_StatsNotify.RegistarObserver(m_GameStats);
}

GameEngine::~GameEngine()
{
	for each(PlayerObserver* obv in m_PlayersObservers) // delete players observers
	{
		if (obv != nullptr)
		{
			delete obv;
			obv = nullptr;
		}
	}
	m_PlayersObservers.clear();
}

// MakeFileName -----------------------------------------------------------------------------------
std::string GameEngine::MakeFileName()
{
	time_t t = time(0);
	struct tm* now = localtime(&t); // get local time

	// build file path + name with padding
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
	// with name complete the details 
	m_Players.emplace_back(new Player(newPlayerName, m_Board.m_RoleDeck.DrawCard()));
	m_PlayersObservers.emplace_back(new PlayerObserver(m_Players.back())); // make new player observer with the last player added
	m_Players.back()->RegistarObserver(m_PlayersObservers.back()); // give latest player his observer's pointer
}
// RegisterPlayer ---------------------------------------------------------------------------------

// PlayerSetup ------------------------------------------------------------------------------------
void GameEngine::PlayersSetup()
{
	std::cout << "How many players will there be?" << std::endl; //players
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
	std::shuffle(m_Players.begin(), m_Players.end(), g); // shuffle players for fun

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
	std::cout << "Choose your difficulty...\n 1. Introductory 2. Standard 3. Heroic\n"; // relates to number of epidemic cards
	uint16_t dif = GetUserInput(1, 3);

	m_Board.m_PlayerDeck.IncreaseDifficulty(dif); // add epidemics
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
	m_StatsNotify.Notify(Priority::TURN);
	SaveGame(); // auto save
}
// TurnSequence -----------------------------------------------------------------------------------

// GetUserInput -----------------------------------------------------------------------------------
const uint16_t GameEngine::GetUserInput(const uint16_t & lower, const uint16_t & upper)
{
	// this is a gneral utility function to get a valid input between two values (inclusively)
	// adding this removed aprox. 200 lines of code lol
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
		m_Board.m_Map.MapSubject::Notify(); // force map print
		m_Players.at(pos)->Notify(); //force play details print

		// check what player can do from list of all possible game moves
		MovesPerCity options = CalculatePlayerOpt(pos);
		std::cout << "Select your desired move from the list below... (#)" << std::endl;
		PlayerMoves moves = DeterminePlayerMoves(options);
		uint16_t selection = GetUserInput(1, (uint16_t)moves.size());

		// execute thier selection
		i += ExecuteMove(pos, moves.at(selection).first, moves.at(selection).second);
		m_StatsNotify.Notify(Priority::ACTION);
	}
	m_StatsNotify.Notify(Priority::PHASE);

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
			m_Players.at(pos)->Notify();
			//if has an event card, would you like to play it?
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
		m_StatsNotify.Notify(Priority::ACTION);
	}
	m_StatsNotify.Notify(Priority::PHASE);
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

	for (size_t i = 0; i < m_Board.m_InfectRate.GetRate(); i++) // based on infection rate
	{
		InfectCity(); // do the obvious
		CheckIfGameOver(); // check if game over .... these functions have good names xD
		m_StatsNotify.Notify(Priority::ACTION);
	}
	m_StatsNotify.Notify(Priority::PHASE);
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

	if (m_Board.m_Cures.IsEradicated(c)) // if eradicated do NOT add cubes
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
		case RoleList::QUARANTINE: // dont add cubes
			return;
		case RoleList::MEDIC:
			if (m_Board.m_Cures.IsCured(c)) // dont add cubes iff cured
				return;
		default:
			break;
		}
	}

	uint16_t cubesActuallyAdded = 0;
	for (size_t i = 0; i < cubesToAdd; i++) // add as many cubes as need
	{
		if (city->GetNumberOfCubes(city->GetCityColor()) == 3) // if city has 3
		{
			if(cubesActuallyAdded > 0) 
				m_LogNotifier.AddLatestInfection(city->GetCityName(), cubesActuallyAdded); // if cubes were added notify infect log

			Outbreak(city); // outbreak occures!!!
			return;
		}
		else
		{
			city->AddCube(m_Board.m_Cubes.TakeCube(city->GetCityColor())); // lets add a cube!
			cubesActuallyAdded += 1;
		}
		CheckIfGameOver();
	}

	m_LogNotifier.AddLatestInfection(city->GetCityName(), cubesActuallyAdded); // record in log
}
// InfectCity -------------------------------------------------------------------------------------

// IsQuarentineSpecialistNearBy -------------------------------------------------------------------
bool GameEngine::IsQuarentineSpecialistNearBy(City * city)
{
	//utility fuction 
	for each(Player* joeur in m_Players)
	{
		if (joeur->GetRoleID() == RoleList::QUARANTINE) // if any player is quarantine spec
		{
			CityList::CityID cid = joeur->GetCityID();
			for each(City* ville in city->GetNearByCities()) // look if they are in any near by ones
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
void GameEngine::Outbreak(City* city, std::vector<City*> skip)
{
	// pre conditions
	if (IsQuarentineSpecialistNearBy(city)) // make sure quarantine specialist isnt nearby
		return;

	if (m_Board.m_Cures.IsCured(city->GetCityColor())) //worth checking for medic?
	{
		for each(Player* joeur in m_Players) // lets figure out the the medic is in the city
		{
			if (joeur->GetCityID() == city->GetCityID())
				if (joeur->GetRoleID() == RoleList::MEDIC)
					return;
		}
	}		

	// main scenario
	std::cout << "  --- OUTBREAK " << std::string((skip.size() > 0) ? "CONTINUED " : "") << "--- " << city->GetCityName() << " --- " << std::endl;
	m_Board.m_OutBreak.IncreaseRate();
	std::cout << "Outbreak Marker: " << m_Board.m_OutBreak.GetMarker() << std::endl;
	CheckIfGameOver();

	for each(City* connected in city->GetNearByCities())
	{
		bool alreadyhit = false; // lets check if the connected city has already been hit in the chain
		if (skip.size() > 0) // chainning is happening
			for each(City* skipped in skip)
				if (connected->GetCityID() == skipped->GetCityID()) // compare current connected with alreay hit cities
					alreadyhit = true;

		if(alreadyhit) continue; // if indeed a chainned city let skip it 

		if (connected->GetNumberOfCubes(city->GetCityColor()) == 3) 
		{
			// chain of outbreaks!
			skip.emplace_back(connected); // mark as to be skipped 
			Outbreak(connected, skip); 
		}
		else
		{
			connected->AddCube(m_Board.m_Cubes.TakeCube(city->GetCityColor())); // let's add a cube baby
			m_LogNotifier.AddLatestInfection(connected->GetCityName(), 1); // record in log
		}
	CheckIfGameOver();
	}
	skip.clear();
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
	City::CityID cid = (City::CityID)(ic->GetNumID() - InfectionCard::INFECTIONCARD_MIN);
	City* city = m_Board.m_Map.GetCityWithID(cid);

	if (m_Board.m_Cures.IsNotEradicated(citycolor) && !IsQuarentineSpecialistNearBy(city))
	{
		std::cout << "Occurring in: " << city->GetCityName() << std::endl;
		bool nooutbreak = true;
		for (uint16_t i = 0; i < 3; i += 1)
		{
			// 2.1. Otbreaks if Need be
			if (city->GetNumberOfCubes(citycolor) == 3) // let have ab outbreak!
			{
				nooutbreak = false;
				m_LogNotifier.AddLatestInfection(city->GetCityName(), i); // record in log
				Outbreak(city);
				break;
			}

			city->AddCube(m_Board.m_Cubes.TakeCube(citycolor)); // add a cube
			CheckIfGameOver();
		}
		if(nooutbreak) m_LogNotifier.AddLatestInfection(city->GetCityName(), 3); // if no outbreak occured update log

	}
	delete ic; ic = nullptr;

	// 3. Intensify reshuffle infect discard and add on top of deck
	m_Board.m_InfecDeck.Intensify();
}
// Epidemic ---------------------------------------------------------------------------------------

// CalculatePlayerOpt -----------------------------------------------------------------------------
GameEngine::MovesPerCity GameEngine::CalculatePlayerOpt(const uint16_t & pos)
{
	MovesPerCity options;

	// Quit ---------------------------------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::QUIT, m_Players.at(pos)->GetCityID()));

	// Settings Frequency -------------------------------------------------------------------------
	options.insert(std::make_pair(GameEngine::SETTINGS_FREQ, m_Players.at(pos)->GetCityID()));

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

	// Contingency Planer -------------------------------------------------------------------------
	/*
	if(m_Players.at(pos)->GetRolID() == RoleList::CONTI..)
	{
	options.insert(std::make_pair(GameEngine::CONTIN, m_Players.at(pos)->GetCityID()))
	}
	*/

	// Operations Expert --------------------------------------------------------------------------
	/*
	if(m_Players.at(pos)->GetRolID() == RoleList::OP && !IsRCin(m_Players.at(pos)->GetCityID()))
		options.insert(std::make_pair(GameEngine::CONTIN, m_Players.at(pos)->GetCityID()))

	foreach(CityList::CityID id in CalculateOperationsExpertRCtoanycity(pos)
	{
	options.insert(std::make_pair(GameEngine::OE TO ANY CITY, m_Players.at(pos)->GetCityID()))
	}
	*/

	// Dispatcher ---------------------------------------------------------------------------------
	/*
	foreach(CityList::CityID id in CalculateDispatcherMovePAwntoPAwn(pos)
	{
	options.insert(std::make_pair(GameEngine::dispatchpawn topawn, id))
	}

	foreach(CityList::CityID id in CalculateDispatcherMoveAsOwn(pos)
	{
	options.insert(std::make_pair(GameEngine::dispatchmoveasown, id))
	}
	*/

	return options;
}
// CalculatePlayerOpt -----------------------------------------------------------------------------

// CalculateDriveCitiesFor ------------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateDriveCitiesFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;
	for each(City* city in m_Board.m_Map.GetCitiesConnectedTo(m_Players.at(pos)->GetCityID()))
	{
		result.emplace_back(city->GetCityID()); // add all connected cities
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
			result.emplace_back((CityList::CityID)(pc->GetNumID() - CityCard::CITYCARD_MIN)); // to all citycards in players hand
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
			if (city->GetCityID() == m_Players.at(pos)->GetCityID()) //skip current city
				continue;

			result.emplace_back(city->GetCityID()); // to every other city
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
	CityList::CityID cid = m_Players.at(pos)->GetCityID(); // get players city
	for each(ResearchCenter rc in m_Board.m_Centers.GetAllCenters()) // scan all RCs
	{
		if (rc.GetCityID() == cid) // if player is in a city with a RC
		{
			IsInACityWithAResearchCEnter = true;
			continue; //skip
		}
		else
		{
			flights.emplace_back(rc.GetCityID());
		}
	}

	if (!IsInACityWithAResearchCEnter) // if player is not in a city with a RC
	{
		flights.clear(); // return nothing
	}
	return flights;
}
// CalculateShuttleFlightsFor ---------------------------------------------------------------------

// CalculateShareKnowlegdeFor ---------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateShareKnowlegdeFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;

	// 1. Giving Cards
	// 1.1 Player is the researcher
	if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos) continue; // skip same player

			if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID()) // two players in the same city
			{
				if (m_Players.at(index)->m_Hand.size() < 7) // other guys hand is not full
				{
					result.emplace_back(m_Players.at(index)->GetCityID());
					return result;
				}
			}
		}
	}

	// 1.2 has current city's matching city card
	if (m_Players.at(pos)->HasCurrentCityCard())
	{
		for (size_t index = 0; index < m_Players.size(); index += 1)
		{
			if (index == pos) continue; // skip same player

			if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID()) // two players in the same city
			{
				if (m_Players.at(index)->m_Hand.size() < 7) // other guys hand is not full
				{
					result.emplace_back(m_Players.at(index)->GetCityID());
					return result;
				}
			}
		}
	}

	// 2. Taking Cards
	// 2.1 Other Player is the researcher
	for (size_t index = 0; index < m_Players.size(); index += 1)
	{
		if (index == pos) continue; // skip same

		if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())  // two players in the same city
		{
			if (m_Players.at(index)->GetRoleID() == RoleList::RESEARCHER)
			{
				if (m_Players.at(pos)->m_Hand.size() < 7) // your hand isnt full
				{
					result.emplace_back(m_Players.at(index)->GetCityID());
					return result;
				}
			}
		}
	}

	// 2.2 Other Player has current city card
	for (size_t index = 0; index < m_Players.size(); index += 1)
	{
		if (index == pos) continue; // skip same player

		if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID()) // two players in the same city
		{
			if (m_Players.at(index)->GetRoleID() != RoleList::RESEARCHER && // other guy isnt Research but has card (prevents double loggging of option)
				m_Players.at(index)->HasCurrentCityCard())
			{
				if (m_Players.at(pos)->m_Hand.size() < 7)  // your hand isnt full
				{
					result.emplace_back(m_Players.at(index)->GetCityID());
					return result;
				}
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

	if(DetermineCureColor(pos) != Color::INVALID) // the player can cure a disease
		if (m_Board.m_Centers.IsaCenterIn(m_Players.at(pos)->GetCityID())) // if his city has a RC
			result.emplace_back(m_Players.at(pos)->GetCityID());

	return result;
}
// CalculateDiscoverCureFor -----------------------------------------------------------------------

// CalculateReseilientPopFor ----------------------------------------------------------------------
std::vector<CityList::CityID> GameEngine::CalculateReseilientPopFor(const uint16_t& pos)
{
	std::vector<CityList::CityID> result;

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID())) // look for event cards
		{
			if(pc->GetNumID() == EventCard::RESILLIENT) // if resilent pop
			{
				for each(InfectionCard::CardsList icID in m_Board.m_InfecDeck.GetDiscardPile()) // add all discard infection cards
				{
					result.emplace_back((CityList::CityID)(icID - InfectionCard::INFECTIONCARD_MIN));
				}
				break;
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

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID())) // look for event cards
		{
			if (pc->GetNumID() == EventCard::AIRLIFT) // if airlift 
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				break;
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

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID()))  // look for event cards
		{
			if (pc->GetNumID() == EventCard::FORECAST) // if forecast
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				break;
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

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID())) // look for event cards
		{
			if (pc->GetNumID() == EventCard::QUIETNIGHT) // if quiet night
			{
				result.emplace_back(m_Players.at(pos)->GetCityID());
				break;
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

	for each(PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(pc->GetNumID())) // look for event cards
		{
			if (pc->GetNumID() == EventCard::GOVTGRANT) // if govt grant
			{
				for each(City* city in m_Board.m_Map.GetAllCities()) // get all cities 
				{
					CityList::CityID cid = city->GetCityID();
					result.emplace_back(cid); // save to list

					for each(ResearchCenter rc in m_Board.m_Centers.GetAllCenters()) // if that city already has an RC...
					{
						if (rc.GetCityID() == cid)
						{
							result.erase(result.end()-1); // ... remove it from the list
							break;
						}
					}
				}
				break;
			}
		}
	}
	return result;
}
// CalculateGovernmentGrantFor --------------------------------------------------------------------

// DetermineCureColor -----------------------------------------------------------------------------
Color GameEngine::DetermineCureColor(const uint16_t& pos)
{
	uint16_t NumOfCardsNeeded = m_Players.at(pos)->GetNumOfCardToDiscoverCure(); // get number of cards to cure (varies for scientist)
	if (m_Players.at(pos)->m_Hand.size() >= NumOfCardsNeeded) // if player even has enough cards
	{
		uint16_t red = 0, blue = 0, yellow = 0, black = 0;
		for each (PlayerCard* pc in m_Players.at(pos)->m_Hand) // scan hand
		{
			if (PlayerCardFactory::IsaCityCard(pc->GetNumID())) // look for city cards
			{
				switch (dynamic_cast<CityCard*>(pc)->GetCityColor()) // cast and check color
				{
				case Color::RED: red++; break; // incr counters
				case Color::BLUE: blue++; break;
				case Color::YELLOW: yellow++; break;
				case Color::BLACK: black++; break;
				}
			}
		}

		// since it impossible to be able to cure more than 1
		if (red >= NumOfCardsNeeded) // check which one (if any) is able to be cured 
			return Color::RED; // and return the color
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
	uint8_t itor = 'A'; // letter for categories
	uint16_t i = 0; // index for selection

	// format
	// if option exist (ie. count > 0)
	// for that range (low --> high) inclusive
	// index all options and print with cities info


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

	// Settings Frequency -------------------------------------------------------------------------
	if (options.count(GameEngine::SETTINGS_FREQ) > 0)
	{
		std::cout << std::endl << itor++ << ". Change Statistics Display Frequency" << std::endl;
		auto low = options.lower_bound(GameEngine::SETTINGS_FREQ);
		auto high = options.upper_bound(GameEngine::SETTINGS_FREQ);

		for (auto it = low; it != high; it++)
		{
			moves.insert(std::make_pair(++i, *it));
			std::cout << "  " << i << " - Change the settings" << std::endl;
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


	// Contingency Planer -------------------------------------------------------------------------
	/*
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
	*/

	// Operations Expert --------------------------------------------------------------------------
	/*
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
	*/

	// Operations Expert --------------------------------------------------------------------------
	/*
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
	*/

	// Dispatcher ---------------------------------------------------------------------------------
	/*
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
	*/

	return moves;
}
// DeterminePlayerMoves ---------------------------------------------------------------------------

// ExecuteMove ------------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteMove(const uint16_t& pos, const MoveOptions & opt, const CityList::CityID & cityID)
{
	// deligates execute to specialized methods
	switch (opt)
	{
	case QUIT:
		return ExecuteQuit(pos, cityID);
	case SETTINGS_FREQ:
		return ExecuteChangeFrequency(pos, cityID);
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
	std::cout << "Are you sure? Yes=1 No=0" << std::endl; // prompt in case typo
	uint16_t selection = GetUserInput(0, 1);
	if (selection == 1) // if yes do it
	{
		SaveGame();
		throw GameQuitException();
	}
	return 0;
}
// ExecuteQuit ------------------------------------------------------------------------------------

// ExecuteChangeFrequency -------------------------------------------------------------------------
uint16_t GameEngine::ExecuteChangeFrequency(const uint16_t & pos, const CityList::CityID & cityID)
{
	pos; // unused, keept for normalization
	cityID; // unused, keept for normalization
	std::cout << "What display setting would you like? Per...\n- Action=0\n- Phase=1\n- Turn=2\n"; // prompt for options
	uint16_t selection = GetUserInput(0, 2);
	switch (selection)
	{
	case 0:
		m_GameStats->ChangeFrequency(new GameStatsPerAction);
		break;
	case 1:
		m_GameStats->ChangeFrequency(new GameStatsPerPhase);
		break;
	case 2:
		m_GameStats->ChangeFrequency(new GameStatsPerTurn);
		break;
	default:
		break;
	}
	return 0;
}
// ExecuteChangeFrequency -------------------------------------------------------------------------

// ExecuteViewRefCard -----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteViewRefCard(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	std::cout << m_Players.at(pos)->m_RefCard.GetCardInfo() << std::endl; // print ref card
	return 0;
}
// ExecuteViewRefCard -----------------------------------------------------------------------------

// ExecutePeakInfectionDiscard --------------------------------------------------------------------
uint16_t GameEngine::ExecutePeakInfectionDiscard(const uint16_t & pos, const CityList::CityID & cityID)
{
	pos; // unused, keept for normalization
	cityID; // unused, keept for normalization
	auto discard = m_Board.m_InfecDeck.GetDiscardPile(); // get all discarded
	size_t counter = discard.size();
	std::cout << std::endl << "Infection deck (recent to oldest)" << std::endl;
	for(auto itor = discard.crbegin(); itor != discard.crend(); itor++) // print the discard backwards to show history
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
	auto discard = m_Board.m_PlayerDeck.GetDiscardPile(); // get all discarded
	size_t counter = discard.size();
	std::cout << std::endl << "Infection deck (recent to oldest)" << std::endl;
	for (auto itor = discard.crbegin(); itor != discard.crend(); itor++) // print the discard backwards to show history
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
	ss << std::hex << cityID;                                  // parse value to string
	m_Players.at(pos)->ChangeCity(ss.str());                   // change players city

	if (m_Players.at(pos)->GetRoleID() == RoleList::MEDIC)     // if its the medic entering
		if (m_Board.m_Cures.IsAnyCured())                     // check if next call is worth it
			ExecuteMedicEnteredCity(cityID);                   // rm cubes of cured diseases

	return 1;
}
// ExecuteDriveFerry ------------------------------------------------------------------------------

// ExecuteMedicEnteredCity ------------------------------------------------------------------------
void GameEngine::ExecuteMedicEnteredCity(const CityList::CityID & cityID)
{
	City* city = m_Board.m_Map.GetCityWithID(cityID);  // get city
	if (m_Board.m_Cures.IsCured(Color::RED))           // check if red is cured
		city->RemoveCubeAsMedic(Color::RED);            // rm all red cubes
	if (m_Board.m_Cures.IsCured(Color::BLACK))			// check if black is cured 
		city->RemoveCubeAsMedic(Color::BLACK);			// pattern repeates 
	if (m_Board.m_Cures.IsCured(Color::YELLOW))		// check if yellow is cured 
		city->RemoveCubeAsMedic(Color::YELLOW);			// pattern repeates 
	if (m_Board.m_Cures.IsCured(Color::BLUE))			// check if blue is cured 
		city->RemoveCubeAsMedic(Color::BLUE);			// pattern repeates 

}
// ExecuteMedicEnteredCity ------------------------------------------------------------------------

// ExecuteDirectFlight ----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteDirectFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID)); // remove that cities card from hand and add to discard pile
	std::stringstream ss;
	ss << std::hex << cityID;									 // parse value to string
	m_Players.at(pos)->ChangeCity(ss.str());					 // change players city

	if (m_Players.at(pos)->GetRoleID() == RoleList::MEDIC)		 // if its the medic entering
		if (m_Board.m_Cures.IsAnyCured())						 // check if next call is worth it
			ExecuteMedicEnteredCity(cityID);					 // rm cubes of cured diseases

	return 1;
}
// ExecuteDirectFlight ----------------------------------------------------------------------------

// ExecuteCharterFlight ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteCharterFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(m_Players.at(pos)->GetCityID())); // remove current cities card from hand and add to discard pile
	std::stringstream ss;
	ss << std::hex << cityID;									// parse value to string
	m_Players.at(pos)->ChangeCity(ss.str());					// change players city

	if (m_Players.at(pos)->GetRoleID() == RoleList::MEDIC)		// if its the medic entering
		if (m_Board.m_Cures.IsAnyCured())						// check if next call is worth it
			ExecuteMedicEnteredCity(cityID);					// rm cubes of cured diseases

	return 1;
}
// ExecuteCharterFlight ---------------------------------------------------------------------------

// ExecuteShuttleFlight ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteShuttleFlight(const uint16_t & pos, const CityList::CityID & cityID)
{
	std::stringstream ss;
	ss << std::hex << cityID;								   // parse value to string
	m_Players.at(pos)->ChangeCity(ss.str());				   // change players city

	if (m_Players.at(pos)->GetRoleID() == RoleList::MEDIC)	   // if its the medic entering
		if (m_Board.m_Cures.IsAnyCured())					   // check if next call is worth it
			ExecuteMedicEnteredCity(cityID);				   // rm cubes of cured diseases

	return 1;
}
// ExecuteShuttleFlight ---------------------------------------------------------------------------

// ExecuteTreateDisease ---------------------------------------------------------------------------
uint16_t GameEngine::ExecuteTreateDisease(const uint16_t & pos, const CityList::CityID & cityID)
{
	City* city = m_Board.m_Map.GetCityWithID(cityID); // get city
	Color removed;
	switch (m_Players.at(pos)->GetRoleID()) // check role
	{
	case RoleList::MEDIC:
		removed = ExecuteTreateDiseaseAsMedic(city); // if medic than remove all cubes of a color ( defaults to greatest qty ) and return color of cubes removed
		break;
	default:
		removed = m_Board.m_Cubes.PlaceCube(city->RemoveCube()); // remove the oldest cube in the city

		if (m_Board.m_Cures.IsCured(removed))
			removed = ExecuteTreateDiseaseForCured(city, removed);
		else
		break;
	}
	city->PrintInformation(); // show new info

	if (m_Board.m_Cures.IsCured(removed)) // if the color of the removed cube has been cured
		if (m_Board.m_Cubes.IsFull(removed)) // and the pile is back to full (ie. no cubes on the feild for that color)
			m_Board.m_Cures.EradicateDisease(removed); // than set that disease to cured

	CheckIfGameOver();
	return 1;
}
// ExecuteTreateDisease ---------------------------------------------------------------------------

// ExecuteTreateDiseaseAsMedic --------------------------------------------------------------------
const Color GameEngine::ExecuteTreateDiseaseAsMedic(City* city)
{
	std::vector<DiseaseCube*> cubes = city->RemoveCubeAsMedic(); // rm most cubes possible
	const Color result = cubes.at(0)->GetColor(); // get the color 
	for each(DiseaseCube* dc in cubes)
	{
		m_Board.m_Cubes.PlaceCube(dc); // return to pile each cube
	}
	return result;
}
// ExecuteTreateDiseaseAsMedic --------------------------------------------------------------------

// ExecuteTreateDiseaseForCured -------------------------------------------------------------------
const Color GameEngine::ExecuteTreateDiseaseForCured(City* city, const Color& color)
{
	std::vector<DiseaseCube*> cubes = city->RemoveCubeForCured(color); // rm all cubes of that color
	const Color removed = cubes.at(0)->GetColor(); // get the color 
	for each(DiseaseCube* dc in cubes)
	{
		m_Board.m_Cubes.PlaceCube(dc); // return to pile each cube
	}
	return color;
}
// ExecuteTreateDiseaseForCured -------------------------------------------------------------------

// ExecuteBuildResearchCenter ---------------------------------------------------------------------
uint16_t GameEngine::ExecuteBuildResearchCenter(const uint16_t & pos, const CityList::CityID & cityID)
{
	m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCard(cityID)); // removes current city card
	AddResearchCenter(pos, cityID); // Add the center
	return 1;
}
// ExecuteBuildResearchCenter ---------------------------------------------------------------------

// AddResearchCenter ------------------------------------------------------------------------------
void GameEngine::AddResearchCenter(const uint16_t& pos, const CityList::CityID& cityID)
{
	pos; // unused but kept for formality
	if (m_Board.m_Centers.GetAllCenters().size() < 6) // is theres less than the max
	{
		m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(cityID)); // add RC (will notify map)
		std::cout << "New Research Center in: " << m_Board.m_Map.GetCityWithID(cityID)->GetCityName() << std::endl; // print new details
	}
	else if (m_Board.m_Centers.GetAllCenters().size() == 6) // max number of RCs 
	{
		std::cout << "Remove Existing Center..." << std::endl; // gotta remove one
		uint16_t j = 0;
		for each(ResearchCenter rc in m_Board.m_Centers.GetAllCenters()) // show all RCs
		{
			std::cout << j++ << ": ";
			rc.GetCity()->PrintInformation();
		}
		uint16_t selection = GetUserInput(0, j - 1);

		m_Board.m_Centers.RemoveStation(selection); // remove selection
		m_Board.m_Centers.AddStation(m_Board.m_Map.GetCityWithID(cityID)); // add new RC (will notify map)
		std::cout << "New Research Center in: " << m_Board.m_Map.GetCityWithID(cityID)->GetCityName() << std::endl;  // print new details
	}
#if _DEBUG
	else // if there is some how more than 6 RCs than throw error when in debug
	{
		throw GameErrorException("Some how exceeded max number of RCs"); // uncaught allows me to trace+debug
	}
#endif // _DEBUG
}
// AddResearchCenter ------------------------------------------------------------------------------

// ExecuteShareKnowledge --------------------------------------------------------------------------
uint16_t GameEngine::ExecuteShareKnowledge(const uint16_t & pos, const CityList::CityID & cityID)
{
	for (size_t index = 0; index < m_Players.size(); index += 1) // scan players
	{
		if (index == pos) continue; // skip urself

		if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID())
		{
			// ultra rare case --------------------------------------------------------------------
			if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER && // both can share
				m_Players.at(index)->HasCurrentCityCard())
			{
				std::cout << "Who would like to share?\n 0:" << m_Players.at(pos)->GetName() << " (Researcher) or...\n1:" << // promt for whos giving
					m_Players.at(index)->GetName() << " (with current city card)" << std::endl;
				uint16_t selection = GetUserInput(0, 1);

				if (selection == 0)
					ExecuteShareKnowledgeAsResearcher(pos); // 2.1
				else
					m_Players.at(pos)->AddCard(m_Players.at(index)->RemoveCard(cityID)); // 1.2

			}
			if (m_Players.at(index)->GetRoleID() == RoleList::RESEARCHER && // both can share other order this time
				m_Players.at(pos)->HasCurrentCityCard())
			{
				std::cout << "Who would like to share?\n 0:" << m_Players.at(index)->GetName() << " (Researcher) or...\n1:" <<  // promt for whos giving
					m_Players.at(pos)->GetName() << " (with current city card)" << std::endl;
				uint16_t selection = GetUserInput(0, 1);

				if(selection == 0)
					ExecuteShareKnowledgeAsResearcher((uint16_t)index); // 2.1
				else
					m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCard(cityID)); // 1.2

			}

			// basics -----------------------------------------------------------------------------
			if (m_Players.at(pos)->GetRoleID() == RoleList::RESEARCHER)
			{
				ExecuteShareKnowledgeAsResearcher(pos); // 1.1
			}
			if (m_Players.at(index)->GetRoleID() == RoleList::RESEARCHER )
			{
				ExecuteShareKnowledgeAsResearcher((uint16_t)index); // 2.1
			}
			else if (m_Players.at(index)->HasCurrentCityCard()) // 2.2
			{
				m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCard(cityID)); // 1.2
			}
			else if (m_Players.at(pos)->HasCurrentCityCard())
			{
				m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCard(cityID)); // 1.2
			}
		}
	}
	return 1;
}
// ExecuteShareKnowledge --------------------------------------------------------------------------

// ExecuteShareKnowledgeAsResearcher --------------------------------------------------------------
void GameEngine::ExecuteShareKnowledgeAsResearcher(const uint16_t & pos)
{
	m_Players.at(pos)->Notify(); // print researchers hand
	std::cout << "Which card would you like to share..." << std::endl; // promt for which to giving
	uint16_t selection = GetUserInput(0 , (uint16_t)m_Players.at(pos)->m_Hand.size()-1);

	for (size_t index = 0; index < m_Players.size(); index += 1) // find next player in that city
	{
		if (index == pos) continue; // skip yourself

		if (m_Players.at(pos)->GetCityID() == m_Players.at(index)->GetCityID()) // if same city
		{
			m_Players.at(index)->AddCard(m_Players.at(pos)->RemoveCardAt(selection)); // rm from researcher and give to other guy
			return;
		}
	}
}
// ExecuteShareKnowledgeAsResearcher --------------------------------------------------------------

// ExecuteCureDisease -----------------------------------------------------------------------------
uint16_t GameEngine::ExecuteCureDisease(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	Color cc = DetermineCureColor(pos); // determine which to cure
	if (cc != Color::INVALID) // make sure its not invalid
	{
		m_Board.m_Cures.CureDiscover(cc);
		size_t k = 0;
		for ( /* no init */; k < m_Players.at(pos)->m_Hand.size() && k < m_Players.at(pos)->GetNumOfCardToDiscoverCure(); k += 1)
		{
			if (PlayerCardFactory::IsaCityCard(m_Players.at(pos)->m_Hand.at(k)->GetNumID()))
				if (dynamic_cast<CityCard*>(m_Players.at(pos)->m_Hand.at(k))->GetCityColor() == cc)
					m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)k));
		}

#if _DEBUG
		if (k != m_Players.at(pos)->GetNumOfCardToDiscoverCure())
			throw GameErrorException("Did not delete correct number of cards!");
#endif // _DEBUG

	}
#if _DEBUG
	else // there is a false call to this action
	{
		throw GameErrorException("Some how exceeded max number of RCs"); // uncaught allows me to trace+debug
	}
#endif // _DEBUG
	CheckIfGameWon();

	return 1;
}
// ExecuteCureDisease -----------------------------------------------------------------------------

// ExecuteAirLift ---------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteAirLift(const uint16_t& pos, const CityList::CityID& cityID)
{
	cityID; // unused, keept for normalization

	for (size_t l = 0; l < m_Players.at(pos)->m_Hand.size(); l += 1) // lets remove the the air lift card
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(l)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(l)->GetNumID() == EventCard::AIRLIFT)
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)l)); // discard airlift
				break;
			}
	}

	std::cout << "Note: All players involved must agree!" << std::endl;
	std::cout << "Select the player to move..." << std::endl; // who do you want to move
	uint16_t i = 0;
	for each(Player* joeur in m_Players)
	{
		std::cout << i++ << ": " << joeur->GetName() << " in the city " << Card::GetCardName(joeur->GetCityID() + CityCard::CITYCARD_MIN) << std::endl; //print players and index 
	}
	uint16_t selection = GetUserInput(0,i-1); // pick player

	std::map<uint16_t, CityList::CityID> secondary; 
	uint16_t j = 0;
	std::cout << "Which city would you like to move " << m_Players.at(selection)->m_Name << " to..." << std::endl;
	for each(City* ville in m_Board.m_Map.GetAllCities()) // get all cities
	{
		if (ville->GetCityID() == m_Players.at(selection)->GetCityID()) // skip city player is in
			continue;

		std::cout << j << ": "; // index them
		ville->PrintInformation(); // print city's info
		secondary.insert(std::make_pair(j++, ville->GetCityID())); // map of every city id + pick number
	}
	uint16_t pick = GetUserInput(0,j-1); // get users selection

	std::stringstream ss;
	ss << std::hex << secondary.at(pick);
	m_Players.at(selection)->ChangeCity(ss.str()); // move them to desired city

	if (m_Players.at(selection)->GetRoleID() == RoleList::MEDIC) // if player moved was the medic
		if (m_Board.m_Cures.IsAnyCured()) // check if worth the next call
			ExecuteMedicEnteredCity(cityID); // remove all cubes of cured diseases

	return 0;
}
// ExecuteAirLift ---------------------------------------------------------------------------------

// ExecuteResillentPopulation ---------------------------------------------------------------------
uint16_t GameEngine::ExecuteResillentPopulation(const uint16_t & pos, const CityList::CityID & cityID)
{
	for (size_t m = 0; m < m_Players.at(pos)->m_Hand.size(); m += 1) // scan hand 
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(m)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(m)->GetNumID() == EventCard::RESILLIENT) // find resilent pop
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)m)); // rm and discard it card
				break;
			}
	}
	m_Board.m_InfecDeck.ResiliantPopulation((InfectionCard::CardsList)(cityID + InfectionCard::INFECTIONCARD_MIN)); // rm selected city card from discard pile
	return 0;
}
// ExecuteResillentPopulation ---------------------------------------------------------------------

// ExecuteForecast --------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteForecast(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	for (size_t n = 0; n < m_Players.at(pos)->m_Hand.size(); n += 1) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(n)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(n)->GetNumID() == EventCard::FORECAST) // find forecast
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)n)); // rm and discard it card
				break;
			}
	}

	std::cout << "Changing forecast..." << std::endl;
	uint16_t selectionA = 0;
	std::deque<InfectionCard*> forecast = m_Board.m_InfecDeck.GetForecast(); // get top six cards of infection deck
	do
	{
		std::cout << "NOTE: Enter 0 as a selection to quit." << std::endl; // notify of quit option
		std::cout << " - TOP - " << std::endl;
		auto itor = forecast.crbegin(); 															// printing forecast relative to way it will be placed back
		for (uint16_t a = (uint16_t)forecast.size(); itor != forecast.crend(); a -= 1, itor++)		// printing forecast relative to way it will be placed back
		{																							// printing forecast relative to way it will be placed back
			std::cout << a << ": " << (*itor)->GetCardInfo() << std::endl;							// printing forecast relative to way it will be placed back
		}																							// printing forecast relative to way it will be placed back
		std::cout << " - BOTTOM - " << std::endl;													// printing forecast relative to way it will be placed back

		std::cout << "Which card would you like to move? "; // get first option
		selectionA = GetUserInput(0, 6);

		if (selectionA == 0)
			break;

		std::cout << "Which card would you like to swap with? "; // get second
		uint16_t selectionB = GetUserInput(1, 6);

		InfectionCard* move = forecast.at(selectionA - 1);	  // and lets swap
		InfectionCard* swap = forecast.at(selectionB - 1);	  // and lets swap
		forecast.at(selectionA - 1) = swap;					  // and lets swap
		forecast.at(selectionB - 1) = move;					  // and lets swap
	} while (selectionA != 0);

	m_Board.m_InfecDeck.SetForecast(forecast); // place card back on the infect deck

	return 0;
}
// ExecuteForecast --------------------------------------------------------------------------------

// ExecuteQuietNight ------------------------------------------------------------------------------
uint16_t GameEngine::ExecuteQuietNight(const uint16_t & pos, const CityList::CityID & cityID)
{
	cityID; // unused, keept for normalization
	for (size_t o = 0; o < m_Players.at(pos)->m_Hand.size(); o += 1) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(o)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(o)->GetNumID() == EventCard::QUIETNIGHT) // find quiet night card
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)o)); // rm and discard it
				break;
			}
	}

	std::cout << "\n  Next Infection Phase Will Be Skiped\n";
	m_SkipNextInfectionPhase = true;

	return 0;
}
// ExecuteQuietNight ------------------------------------------------------------------------------

// ExecuteGovernmentGrant -------------------------------------------------------------------------
uint16_t GameEngine::ExecuteGovernmentGrant(const uint16_t & pos, const CityList::CityID & cityID)
{
	for (size_t o = 0; o < m_Players.at(pos)->m_Hand.size(); o += 1) // scan hand
	{
		if (PlayerCardFactory::IsaEventCard(m_Players.at(pos)->m_Hand.at(o)->GetNumID()))
			if (m_Players.at(pos)->m_Hand.at(o)->GetNumID() == EventCard::GOVTGRANT) // find govt grant card
			{
				m_Board.m_PlayerDeck.DiscardCard(m_Players.at(pos)->RemoveCardAt((uint16_t)o)); // rm and discard it
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
	// game over checks + explination ... will be caught to kill game
	if (m_Board.m_Cubes.IsAnyEmpty()) throw GameOverException("a cube pile is empty!");
	if (m_Board.m_OutBreak.GetMarker() == 8) throw GameOverException("maximum outbreaks has been reached");
	if (m_Board.m_PlayerDeck.IsDeckEmpty()) throw GameOverException("the player deck is empty!");
}
// CheckIfGameOver --------------------------------------------------------------------------------

// CheckIfGameWon ---------------------------------------------------------------------------------
void GameEngine::CheckIfGameWon()
{
	// game won check + explination ... will be caught to end game
	if (m_Board.m_Cures.IsAllCuresDiscovered()) throw GameWonException("all cures have been discovered!");
}
// CheckIfGameWon ---------------------------------------------------------------------------------

// SaveGame ---------------------------------------------------------------------------------------
void GameEngine::SaveGame()
{
	if (!m_PreGameComplete) // prvent save if game wasnt even started
	{
		std::cout << "Game Not Initialized" << std::endl;
		return;
	}

	// Create/Open File ---------------------------------------------------------------------------
	std::ofstream myfile(m_Filename,std::ofstream::trunc);
	myfile << m_Filename << "\n";

	// Infection Cards ----------------------------------------------------------------------------
	myfile << m_Board.m_InfecDeck.GetSaveOutput() << "\n";

	// Player Cards -------------------------------------------------------------------------------
	myfile << m_Board.m_PlayerDeck.GetSaveOutput() << "\n";

	// Role Cards ---------------------------------------------------------------------------------
	myfile << m_Board.m_RoleDeck.GetSaveOutput() << "\n";

	// Cities -------------------------------------------------------------------------------------
	myfile << m_Board.m_Map.GetSaveOutput() << "\n";

	// Players ------------------------------------------------------------------------------------
	for each (Player* play in m_Players)
	{
		myfile << play->GetSaveOutput();
		myfile << "/ ";
	}
	myfile << "\n";

	// Cures --------------------------------------------------------------------------------------
	myfile << m_Board.m_Cures.GetSaveOutput() << "\n";

	// Infection Rate -----------------------------------------------------------------------------
	myfile << m_Board.m_InfectRate.GetSaveOutput() << "\n";

	// Outbreak Marker ----------------------------------------------------------------------------
	myfile << m_Board.m_OutBreak.GetSaveOutput() << "\n";

	// Research Centers ---------------------------------------------------------------------------
	myfile << m_Board.m_Centers.GetSaveOutput() << "\n";

	// Infection Log ------------------------------------------------------------------------------
	myfile << m_Log.GetSaveOutput() << "\n";

	// Turn Counter -------------------------------------------------------------------------------
	myfile << std::to_string(m_TurnCounter) << "\n";

	myfile.close();
}
// SaveGame ---------------------------------------------------------------------------------------

// LoadGame ---------------------------------------------------------------------------------------
void GameEngine::LoadGame()
{
	if (m_PreGameComplete) // if a game was started
	{
		std::cout << "WARNING: Game has already started..." << std::endl;
		SaveGame();
		std::cout << "AutoSave Completed" << std::endl; // save it
	}

	// Scan Save Directory ------------------------------------------------------------------------
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
				if (bfs::is_regular_file(itor->path())) // if item is a regular file
				{
					std::cout << i << ": " << itor->path().filename() << std::endl; // print option
					files.emplace(std::make_pair(i++, *itor)); // add options
				}
			}
		}
		else
		{
			// this is a fatal error which may prevent the game from ever loading
			std::cout << "\n\n ERROR: the pandemic save folder exists, but is not a directory\n"; // explain error
			std::cout << "WARNING - Our 'auto solution' tool will delete anything called 'bin' in this execution folder and may cause a curruption!\n"; // promt warning
			std::cout << "Would you like to try our 'auto solution'? Yes=1 No=0" << std::endl; // prompt choice
			uint16_t selection = GetUserInput(0, 1);
			if (selection == 1) // if user tries my lil solution
			{
				bfs::remove(p); // delete what ever it is
				if (!bfs::exists(p))
					std::cout << "The save folder error has been removed for you. Relaunch the game and try loading again." << std::endl; // success
				else
					std::cout << "The save folder error is in an irregular state please remove it manually to allow game load. " << p << std::endl; // failure
			}
			return;
		}
	}
	else
	{
		std::cout << "You have never has a game save, you should maybe play before trying to load a game =p\n\n"; // simple error where game has never been saved
		return;
	}

	if (files.size() == 0) // fail if no load options
	{
		std::cout << "No Load options avaliable." << std::endl;
		return;
	}

	uint16_t selection = GetUserInput(0, i - 1); // get users saved game choice


	// Read Selected Save Game File ---------------------------------------------------------------
	bfs::ifstream load;
	load.open(files.at(selection).path()); // open correct file

	char* buffer = new char[512];
	load.getline(buffer, 512); // get saved output
	m_Filename = std::string(buffer); // set filename to loaded games to allow correct saving with the continued game
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
		infecdeckbuilder.ParseDeck(infecdeck).ParseDiscard(infecdiscard); // parse save output
		m_Board.m_InfecDeck.InputLoadedGame(infecdeckbuilder.GetDeck(), infecdeckbuilder.GetDiscard()); // input loaded values
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
		playerdeckbuilder.ParseDeck(playdeck).ParseDiscard(playdiscard); // parse save output
		m_Board.m_PlayerDeck.InputLoadedGame(playerdeckbuilder.GetDeck(), playerdeckbuilder.GetDiscard()); // input loaded values
	}

	// Role Cards ---------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string role(buffer);
		delete[] buffer;
		buffer = nullptr;

		m_Board.m_RoleDeck.InputLoadedGame(RoleDeck::Builder::GetInstance().ParseDeck(role).GetDeck()); // build and input loaded values
	}

	// Cities -------------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string cities(buffer);
		delete[] buffer;
		buffer = nullptr;

		///Theres no builder for this section since it requries multiple components

		for each(City* city in m_Board.m_Map.GetAllCities()) // for each city 
		{
			size_t sep = cities.find("/"); // if nothing is written for that city
			if (sep == 0)
			{
				cities = cities.substr(sep + 2); // move forward
				continue; // and got to next
			}

			std::string cubecolors = cities.substr(0, sep); // get all the saved values (Color::XYZ's value)
			cities = cities.substr(sep + 2); // move forward
			for each(char c in cubecolors) // parse char (kinda wasteful since there are spaces)
			{
				switch (c) // lets play our cubes approperiately
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
		for (uint16_t r = 0; r < 4; r += 1) // force limit to max players
		{
			size_t slash = players.find("/");
			if (slash == std::string::npos) break;
			std::string play = players.substr(0, slash); // grab first players saved output
			players = players.substr(slash + 2); // move forward

			Player::Builder playerbuilder;
			gamers.emplace_back(playerbuilder.ParsePlayer(play).GetPlayer()); // build and input loaded values
			
			m_PlayersObservers.emplace_back(new PlayerObserver(gamers.back())); // handle observer
			gamers.back()->RegistarObserver(m_PlayersObservers.back());

		}
		m_Players.InputLoadedGame(gamers); // input loaded values
	}

	// Cures --------------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string rate(buffer);
		delete[] buffer;
		buffer = nullptr;

		m_Board.m_Cures.InputLoadedGame(CureMarkers::Builder::GetInstance().ParseCures(rate).GetRedCure(), CureMarkers::Builder::GetInstance().GetBlueCure(), CureMarkers::Builder::GetInstance().GetYellowCure(), CureMarkers::Builder::GetInstance().GetBlackCure()); // build and input loaded values
	}

	// Infection Rate -----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string rate(buffer);
		delete[] buffer;
		buffer = nullptr;

		m_Board.m_InfectRate.InputLoadedGame(InfectionRate::Builder::GetInstance().ParseInfectionRate(rate).GetPosition()); // build and input loaded values
		
	}

	// Outbreak Marker ----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string marker(buffer);
		delete[] buffer;
		buffer = nullptr;

		m_Board.m_OutBreak.InputLoadedGame(OutbreakMarker::Builder::GetInstance().ParseOutbreakMarker(marker).GetPosition()); // build and input loaded values
	}

	//ResearchCenters -----------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string stations(buffer);
		delete[] buffer;
		buffer = nullptr;

		///Theres no builder for this section since it requries multiple components

		std::vector<ResearchCenter> centers;
		for (uint16_t r = 0; r < 6; r += 1)
		{
			size_t slash = stations.find("/");
			if (slash == std::string::npos) break;
			std::string city = stations.substr(0, slash); // grab stations saved output
			stations = stations.substr(slash + 2); // move forward
			std::stringstream ss(city);
			uint64_t num = 0;
			ss >> std::hex >> num; // parse to ID
			centers.emplace_back(m_Board.m_Map.GetCityWithID((CityList::CityID)num)); // city with corresponding ID
		}
		m_Board.m_Centers.InputLoadedGame(centers); // input loaded values
	}

	// Infection Log ------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string log(buffer);
		delete[] buffer;
		buffer = nullptr;

		m_Log.InputLoadedGame(InfectionLog::Builder::GetInstance().ParseLog(log).GetLog()); // build and input loaded values
	}

	// Turn Counter -------------------------------------------------------------------------------
	{
		buffer = new char[512];
		load.getline(buffer, 512); // get saved output
		std::string counter(buffer);
		delete[] buffer;
		buffer = nullptr;

		std::stringstream ss(counter);
		ss >> std::hex >> m_TurnCounter; // parse and input loaded values
	}

	CheckIfGameOver();
	m_PreGameComplete = true;
}
// LoadGame ---------------------------------------------------------------------------------------

// Initialize -------------------------------------------------------------------------------------
void GameEngine::Initialize()
{
	std::cout << "Would you like to load a game? YES=1 NO=0" << std::endl; // promt for load option
	uint16_t selection = GetUserInput(0, 1);
	if (selection == 1)
	{
		try
		{
			LoadGame(); // lets load
		}
		catch (GameOverException&)
		{
			//potential that the loaded game has already been lost
			std::cout << "That game was already lost! ";
			bfs::path remove(m_Filename); // auto rm of file
			if (bfs::exists(remove))
				bfs::remove(remove);
			if (!bfs::exists(remove))
				std::cout << "It has been removed for you." << std::endl;
			else
				std::cout << "The file is in an irregular state please remove it manually." << std::endl; // warn if there was an issue
		}
	}
	else
	{
		BoardSetup();			 //DO NOT TOUCH ORDER !
		PlayersSetup();			 //DO NOT TOUCH ORDER !
		DifficultySetup();		 //DO NOT TOUCH ORDER !
		m_PreGameComplete = true;
	}
}
// Initialize -------------------------------------------------------------------------------------

// Launch -----------------------------------------------------------------------------------------
void GameEngine::Launch()
{
	if (!m_PreGameComplete) // make sure the game has been setup before playing
	{
		std::cout << "Game Not Initialized" << std::endl;
		return;
	}

	try
	{       
		for ( /* no init */; /* no limit */; m_TurnCounter += 1)
		{
			std::cout << "\n\nGet ready " << m_Players.at(m_TurnCounter % (uint16_t)m_Players.size())->GetName() << " you're up next!\nPress 'enter' to continue..."; 
			std::cin.get(); // promt to alert next player

			//main mod to switch between players
			TurnSequence(m_TurnCounter % (uint16_t)m_Players.size());
		}
	}
	catch (const GameOverException& e)
	{
		//if game over
		std::cout << "\n\n ---- GAME OVER! ----\n  You lost due to: " << e.what() << std::endl; // print why
		m_Board.m_Map.MapSubject::Notify(); // print last map
		bfs::path remove(m_Filename); // auto rm file
		if (bfs::exists(remove))
			if (bfs::is_regular_file(remove))
				bfs::remove(remove);
		if (!bfs::exists(remove))
			std::cout << "The game file has been removed for you." << std::endl; // success
		else
			std::cout << "The game file is in an irregular state please remove it manually. " << m_Filename << std::endl; // failure
	}
	catch (const GameWonException& e)
	{
		std::cout << "\n\n ---- Congradulations! ----\n  You won due to: " << e.what() << std::endl; // you won =)
	}
	catch (const GameQuitException& e)
	{
		std::cout << "\n\n ---- Good Bye! ----\n  " << e.what() << std::endl; // you stoped playing ='(
	}
	
}
// Launch -----------------------------------------------------------------------------------------
