#include "Player.h"

Player::~Player()
{
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

Role::Role(const uint64_t & id)
{
	m_name = Card::getCardName(id);
}
