#include <algorithm>
#include <random>
#include "Deck.h"

InfectionDeck::InfectionDeck() : Deck(48)
{
	m_deck.emplace_back(new InfectionCard(InfectionCard::ALGIERS));
	m_deck.emplace_back(new InfectionCard(InfectionCard::ATLANTA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::BAGHDAD));
	m_deck.emplace_back(new InfectionCard(InfectionCard::BANGKOK));
	m_deck.emplace_back(new InfectionCard(InfectionCard::BEIJING));
	m_deck.emplace_back(new InfectionCard(InfectionCard::BOGOTA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::BUENOSAIRES));
	m_deck.emplace_back(new InfectionCard(InfectionCard::CAIRO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::CHENNAI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::CHICAGO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::DELHI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::ESSEN));
	m_deck.emplace_back(new InfectionCard(InfectionCard::HOCHIMINH));
	m_deck.emplace_back(new InfectionCard(InfectionCard::HONGKONG));
	m_deck.emplace_back(new InfectionCard(InfectionCard::ISTANBUL));
	m_deck.emplace_back(new InfectionCard(InfectionCard::JAKARTA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::JOHANNESBURG));
	m_deck.emplace_back(new InfectionCard(InfectionCard::KARACHI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::KHARTOUM));
	m_deck.emplace_back(new InfectionCard(InfectionCard::KINSHASA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::KOLKATA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::LAGOS));
	m_deck.emplace_back(new InfectionCard(InfectionCard::LIMA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::LONDON));
	m_deck.emplace_back(new InfectionCard(InfectionCard::LOSANGELES));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MADRID));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MANILA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MEXICO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MIAMI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MILAN));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MONTREAL));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MOSCOW));
	m_deck.emplace_back(new InfectionCard(InfectionCard::MUMBAI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::NEWYORK));
	m_deck.emplace_back(new InfectionCard(InfectionCard::OSAKA));
	m_deck.emplace_back(new InfectionCard(InfectionCard::PARIS));
	m_deck.emplace_back(new InfectionCard(InfectionCard::RIYADH));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SANFRAN));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SANTIAGO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SAOPAULO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SEOUL));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SHANGHAI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::STPETER));
	m_deck.emplace_back(new InfectionCard(InfectionCard::SYDNEY));
	m_deck.emplace_back(new InfectionCard(InfectionCard::TAIPEI));
	m_deck.emplace_back(new InfectionCard(InfectionCard::TEHRAN));
	m_deck.emplace_back(new InfectionCard(InfectionCard::TOKYO));
	m_deck.emplace_back(new InfectionCard(InfectionCard::WASHINGTON));

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

InfectionDeck::~InfectionDeck()
{
	for (size_t pos = 0; pos < m_deck.size(); pos += 1)
	{
		if (m_deck.at(pos) != NULL)
		{
			delete m_deck.at(pos);
			m_deck.at(pos) = NULL;
		}
	}
	m_deck.clear();

	for (size_t pos = 0; pos < m_discard.size(); pos += 1)
	{
		if (m_discard.at(pos) != NULL)
		{
			delete m_discard.at(pos);
			m_discard.at(pos) = NULL;
		}
	}
	m_discard.clear();
}

InfectionCard* InfectionDeck::DrawCard()
{
	InfectionCard* draw = m_deck.front();
	m_deck.pop_front();
	m_discard.emplace_front(draw);
	return draw;
}

PlayerDeck::PlayerDeck() : Deck(57)
{
	m_deck.emplace_back(new CityCard(CityCard::ALGIERS	   ));
	m_deck.emplace_back(new CityCard(CityCard::ATLANTA	   ));
	m_deck.emplace_back(new CityCard(CityCard::BAGHDAD	   ));
	m_deck.emplace_back(new CityCard(CityCard::BANGKOK	   ));
	m_deck.emplace_back(new CityCard(CityCard::BEIJING	   ));
	m_deck.emplace_back(new CityCard(CityCard::BOGOTA	   ));
	m_deck.emplace_back(new CityCard(CityCard::BUENOSAIRES ));
	m_deck.emplace_back(new CityCard(CityCard::CAIRO	   ));
	m_deck.emplace_back(new CityCard(CityCard::CHENNAI	   ));
	m_deck.emplace_back(new CityCard(CityCard::CHICAGO	   ));
	m_deck.emplace_back(new CityCard(CityCard::DELHI	   ));
	m_deck.emplace_back(new CityCard(CityCard::ESSEN	   ));
	m_deck.emplace_back(new CityCard(CityCard::HOCHIMINH   ));
	m_deck.emplace_back(new CityCard(CityCard::HONGKONG	   ));
	m_deck.emplace_back(new CityCard(CityCard::ISTANBUL	   ));
	m_deck.emplace_back(new CityCard(CityCard::JAKARTA	   ));
	m_deck.emplace_back(new CityCard(CityCard::JOHANNESBURG));
	m_deck.emplace_back(new CityCard(CityCard::KARACHI	   ));
	m_deck.emplace_back(new CityCard(CityCard::KHARTOUM	   ));
	m_deck.emplace_back(new CityCard(CityCard::KINSHASA	   ));
	m_deck.emplace_back(new CityCard(CityCard::KOLKATA	   ));
	m_deck.emplace_back(new CityCard(CityCard::LAGOS	   ));
	m_deck.emplace_back(new CityCard(CityCard::LIMA		   ));
	m_deck.emplace_back(new CityCard(CityCard::LONDON	   ));
	m_deck.emplace_back(new CityCard(CityCard::LOSANGELES  ));
	m_deck.emplace_back(new CityCard(CityCard::MADRID	   ));
	m_deck.emplace_back(new CityCard(CityCard::MANILA	   ));
	m_deck.emplace_back(new CityCard(CityCard::MEXICO	   ));
	m_deck.emplace_back(new CityCard(CityCard::MIAMI	   ));
	m_deck.emplace_back(new CityCard(CityCard::MILAN	   ));
	m_deck.emplace_back(new CityCard(CityCard::MONTREAL	   ));
	m_deck.emplace_back(new CityCard(CityCard::MOSCOW	   ));
	m_deck.emplace_back(new CityCard(CityCard::MUMBAI	   ));
	m_deck.emplace_back(new CityCard(CityCard::NEWYORK	   ));
	m_deck.emplace_back(new CityCard(CityCard::OSAKA	   ));
	m_deck.emplace_back(new CityCard(CityCard::PARIS	   ));
	m_deck.emplace_back(new CityCard(CityCard::RIYADH	   ));
	m_deck.emplace_back(new CityCard(CityCard::SANFRAN	   ));
	m_deck.emplace_back(new CityCard(CityCard::SANTIAGO	   ));
	m_deck.emplace_back(new CityCard(CityCard::SAOPAULO	   ));
	m_deck.emplace_back(new CityCard(CityCard::SEOUL	   ));
	m_deck.emplace_back(new CityCard(CityCard::SHANGHAI	   ));
	m_deck.emplace_back(new CityCard(CityCard::STPETER	   ));
	m_deck.emplace_back(new CityCard(CityCard::SYDNEY	   ));
	m_deck.emplace_back(new CityCard(CityCard::TAIPEI	   ));
	m_deck.emplace_back(new CityCard(CityCard::TEHRAN	   ));
	m_deck.emplace_back(new CityCard(CityCard::TOKYO	   ));
	m_deck.emplace_back(new CityCard(CityCard::WASHINGTON  ));

	m_deck.emplace_back(new EpidemicCard(EpidemicCard::EPIDEMICCARDONE));
	m_deck.emplace_back(new EpidemicCard(EpidemicCard::EPIDEMICCARDTWO));
	m_deck.emplace_back(new EpidemicCard(EpidemicCard::EPIDEMICCARDTHREE));
	m_deck.emplace_back(new EpidemicCard(EpidemicCard::EPIDEMICCARDFOUR));

	m_deck.emplace_back(new EventCard(EventCard::RESILLIENT));
	m_deck.emplace_back(new EventCard(EventCard::AIRLIFT));
	m_deck.emplace_back(new EventCard(EventCard::FORECAST));
	m_deck.emplace_back(new EventCard(EventCard::QUIETNIGHT));
	m_deck.emplace_back(new EventCard(EventCard::GOVTGRANT));

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

PlayerDeck::~PlayerDeck()
{
	for (size_t pos = 0; pos < m_deck.size(); pos += 1)
	{
		if (m_deck.at(pos) != NULL)
		{
			delete m_deck.at(pos);
			m_deck.at(pos) = NULL;
		}
	}
	m_deck.clear();

	for (size_t pos = 0; pos < m_discard.size(); pos += 1)
	{
		if (m_discard.at(pos) != NULL)
		{
			delete m_discard.at(pos);
			m_discard.at(pos) = NULL;
		}
	}
	m_discard.clear();
}

PlayerCard* PlayerDeck::DrawCard()
{
	PlayerCard* draw = m_deck.front();
	m_deck.pop_front();
	return draw;
}

void PlayerDeck::DiscardCard(PlayerCard* pc)
{
	m_discard.emplace_front(pc);
}

RoleDeck::RoleDeck() : Deck(7)
{
	m_deck.emplace_back(new RoleCard(RoleCard::CONTIGENCY));
	m_deck.emplace_back(new RoleCard(RoleCard::DISPATCHER)); 
	m_deck.emplace_back(new RoleCard(RoleCard::MEDIC));
	m_deck.emplace_back(new RoleCard(RoleCard::OPERATIONS));
	m_deck.emplace_back(new RoleCard(RoleCard::QUARANTINE));
	m_deck.emplace_back(new RoleCard(RoleCard::RESEARCHER));
	m_deck.emplace_back(new RoleCard(RoleCard::SCIENTIST));

	//make sure its the right size
	m_deck.shrink_to_fit();

	//random shuffle =)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_deck.begin(), m_deck.end(), g);
}

RoleDeck::~RoleDeck()
{
	for (size_t pos = 0; pos < m_deck.size(); pos += 1)
	{
		if (m_deck.at(pos) != NULL)
		{
			delete m_deck.at(pos);
			m_deck.at(pos) = NULL;
		}
	}
	m_deck.clear();
}

RoleCard* RoleDeck::DrawCard()
{
	RoleCard* draw = m_deck.front();
	m_deck.pop_front();
	return draw;
}
