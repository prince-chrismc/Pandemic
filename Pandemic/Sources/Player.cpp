#include "Player.h"
#include <sstream> //std::stringstream

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
	m_hand.clear();
}

PlayerCard* Player::rmCard(uint8_t pos)
{
	PlayerCard* pc = m_hand.at(pos); 
	m_hand.erase(m_hand.begin() + pos); 
	return pc;
}

void Player::printName()
{
	printf("Player %s: \n", m_name.c_str());
}


void Player::printInfo()
{
	printf("Player %s - %s: \n", m_name.c_str(), m_role->getName());
}

void Player::printHand()
{
	printName();
	for (size_t s = 0; s < m_hand.size(); s += 1)
	{
		printf("Card %d: ", s);
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
	ss << std::hex << CityCard::ATLANTA;
	m_CityID = ss.str();
}
