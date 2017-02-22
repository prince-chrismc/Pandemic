///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Deck Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <deque>
#include "Cards.h"

/*
TODO:

redesign of decks ! cards pile wil be vector ofstring IDs and on card draw a new 
will be returned and added to discard or hand ... reducing heap allocation
same thing to be applied to cube piles 

*/

class Deck abstract
{
protected:
	const uint8_t m_size;
	Deck(const uint8_t& size) : m_size(size) {}
};

class InfectionDeck final : Deck
{
private:
	std::deque<InfectionCard::CardsList> m_deck;
	std::deque<InfectionCard::CardsList> m_discard;

public:
	InfectionDeck();

	InfectionCard* DrawCard();
};

class PlayerDeck final : Deck
{
private:
	std::deque<PlayerCard::CardsList> m_deck;
	std::deque<PlayerCard::CardsList> m_discard;

public:
	PlayerDeck();

	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
};

class RoleDeck final : public Deck
{
private:
	std::deque<RoleCard::Roles> m_deck;

public:
	RoleDeck();

	RoleCard* DrawCard();
};