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
private:
	Color m_color;

public:
	//Pawn(const Color& color) : m_color(color) {}
};


class Role
{
private:
	std::string m_name;
public:
	virtual const uint8_t getHandLimit() { return 7; }
	const char* getName() { return m_name.c_str(); }

	Role(const uint64_t& id);
};



class Player final
{
private:
	std::string m_name;
	std::vector<PlayerCard*> m_hand;
	Role* m_role;
	Pawn* m_pawn;

public:
	Player(const std::string& name, Role* role, Pawn* pawn) : m_name(name) { m_role = role; m_pawn = pawn; }
	~Player();

	void addCard(PlayerCard* card) { m_hand.emplace_back(card); }
	PlayerCard* rmCard(uint8_t pos);

	void printName();
	void printInfo();
	void printHand();
};