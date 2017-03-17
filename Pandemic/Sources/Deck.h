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
	const uint16_t m_Size;
	Deck(const uint16_t& size) : m_Size(size) {}
};

class InfectionDeck final : public Deck //InfectionCard Factory
{
private:
	std::deque<InfectionCard::CardsList> m_Deck;
	std::deque<InfectionCard::CardsList> m_Discard;

public:
	InfectionDeck();

	//Prevent Copy/Assignment
	InfectionDeck(const InfectionDeck&) = delete;
	void operator=(const InfectionDeck&) = delete;

	InfectionCard* DrawCard();
	InfectionCard* DrawCardForEpidemic();
	void Intensify();
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<InfectionCard::CardsList> deck, std::deque<InfectionCard::CardsList> discard);
};

class PlayerDeck final : public Deck, private PlayerCardFactory //PlayerCards Factory
{
private:
	std::deque<PlayerCard::CardsList> m_Deck;
	std::deque<PlayerCard::CardsList> m_Discard;
	Difficulty::DIFFICULTY m_Difficulty;

public:
	PlayerDeck();

	//Prevent Copy/Assignment
	PlayerDeck(const PlayerDeck&) = delete;
	void operator=(const PlayerDeck&) = delete;

	bool IsDeckEmpty() { return (m_Deck.size() == 0); }
	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
	void IncreaseDifficulty(const Difficulty::DIFFICULTY& dif);
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<PlayerCard::CardsList> deck, std::deque<PlayerCard::CardsList> discard);
};

class RoleDeck final : public Deck //RoleCard Factory
{
private:
	std::deque<RoleCard::Roles> m_Deck;

public:
	RoleDeck();

	//Prevent Copy/Assignment
	RoleDeck(const RoleDeck&) = delete;
	void operator=(const RoleDeck&) = delete;

	RoleCard* DrawCard();
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<RoleCard::Roles> deck);
};