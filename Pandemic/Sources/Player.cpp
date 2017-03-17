#include <sstream> //std::stringstream
#include "Player.h"

Pawn::Pawn(const uint64_t& color) : m_Color((PawnColor)color)
{
	std::stringstream ss;
	ss << std::hex << CityList::ATLANTA;
	m_CityID = ss.str();
}

Role::Role(const uint64_t & id) : m_Name(Card::GetCardName(id)), m_Pawn(id)
{
	std::stringstream ss;
	ss << std::hex << id;
	m_roleID = ss.str();
}

Role::Role(RoleCard* card) : Role(card->GetNumID())
{
	m_Card = card;
}

Role::~Role()
{
	delete m_Card;
}

Player::~Player()
{
	for (size_t pos = 0; pos < m_Hand.size(); pos += 1)
	{
		if (m_Hand.at(pos) != nullptr)
		{
			delete m_Hand.at(pos);
			m_Hand.at(pos) = nullptr;
		}
	}
	m_Hand.resize(0);
	m_Hand.clear();
}

PlayerCard* Player::RemoveCardAt(const uint16_t& pos)
{
	PlayerCard* pc = m_Hand.at(pos);
	m_Hand.erase(m_Hand.begin() + pos);
	return pc;
}

PlayerCard* Player::RemoveCard(const CityList::CityID& id)
{
	uint16_t counter = 0;
	for each(PlayerCard* pc in m_Hand)
	{
		if (PlayerCardFactory::IsaCityCard(pc->GetNumID()))
		{
			if ((pc->GetNumID() - CityCard::CITYCARD_MIN) == id)
			{
				return RemoveCardAt(counter);
			}
		}
		++counter;
	}
}

CityList::CityID Player::GetCityID()
{
	std::stringstream ss;
	ss << std::hex << m_Role.m_Pawn.m_CityID;
	uint64_t num = 0;
	ss >> std::hex >> num;

	return (CityList::CityID)num;
}

bool Player::HasCurrentCityCard()
{
	for (size_t pos = 0; pos < m_Hand.size(); pos += 1)
	{
		if (m_Hand.at(pos)->GetNumID() == (uint64_t)(GetCityID() + CityCard::CITYCARD_MIN))
			return true;
	}
	return false;
}

uint16_t Player::GetNumOfCardToDiscoverCure()
{
	switch (m_Role.m_Card->GetNumID())
	{
	case RoleList::SCIENTIST:
		return 4;
	default:
		return 5;
	}
}

void Player::PrintInfo()
{
	std::stringstream ss;
	ss << std::hex << m_Role.m_Pawn.m_CityID;
	uint64_t num = 0;
	ss >> std::hex >> num;

	printf("Player %s - %s: is in %s\n", m_Name.c_str(), m_Role.m_Name.c_str(), Card::GetCardName(num + CityCard::CITYCARD_MIN));
}

void Player::PrintHand()
{
	printf("\n");
	printf("Player %s: \n", m_Name.c_str());
	if (m_Hand.size() == 0)
	{
		printf(" Hand is empty\n");
		return;
	}

	for (size_t s = 0; s < m_Hand.size(); s += 1)
	{
		printf("Card %d: ", (int)s);
		m_Hand.at(s)->PrintInformation();
	}
}

void Player::PrintRefCard()
{
	printf("Reference Card:\n--------------------------------------------------\n");
	m_RefCard.PrintInformation();
	printf("--------------------------------------------------\n\n");
}

std::string Player::GetSaveOutput()
{
	std::string result = m_Name + " " + m_Role.m_roleID + " ";

	for each (PlayerCard* pc in m_Hand)
	{
		std::stringstream ss;
		ss << std::hex << pc->GetNumID();
		result += ss.str() + " ";
	}

	return result;
}
