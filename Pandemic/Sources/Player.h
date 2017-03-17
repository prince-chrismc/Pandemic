///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Player Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "Pandemic.h"
#include "Cards.h"

class Pawn final //Object on board to represent player
{
	friend class Player;
private:
	enum PawnColor
	{
		CYAN = RoleList::CONTIGENCY,
		PINK = RoleList::DISPATCHER,
		ORANGE = RoleList::MEDIC,
		YELLOWGREEN = RoleList::OPERATIONS,
		FORESTGREEN = RoleList::QUARANTINE,
		BROWN = RoleList::RESEARCHER,
		WHITE = RoleList::SCIENTIST,
	};

	std::hexadecimal m_CityID;
	PawnColor m_Color;

public:
	Pawn(const uint64_t& color);

	//Prevent Copy/Assignment
	Pawn(const Pawn&) = delete;
	void operator=(const Pawn&) = delete;
};

class Role //Defines Role Attributes held by a player
{
	friend class Player;
private:
	const std::string m_Name;
	std::hexadecimal m_roleID;
	Pawn m_Pawn;
	RoleCard* m_Card;

protected:
	Role(const uint64_t& id);

public:
	Role(RoleCard* card);
	~Role();

	//Prevent Copy/Assignment
	Role(const Role&) = delete;
	void operator=(const Role&) = delete;
};

class Player final //The Almighty Player
{
	friend class GameEngine;
private:
	const std::string m_Name;
	std::vector<PlayerCard*> m_Hand;
	Role m_Role;
	ReferenceCard m_RefCard;

protected:
	bool ValidateHand() { return (m_Hand.size() <= 7); }

public:
	Player(const std::string& name, RoleCard* card) : m_Name(name), m_Role(card), m_RefCard() {}
	~Player();

	//Prevent Copy/Assignment
	Player(const Player&) = delete;
	void operator=(const Player&) = delete;

	//Manipulate Hand
	void AddCard(PlayerCard* card) { m_Hand.emplace_back(card); }
	PlayerCard* RemoveCard(const CityList::CityID& id);
	PlayerCard* RemoveCardAt(const uint16_t& pos);

	//Get/Set City
	CityList::CityID GetCityID();
	void ChangeCity(const std::hexadecimal& id) { m_Role.m_Pawn.m_CityID = id; }

	//utility
	bool HasCurrentCityCard();
	RoleList::Roles GetRoleID() { return (RoleList::Roles)m_Role.m_Card->GetNumID(); }
	uint16_t GetNumOfCardToDiscoverCure();

	void PrintInfo();
	void PrintHand();
	void PrintRefCard();

	std::string GetSaveOutput();  //FilePrint
};