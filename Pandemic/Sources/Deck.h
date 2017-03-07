///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Deck Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <deque>
#include "Cards.h"

class Deck abstract //Primative Definition
{
protected:
	const uint8_t m_size;
	Deck(const uint8_t& size) : m_size(size) {}
};

class InfectionDeck final : public Deck //InfectionCard Factory
{
private:
	std::deque<InfectionCard::CardsList> m_deck;
	std::deque<InfectionCard::CardsList> m_discard;

public:
	InfectionDeck();

	//Prevent Copy/Assignment
	InfectionDeck(const InfectionDeck&) = delete;
	void operator=(const InfectionDeck&) = delete;

	InfectionCard* DrawCard();
	InfectionCard* DrawCardForEpidemic();
	void Intensify();
	std::string GetSaveOutput();  //FilePrint
};

class PlayerDeck final : public Deck, private PlayerCardFactory //PlayerCards Factory
{
private:
	std::deque<PlayerCard::CardsList> m_deck;
	std::deque<PlayerCard::CardsList> m_discard;

public:
	PlayerDeck();

	//Prevent Copy/Assignment
	PlayerDeck(const PlayerDeck&) = delete;
	void operator=(const PlayerDeck&) = delete;

	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
	std::string GetSaveOutput();  //FilePrint
};

class RoleDeck final : public Deck //RoleCard Factory
{
private:
	std::deque<RoleCard::Roles> m_deck;

public:
	RoleDeck();

	//Prevent Copy/Assignment
	RoleDeck(const RoleDeck&) = delete;
	void operator=(const RoleDeck&) = delete;

	RoleCard* DrawCard();
	std::string GetSaveOutput();  //FilePrint
};