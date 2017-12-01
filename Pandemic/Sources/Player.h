/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
	PlayerCard* m_PlannersEventCard;
	Role m_Role;
	ReferenceCard m_RefCard;

protected:
	bool ValidateHand() { return (m_Hand.size() <= 7); }

public:
	Player(const std::string& name, RoleCard* card) : m_Name(name), m_Role(card), m_RefCard(), m_PlannersEventCard(nullptr) {}
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

	bool HasExtraCard() { return (m_PlannersEventCard != nullptr) && (GetRoleID() == RoleList::CONTIGENCY); }
	void AddExtraCard(PlayerCard* extra) {if (HasExtraCard()) { delete m_PlannersEventCard; m_PlannersEventCard = nullptr; } m_PlannersEventCard = extra; }
	PlayerCard* GetExtraCard() { if (HasExtraCard()) return m_PlannersEventCard; else return nullptr; }
	void RemoveExtraCard() { delete m_PlannersEventCard; m_PlannersEventCard = nullptr; }

	PlayerCharacteristics GetCharacteristics();
	void PrintRefCard();

	std::string GetSaveOutput();  //FilePrint

	class Builder final : private PlayerCardFactory
	{
	private:
		std::string m_Name;
		std::vector<PlayerCard*> m_Hand;
		PlayerCard* m_PlannersEventCard;
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

	float GetAverageNumberOfCards();
	uint16_t GetNumberOfPlayers() { return uint16_t(size()); }
};