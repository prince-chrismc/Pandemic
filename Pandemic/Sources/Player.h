///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Player Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Pandemic.h"
#include "Cards.h"


class Pawn final
{
	friend class Role;
public:
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

	Pawn(const uint64_t& color);

protected:
	std::hexadecimal m_CityID; 
	PawnColor m_color;

};

class Role
{
private:
	std::string m_name;
	std::hexadecimal m_roleID;
	Pawn* m_pawn;
	RoleCard* m_card;
	Role(const uint64_t& id);

public:
	virtual const uint8_t getHandLimit() { return 7; }
	const char* getName() { return m_name.c_str(); }

	Role(RoleCard* card);
	~Role();
};

class Player final
{
private:
	std::string m_name;
	std::vector<PlayerCard*> m_hand;
	Role* m_role;

public:
	Player(const std::string& name, RoleCard* card) : m_name(name), m_role(new Role(card)) {}
	~Player();

	void addCard(PlayerCard* card) { m_hand.emplace_back(card); }
	PlayerCard* rmCard(uint8_t pos);

	void printName();
	void printInfo();
	void printHand();
};