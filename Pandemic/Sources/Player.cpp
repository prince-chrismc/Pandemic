#include <sstream> //std::stringstream
#include "Player.h"
#include "Token.h"

Player::~Player()
{
	delete m_role;

	for (size_t pos = 0; pos < m_hand.size(); pos += 1)
	{
		if (m_hand.at(pos) != NULL)
		{
			delete m_hand.at(pos);
			m_hand.at(pos) = NULL;
		}
	}
	m_hand.resize(0);
	m_hand.clear();
}

PlayerCard* Player::rmCard(uint8_t pos)
{
	PlayerCard* pc = m_hand.at(pos); 
	m_hand.erase(m_hand.begin() + pos); 
	return pc;
}

CityList::CityID Player::getCityID()
{
	std::stringstream ss;
	ss << std::hex << m_role->getCityID();
	uint64_t num = 0;
	ss >> std::hex >> num;

	return (CityList::CityID)num;
}

std::vector<CityList::CityID> Player::getDirectFlightCities()
{
	std::vector<CityList::CityID> result;
	for (size_t pos = 0; pos < m_hand.size(); pos += 1)
	{
		if (CityCard::IsaCityCard(m_hand.at(pos)))
		{
			result.emplace_back((CityList::CityID)(m_hand.at(pos)->getNumID() - CityCard::CITYCARD_MIN));
		}
	}
	return result;
}

bool Player::hasCurrentCityCard()
{
	for (size_t pos = 0; pos < m_hand.size(); pos += 1)
	{
		if (m_hand.at(pos)->getNumID() == (uint64_t)(getCityID() + CityCard::CITYCARD_MIN))
			return true;
	}
	return false;
}

void Player::printName()
{
	printf("Player %s: \n", m_name.c_str());
}


void Player::printInfo()
{
	std::stringstream ss;
	ss << std::hex << m_role->getCityID();
	uint64_t num = 0;
	ss >> std::hex >> num;

	printf("Player %s - %s: is in %s\n", m_name.c_str(), m_role->getName(), Card::getCardName(num + CityCard::CITYCARD_MIN) );
}

void Player::printHand()
{
	printName();
	if (m_hand.size() == 0)
	{
		printf(" Hand is empty\n");
		return;
	}

	for (size_t s = 0; s < m_hand.size(); s += 1)
	{
		printf("Card %d: ", (int)s);
		m_hand.at(s)->PrintInformation();
	}
}

void Player::printRefCard()
{
	printf("Reference Card:\n--------------------------------------------------\n");
	m_refcard.PrintInformation();
	printf("--------------------------------------------------\n\n"); 
}

Role::Role(const uint64_t & id) : m_name(Card::getCardName(id)), m_pawn(new Pawn(id))
{
	std::stringstream ss;
	ss << std::hex << id;
	m_roleID = ss.str();
}

Role::Role(RoleCard* card) : Role(card->getNumID())
{
	m_card = card;
}

Role::~Role()
{
	delete m_pawn;
	delete m_card;
}

Pawn::Pawn(const uint64_t& color) : m_color( (PawnColor)color )
{
	std::stringstream ss;
	ss << std::hex << City::ATLANTA;
	m_CityID = ss.str();
}
