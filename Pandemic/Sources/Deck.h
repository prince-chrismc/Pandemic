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

	InfectionCard* DrawCard();
};

class PlayerDeck final : public Deck, private PlayerCardFactory //PlayerCards Factory
{
private:
	std::deque<PlayerCard::CardsList> m_deck;
	std::deque<PlayerCard::CardsList> m_discard;

public:
	PlayerDeck();

	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
};

class RoleDeck final : public Deck //RoleCard Factory
{
private:
	std::deque<RoleCard::Roles> m_deck;

public:
	RoleDeck();

	RoleCard* DrawCard();
};