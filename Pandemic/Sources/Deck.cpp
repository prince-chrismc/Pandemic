#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include "Deck.h"

InfectionDeck::InfectionDeck() : Deck(48)
{
	m_deck.emplace_back(InfectionCard::ALGIERS);
	m_deck.emplace_back(InfectionCard::ATLANTA);
	m_deck.emplace_back(InfectionCard::BAGHDAD);
	m_deck.emplace_back(InfectionCard::BANGKOK);
	m_deck.emplace_back(InfectionCard::BEIJING);
	m_deck.emplace_back(InfectionCard::BOGOTA);
	m_deck.emplace_back(InfectionCard::BUENOSAIRES);
	m_deck.emplace_back(InfectionCard::CAIRO);
	m_deck.emplace_back(InfectionCard::CHENNAI);
	m_deck.emplace_back(InfectionCard::CHICAGO);
	m_deck.emplace_back(InfectionCard::DELHI);
	m_deck.emplace_back(InfectionCard::ESSEN);
	m_deck.emplace_back(InfectionCard::HOCHIMINH);
	m_deck.emplace_back(InfectionCard::HONGKONG);
	m_deck.emplace_back(InfectionCard::ISTANBUL);
	m_deck.emplace_back(InfectionCard::JAKARTA);
	m_deck.emplace_back(InfectionCard::JOHANNESBURG);
	m_deck.emplace_back(InfectionCard::KARACHI);
	m_deck.emplace_back(InfectionCard::KHARTOUM);
	m_deck.emplace_back(InfectionCard::KINSHASA);
	m_deck.emplace_back(InfectionCard::KOLKATA);
	m_deck.emplace_back(InfectionCard::LAGOS);
	m_deck.emplace_back(InfectionCard::LIMA);
	m_deck.emplace_back(InfectionCard::LONDON);
	m_deck.emplace_back(InfectionCard::LOSANGELES);
	m_deck.emplace_back(InfectionCard::MADRID);
	m_deck.emplace_back(InfectionCard::MANILA);
	m_deck.emplace_back(InfectionCard::MEXICO);
	m_deck.emplace_back(InfectionCard::MIAMI);
	m_deck.emplace_back(InfectionCard::MILAN);
	m_deck.emplace_back(InfectionCard::MONTREAL);
	m_deck.emplace_back(InfectionCard::MOSCOW);
	m_deck.emplace_back(InfectionCard::MUMBAI);
	m_deck.emplace_back(InfectionCard::NEWYORK);
	m_deck.emplace_back(InfectionCard::OSAKA);
	m_deck.emplace_back(InfectionCard::PARIS);
	m_deck.emplace_back(InfectionCard::RIYADH);
	m_deck.emplace_back(InfectionCard::SANFRAN);
	m_deck.emplace_back(InfectionCard::SANTIAGO);
	m_deck.emplace_back(InfectionCard::SAOPAULO);
	m_deck.emplace_back(InfectionCard::SEOUL);
	m_deck.emplace_back(InfectionCard::SHANGHAI);
	m_deck.emplace_back(InfectionCard::STPETER);
	m_deck.emplace_back(InfectionCard::SYDNEY);
	m_deck.emplace_back(InfectionCard::TAIPEI);
	m_deck.emplace_back(InfectionCard::TEHRAN);
	m_deck.emplace_back(InfectionCard::TOKYO);
	m_deck.emplace_back(InfectionCard::WASHINGTON);

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

InfectionCard* InfectionDeck::DrawCard()
{
	InfectionCard::CardsList nextID = m_deck.front();
	m_deck.pop_front();
	m_discard.emplace_front(nextID);
	return new InfectionCard(nextID);
}

// Player Deck ------------------------------------------------------------------------------------
PlayerDeck::PlayerDeck() : Deck(57)
{
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::ALGIERS);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::ATLANTA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::BAGHDAD);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::BANGKOK);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::BEIJING);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::BOGOTA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::BUENOSAIRES);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::CAIRO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::CHENNAI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::CHICAGO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::DELHI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::ESSEN);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::HOCHIMINH);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::HONGKONG);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::ISTANBUL);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::JAKARTA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::JOHANNESBURG);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::KARACHI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::KHARTOUM);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::KINSHASA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::KOLKATA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::LAGOS);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::LIMA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::LONDON);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::LOSANGELES);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MADRID);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MANILA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MEXICO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MIAMI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MILAN);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MONTREAL);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MOSCOW);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::MUMBAI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::NEWYORK);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::OSAKA);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::PARIS);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::RIYADH);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SANFRAN);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SANTIAGO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SAOPAULO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SEOUL);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SHANGHAI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::STPETER);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::SYDNEY);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::TAIPEI);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::TEHRAN);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::TOKYO);
	m_deck.emplace_back((PlayerCard::CardsList)CityCard::WASHINGTON);

	m_deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDONE);
	m_deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDTWO);
	m_deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDTHREE);
	m_deck.emplace_back((PlayerCard::CardsList)EpidemicCard::EPIDEMICCARDFOUR);
	
	m_deck.emplace_back((PlayerCard::CardsList)EventCard::RESILLIENT);
	m_deck.emplace_back((PlayerCard::CardsList)EventCard::AIRLIFT);
	m_deck.emplace_back((PlayerCard::CardsList)EventCard::FORECAST);
	m_deck.emplace_back((PlayerCard::CardsList)EventCard::QUIETNIGHT);
	m_deck.emplace_back((PlayerCard::CardsList)EventCard::GOVTGRANT);

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

PlayerCard* PlayerDeck::DrawCard()
{
	PlayerCard::CardsList nextID = m_deck.front();
	m_deck.pop_front();
	return PlayerCardFactory::makeCard(nextID);
}

void PlayerDeck::DiscardCard(PlayerCard* pc)
{
	uint64_t id = pc->getNumID();
	m_discard.emplace_front( (PlayerCard::CardsList)id);
	delete pc;
}

// Role Deck --------------------------------------------------------------------------------------
RoleDeck::RoleDeck() : Deck(7)
{
	m_deck.emplace_back(RoleCard::CONTIGENCY);
	m_deck.emplace_back(RoleCard::DISPATCHER); 
	m_deck.emplace_back(RoleCard::MEDIC);
	m_deck.emplace_back(RoleCard::OPERATIONS);
	m_deck.emplace_back(RoleCard::QUARANTINE);
	m_deck.emplace_back(RoleCard::RESEARCHER);
	m_deck.emplace_back(RoleCard::SCIENTIST);

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

RoleCard* RoleDeck::DrawCard()
{
	RoleCard::Roles nextID = m_deck.front();
	m_deck.pop_front();
	return new RoleCard(nextID); //gets deleted by the player
}
