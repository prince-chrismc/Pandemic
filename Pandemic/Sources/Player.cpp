#include <sstream> //std::stringstream
#include "Player.h"

Pawn::Pawn(const uint64_t& color) : m_Color((PawnColor)color)
{
	std::stringstream ss;
	ss << std::hex << CityList::ATLANTA;
	m_CityID = ss.str();
}

std::string Pawn::GetColor()
{
	switch (m_Color)
	{
	case CYAN:
		return "Cyan";
	case 	PINK:
		return "Pink";
	case 	ORANGE:
		return "Orange";
	case 	YELLOWGREEN:
		return "Yellow-green";
	case 	FORESTGREEN:
		return "Forest Green";
	case 	BROWN:
		return "Brown";
	case 	WHITE:
		return "White";
	default:
		break;
	}
	return "Invalid";
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

	delete m_PlannersEventCard;
	m_PlannersEventCard = nullptr;
}

PlayerCard* Player::RemoveCardAt(const uint16_t& pos)
{
	PlayerCard* pc = m_Hand.at(pos);
	m_Hand.erase(m_Hand.begin() + pos);
	Notify();
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
	return nullptr;
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

PlayerSubject::PlayerCharacteristics Player::GetCharacteristics()
{
	std::stringstream ss;
	ss << std::hex << m_Role.m_Pawn.m_CityID;
	uint64_t num = 0;
	ss >> std::hex >> num;

	std::vector<std::string> cardnames;
	for each(PlayerCard* pc in m_Hand)
	{
		cardnames.emplace_back(pc->GetCardInfo());
	}

	return PlayerSubject::PlayerCharacteristics(m_Name, m_Role.m_Pawn.GetColor(), m_Role.m_Name, std::string(Card::GetCardName(num + CityCard::CITYCARD_MIN)), cardnames);
}

void Player::PrintRefCard()
{
	printf("Reference Card:\n--------------------------------------------------\n%s\n--------------------------------------------------\n\n", m_RefCard.GetCardInfo().c_str());
}

std::string Player::GetSaveOutput()
{
	std::string result = m_Name + " " + m_Role.m_roleID;
	
	if (HasExtraCard())
	{
		std::stringstream ss(".");
		ss << std::hex << m_PlannersEventCard->GetNumID();
		result += ss.str();
	}
	
	result += " " + m_Role.m_Pawn.m_CityID + " ";

	for each (PlayerCard* pc in m_Hand)
	{
		std::stringstream ss;
		ss << std::hex << pc->GetNumID();
		result += ss.str() + " ";
	}

	return result;
}

Player::Builder& Player::Builder::ParseHand(std::string loaded)
{
	for (uint16_t s = 0; s < 7; s += 1)
	{
		size_t space = loaded.find(" ");
		if (space == std::string::npos) break;
		std::stringstream ss(loaded.substr(0, space));
		loaded = loaded.substr(space + 1);
		uint64_t cardnum;
		ss >> std::hex >> cardnum;
		m_Hand.emplace_back(PlayerCardFactory::MakeCard(cardnum));
	}

	return *this;
}

Player::Builder& Player::Builder::ParsePlayer(std::string loaded)
{
	size_t space = loaded.find(" ");
	if (space == std::string::npos) return *this;
	m_Name = loaded.substr(0, space); // get players name
	loaded = loaded.substr(space + 1);

	space = loaded.find(" ");
	std::hexadecimal id = loaded.substr(0, space); // get players role id
	if (id.find(".") != std::string::npos) // role id contains an extra card
	{
		size_t dot = id.find(".");
		std::hexadecimal extra = id.substr(0, dot);
		id = id.substr(dot + 1);
		uint64_t cardnum;
		std::stringstream(extra) >> std::hex >> cardnum;
		m_PlannersEventCard = PlayerCardFactory::MakeCard(cardnum);
	}

	loaded = loaded.substr(space + 1);
	std::stringstream ss(id);
	uint64_t roleid;
	ss >> std::hex >> roleid;
	m_RoleID = (RoleList::Roles)roleid;
	
	space = loaded.find(" ");
	m_CityID = loaded.substr(0, space); // get players city
	loaded = loaded.substr(space + 1);
	
	return ParseHand(loaded);
}

Player* Player::Builder::GetPlayer()
{
	Player* joeur = new Player(m_Name, new RoleCard(m_RoleID));
	joeur->ChangeCity(m_CityID);
	for each(PlayerCard* pc in m_Hand)
	{
		joeur->AddCard(pc);
	}

	return joeur;
}

float PlayersContainer::GetAverageNumberOfCards()
{
	float counter = 0;
	for each(Player* joeur in *this)
	{
		counter += joeur->GetNumberOfCards();
	}
	return (counter / (float)size());
}
