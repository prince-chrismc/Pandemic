///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Player Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include "Pandemic.h"
#include "Cards.h"
#include "Observers.h"
#include "Statistics.h"

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

	///Prevent Copy/Assignment
	Pawn(const Pawn&) = delete;
	void operator=(const Pawn&) = delete;

	std::string GetColor();
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

	///Prevent Copy/Assignment
	Role(const Role&) = delete;
	void operator=(const Role&) = delete;
};

class Player final : public PlayerSubject //The Almighty Player
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

	///Prevent Copy/Assignment
	Player(const Player&) = delete;
	void operator=(const Player&) = delete;

	std::string GetName() const { return m_Name; }
	/// Manipulate Hand
	void AddCard(PlayerCard* card) { m_Hand.emplace_back(card); Notify(); }
	PlayerCard* RemoveCard(const CityList::CityID& id);
	PlayerCard* RemoveCardAt(const uint16_t& pos);

	/// Get/Set City
	CityList::CityID GetCityID();
	void ChangeCity(const std::hexadecimal& id) { m_Role.m_Pawn.m_CityID = id; Notify(); }
	const uint16_t GetNumberOfCards() { return uint16_t(m_Hand.size()); }

	///utility
	bool HasCurrentCityCard();
	RoleList::Roles GetRoleID() { return (RoleList::Roles)m_Role.m_Card->GetNumID(); }
	uint16_t GetNumOfCardToDiscoverCure();

	PlayerCharacteristics GetCharacteristics();
	void PrintRefCard();

	std::string GetSaveOutput();  //FilePrint

	class Builder final : private PlayerCardFactory
	{
	private:
		std::string m_Name;
		std::vector<PlayerCard*> m_Hand;
		RoleList::Roles m_RoleID;
		std::hexadecimal m_CityID;

		Builder& ParseHand(std::string loaded);

	public:
		Builder() : m_Name(), m_Hand(), m_RoleID(), m_CityID() {}

		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		Builder& ParsePlayer(std::string loaded);
		Player* GetPlayer();
	};
};

/// Container to allow for observation
class PlayersContainer final : public std::vector<Player*>, public PlayerStatisticsSubject
{
public:
	PlayersContainer() {}
	~PlayersContainer() { for each(Player* joeur in *this) { delete joeur; joeur = nullptr; } }

	void InputLoadedGame(std::vector<Player*> joeur) { (std::vector<Player*>)*this = joeur; }

	float GetAverageNumberOfCards();
	uint16_t GetNumberOfPlayers() { return uint16_t(size()); }
};