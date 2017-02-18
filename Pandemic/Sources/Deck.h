///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Deck Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <deque>
#include "Cards.h"

class Deck abstract
{
protected:
	const uint8_t m_size;
	Deck(const uint8_t& size) : m_size(size) {}
};

class InfectionDeck final : Deck
{
private:
	std::deque<InfectionCard*> m_deck;
	std::deque<InfectionCard*> m_discard;

public:
	InfectionDeck();
	~InfectionDeck();

	InfectionCard* DrawCard();
};

class PlayerDeck final : Deck
{
private:
	std::deque<PlayerCard*> m_deck;
	std::deque<PlayerCard*> m_discard;

public:
	PlayerDeck();
	~PlayerDeck();

	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
};

class RoleDeck final : public Deck
{
private:
	std::deque<RoleCard*> m_deck;

public:
	RoleDeck();
	~RoleDeck();

	RoleCard* DrawCard();
};