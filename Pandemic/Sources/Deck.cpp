#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include <ios> //std::hex
#include <sstream> //std::stringstream
#include "Deck.h"

// Infection Deck ---------------------------------------------------------------------------------
InfectionDeck::InfectionDeck() : Deck(48)
{
	m_Deck.emplace_back(InfectionCard::ALGIERS);
	m_Deck.emplace_back(InfectionCard::ATLANTA);
	m_Deck.emplace_back(InfectionCard::BAGHDAD);
	m_Deck.emplace_back(InfectionCard::BANGKOK);
	m_Deck.emplace_back(InfectionCard::BEIJING);
	m_Deck.emplace_back(InfectionCard::BOGOTA);
	m_Deck.emplace_back(InfectionCard::BUENOSAIRES);
	m_Deck.emplace_back(InfectionCard::CAIRO);
	m_Deck.emplace_back(InfectionCard::CHENNAI);
	m_Deck.emplace_back(InfectionCard::CHICAGO);
	m_Deck.emplace_back(InfectionCard::DELHI);
	m_Deck.emplace_back(InfectionCard::ESSEN);
	m_Deck.emplace_back(InfectionCard::HOCHIMINH);
	m_Deck.emplace_back(InfectionCard::HONGKONG);
	m_Deck.emplace_back(InfectionCard::ISTANBUL);
	m_Deck.emplace_back(InfectionCard::JAKARTA);
	m_Deck.emplace_back(InfectionCard::JOHANNESBURG);
	m_Deck.emplace_back(InfectionCard::KARACHI);
	m_Deck.emplace_back(InfectionCard::KHARTOUM);
	m_Deck.emplace_back(InfectionCard::KINSHASA);
	m_Deck.emplace_back(InfectionCard::KOLKATA);
	m_Deck.emplace_back(InfectionCard::LAGOS);
	m_Deck.emplace_back(InfectionCard::LIMA);
	m_Deck.emplace_back(InfectionCard::LONDON);
	m_Deck.emplace_back(InfectionCard::LOSANGELES);
	m_Deck.emplace_back(InfectionCard::MADRID);
	m_Deck.emplace_back(InfectionCard::MANILA);
	m_Deck.emplace_back(InfectionCard::MEXICO);
	m_Deck.emplace_back(InfectionCard::MIAMI);
	m_Deck.emplace_back(InfectionCard::MILAN);
	m_Deck.emplace_back(InfectionCard::MONTREAL);
	m_Deck.emplace_back(InfectionCard::MOSCOW);
	m_Deck.emplace_back(InfectionCard::MUMBAI);
	m_Deck.emplace_back(InfectionCard::NEWYORK);
	m_Deck.emplace_back(InfectionCard::OSAKA);
	m_Deck.emplace_back(InfectionCard::PARIS);
	m_Deck.emplace_back(InfectionCard::RIYADH);
	m_Deck.emplace_back(InfectionCard::SANFRAN);
	m_Deck.emplace_back(InfectionCard::SANTIAGO);
	m_Deck.emplace_back(InfectionCard::SAOPAULO);
	m_Deck.emplace_back(InfectionCard::SEOUL);
	m_Deck.emplace_back(InfectionCard::SHANGHAI);
	m_Deck.emplace_back(InfectionCard::STPETER);
	m_Deck.emplace_back(InfectionCard::SYDNEY);
	m_Deck.emplace_back(InfectionCard::TAIPEI);
	m_Deck.emplace_back(InfectionCard::TEHRAN);
	m_Deck.emplace_back(InfectionCard::TOKYO);
	m_Deck.emplace_back(InfectionCard::WASHINGTON);

	//make sure its the right size
	m_Deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Deck.begin(), m_Deck.end(), g);
}

InfectionCard* InfectionDeck::DrawCard()
{
	if (m_Deck.size() == 0) return nullptr; //for when deck is empty

	InfectionCard::CardsList nextID = m_Deck.front();
	m_Deck.pop_front();
	Notify(Priority::MINOR);
	m_Discard.emplace_front(nextID);
	return new InfectionCard(nextID);
}

InfectionCard* InfectionDeck::DrawCardForEpidemic()
{
	if (m_Deck.size() == 0) return nullptr; //for when deck is empty

	InfectionCard::CardsList nextID = m_Deck.back();
	m_Deck.pop_back();
	Notify(Priority::MINOR);
	m_Discard.emplace_front(nextID);
	return new InfectionCard(nextID);
}

void InfectionDeck::Intensify()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Discard.begin(), m_Discard.end(), g);

	for each(InfectionCard::CardsList id in m_Discard)
	{
		m_Deck.emplace_front(id);
	}

	m_Discard.clear();
}

void InfectionDeck::ResiliantPopulation(const InfectionCard::CardsList& id)
{
	uint16_t rm = 0;
	for each(InfectionCard::CardsList cardnum in m_Discard)
	{
		if (id == cardnum)
		{
			m_Discard.erase(m_Discard.begin() + rm);
			break;
		}

		rm += 1;
	}
}

std::deque<InfectionCard*> InfectionDeck::GetForecast()
{
	std::deque<InfectionCard*> topsix;
	for (uint16_t i = 0; i < 6; i += 1)
	{
		topsix.emplace_front(DrawCard());
	}
	return topsix;
}

void InfectionDeck::SetForecast(std::deque<InfectionCard*> top)
{
	for each(InfectionCard* ic in top)
	{
		m_Deck.emplace_front((InfectionCard::CardsList)ic->GetNumID());
		delete ic;
		ic = nullptr;
	}
}

std::string InfectionDeck::GetSaveOutput()
{
	std::string result;

	for each(InfectionCard::CardsList ic in m_Deck)
	{
		std::stringstream ss;
		ss << std::hex << ic;
		result += ss.str() + " ";
	}
	result += "/ ";
	for each(InfectionCard::CardsList ic in m_Discard)
	{
		std::stringstream ss;
		ss << std::hex << ic;
		result += ss.str() + " ";
	}

	return result;
}

void InfectionDeck::InputLoadedGame(std::deque<InfectionCard::CardsList> deck, std::deque<InfectionCard::CardsList> discard)
{
	m_Deck = deck;
	m_Discard = discard;
}

// Player Deck ------------------------------------------------------------------------------------
PlayerDeck::PlayerDeck() : Deck(53), m_Difficulty(Difficulty::INVALID)
{
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::ALGIERS);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::ATLANTA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::BAGHDAD);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::BANGKOK);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::BEIJING);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::BOGOTA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::BUENOSAIRES);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::CAIRO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::CHENNAI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::CHICAGO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::DELHI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::ESSEN);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::HOCHIMINH);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::HONGKONG);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::ISTANBUL);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::JAKARTA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::JOHANNESBURG);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::KARACHI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::KHARTOUM);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::KINSHASA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::KOLKATA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::LAGOS);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::LIMA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::LONDON);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::LOSANGELES);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MADRID);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MANILA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MEXICO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MIAMI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MILAN);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MONTREAL);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MOSCOW);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::MUMBAI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::NEWYORK);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::OSAKA);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::PARIS);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::RIYADH);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SANFRAN);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SANTIAGO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SAOPAULO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SEOUL);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SHANGHAI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::STPETER);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::SYDNEY);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::TAIPEI);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::TEHRAN);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::TOKYO);
	m_Deck.emplace_back((PlayerCard::CardsList)CityCard::WASHINGTON);

	m_Deck.emplace_back((PlayerCard::CardsList)EventCard::RESILLIENT);
	m_Deck.emplace_back((PlayerCard::CardsList)EventCard::AIRLIFT);
	m_Deck.emplace_back((PlayerCard::CardsList)EventCard::FORECAST);
	m_Deck.emplace_back((PlayerCard::CardsList)EventCard::QUIETNIGHT);
	m_Deck.emplace_back((PlayerCard::CardsList)EventCard::GOVTGRANT);

	//make sure its the right size
	m_Deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Deck.begin(), m_Deck.end(), g);
}

PlayerCard* PlayerDeck::DrawCard()
{
	if (m_Deck.size() == 0) return nullptr; //for when deck is empty

	PlayerCard::CardsList nextID = m_Deck.front();
	m_Deck.pop_front();
	Notify(Priority::MINOR);
	return PlayerCardFactory::MakeCard(nextID);
}

void PlayerDeck::DiscardCard(PlayerCard* pc)
{
	uint64_t id = pc->GetNumID();
	m_Discard.emplace_front((PlayerCard::CardsList)id);
	delete pc;
}

void PlayerDeck::IncreaseDifficulty(const uint16_t& dif)
{
	if ((Difficulty)dif <= m_Difficulty) return; //restrict to increasing only

	m_Difficulty = (Difficulty)dif;
	switch ((Difficulty)dif)
	{
	case Difficulty::HARD:
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDSIX);
	case Difficulty::MEDIUM:
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDFIVE);
	case Difficulty::EASY:
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDFOUR);
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDTHREE);
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDTWO);
		m_Deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDONE);
	default:
		break;
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Deck.begin(), m_Deck.end(), g);
}

std::string PlayerDeck::GetSaveOutput()
{
	std::string result;

	for each(PlayerCard::CardsList pc in m_Deck)
	{
		std::stringstream ss;
		ss << std::hex << pc;
		result += ss.str() + " ";
	}
	result += "/ ";
	for each(PlayerCard::CardsList pc in m_Discard)
	{
		std::stringstream ss;
		ss << std::hex << pc;
		result += ss.str() + " ";
	}

	return result;
}

void PlayerDeck::InputLoadedGame(std::deque<PlayerCard::CardsList> deck, std::deque<PlayerCard::CardsList> discard)
{
	m_Deck = deck;
	m_Discard = discard;
	switch (m_Deck.size() + m_Discard.size())
	{
	case 57:
		m_Difficulty = Difficulty::EASY;
	case 58:
		m_Difficulty = Difficulty::MEDIUM;
	case 59:
		m_Difficulty = Difficulty::HARD;
	default:
		m_Difficulty = Difficulty::INVALID;
	}
}

// Role Deck --------------------------------------------------------------------------------------
RoleDeck::RoleDeck() : Deck(7)
{
	m_Deck.emplace_back(RoleCard::CONTIGENCY);
	m_Deck.emplace_back(RoleCard::DISPATCHER);
	m_Deck.emplace_back(RoleCard::MEDIC);
	m_Deck.emplace_back(RoleCard::OPERATIONS);
	m_Deck.emplace_back(RoleCard::QUARANTINE);
	m_Deck.emplace_back(RoleCard::RESEARCHER);
	m_Deck.emplace_back(RoleCard::SCIENTIST);

	//make sure its the right size
	m_Deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Deck.begin(), m_Deck.end(), g);
}

RoleCard* RoleDeck::DrawCard()
{
	if (m_Deck.size() == 0) return nullptr; //for when deck is empty

	RoleCard::Roles nextID = m_Deck.front();
	m_Deck.pop_front();
	return new RoleCard(nextID); //gets deleted by the player
}

std::string RoleDeck::GetSaveOutput()
{
	std::string result;

	for each(RoleCard::Roles rc in m_Deck)
	{
		std::stringstream ss;
		ss << std::hex << rc;
		result += ss.str() + " ";
	}

	return result;
}

void RoleDeck::InputLoadedGame(std::deque<RoleCard::Roles> deck)
{
	m_Deck = deck;
}

// Builder ----------------------------------------------------------------------------------------
InfectionDeck::Builder& InfectionDeck::Builder::ParseDeck(std::string loaded)
{
	for (uint16_t a = 0; a < 48; a += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos) 
			break;

		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);

		uint64_t num = 0;
		ss >> std::hex >> num;
		AddToDeck((InfectionCard::CardsList)num);
	}

	return *this;
}

InfectionDeck::Builder& InfectionDeck::Builder::ParseDiscard(std::string loaded)
{
	for (uint16_t b = 0; b < 48; b += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos)
			break;

		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);

		uint64_t num = 0;
		ss >> std::hex >> num;
		AddToDiscard((InfectionCard::CardsList)num);
	}

	return *this;
}

PlayerDeck::Builder& PlayerDeck::Builder::ParseDiscard(std::string loaded)
{
	for (uint16_t b = 0; b < 48; b += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos) 
				break;

		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);

		uint64_t num = 0;
		ss >> std::hex >> num;
		AddToDiscard((PlayerCard::CardsList)num);
	}

	return *this;
}

PlayerDeck::Builder& PlayerDeck::Builder::ParseDeck(std::string loaded)
{
	for (uint16_t a = 0; a < 48; a += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos)
			break;

		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);

		uint64_t num = 0;
		ss >> std::hex >> num;
		AddToDeck((PlayerCard::CardsList)num);
	}

	return *this;
}

RoleDeck::Builder& RoleDeck::Builder::ParseDeck(std::string loaded)
{
	for (uint16_t a = 0; a < 48; a += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos)
			break;

		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);

		uint64_t num = 0;
		ss >> std::hex >> num;
		AddToDeck((RoleCard::Roles)num);
	}

	return *this;
}
