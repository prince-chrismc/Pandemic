///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Player Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Pandemic.h"
#include "Cards.h"

class Pawn final //Object on board to represent player
{
	friend class Player;
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

private:
	std::hexadecimal m_CityID; 
	PawnColor m_color;

public:
	Pawn(const uint64_t& color);

	//Prevent Copy/Assignment
	Pawn(const Pawn&) = delete;
	void operator=(const Pawn&) = delete;

	void changeCity(const std::hexadecimal& id) { m_CityID = id; }
};

class Role //Defines Role Attributes held by a player
{
	friend class Player;
private:
	const std::string m_name;
	std::hexadecimal m_roleID;
	Pawn* m_pawn;
	RoleCard* m_card;

	Role(const uint64_t& id);

public:
	Role(RoleCard* card);
	~Role();

	//Prevent Copy/Assignment
	Role(const Role&) = delete;
	void operator=(const Role&) = delete;

	virtual const uint8_t getHandLimit() { return 7; }
	const char* getName() { return m_name.c_str(); }
};

class Player final //The Almighty Player
{
private:
	const std::string m_name;
	std::vector<PlayerCard*> m_hand;
	Role* m_role;
	ReferenceCard m_refcard;

public:
	Player(const std::string& name, RoleCard* card) : m_name(name), m_role(new Role(card)), m_refcard() {}
	~Player();

	//Prevent Copy/Assignment
	Player(const Player&) = delete;
	void operator=(const Player&) = delete;

	//Manipulate Hand
	void addCard(PlayerCard* card) { m_hand.emplace_back(card); }
	PlayerCard* rmCard(uint8_t pos);

	//Get/Set City
	std::hexadecimal getCityHexID() { return m_role->m_pawn->m_CityID; }
	CityList::CityID getCityID();
	void ChangeCity(const std::hexadecimal& id) { m_role->m_pawn->changeCity(id); }

	//For game play
	std::vector<CityList::CityID> getDirectFlightCities();
	bool hasCurrentCityCard();
	/* TODO: HAVENT BEEN IMPLEMENTED */
	bool canBuildResearchCenter() { return false; }
	bool canDiscoverCure() { return false; }

	void printName();
	void printInfo();
	void printHand();
	void printRefCard();
};