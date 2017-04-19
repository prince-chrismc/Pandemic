///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Deck Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <deque>
#include "Cards.h"
#include "Statistics.h"

class Deck abstract //Primative Definition
{
protected:
	const uint16_t m_Size;
	Deck(const uint16_t& size) : m_Size(size) {}
};

class InfectionDeck : public Deck , public InfectionDeckStatisticsSubject //InfectionCard Pool/Factory
{
private:
	std::deque<InfectionCard::CardsList> m_Deck;
	std::deque<InfectionCard::CardsList> m_Discard;

public:
	InfectionDeck();

	///Prevent Copy/Assignment
	InfectionDeck(const InfectionDeck&) = delete;
	void operator=(const InfectionDeck&) = delete;
	
	std::deque<InfectionCard::CardsList> GetDiscardPile() const { return m_Discard; }
	void ReduceDeck(std::vector<CityList::CityID> cardstokeep);
	InfectionCard* DrawCard();
	InfectionCard* DrawCardForEpidemic();
	void Intensify();
	void ResiliantPopulation(const InfectionCard::CardsList& id);
	std::deque<InfectionCard*> GetForecast();
	void SetForecast(std::deque<InfectionCard*> top);
	uint16_t GetNumberOfCardRemaining() { return uint16_t(m_Deck.size()); }
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<InfectionCard::CardsList> deck, std::deque<InfectionCard::CardsList> discard);

	class Builder final
	{
	private:
		std::deque<InfectionCard::CardsList> m_Deck;
		std::deque<InfectionCard::CardsList> m_Discard;

		void AddToDeck(InfectionCard::CardsList cardId) { m_Deck.emplace_back(cardId); }
		void AddToDiscard(InfectionCard::CardsList cardId) { m_Discard.emplace_back(cardId); }

	public:
		Builder() : m_Deck(), m_Discard() {}

		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;
		
		Builder& ParseDeck(std::string loaded);
		Builder& ParseDiscard(std::string loaded);

		std::deque<InfectionCard::CardsList> GetDeck() { return m_Deck; }
		std::deque<InfectionCard::CardsList> GetDiscard() { return m_Discard; }
	};
};

class PlayerDeck final : public Deck, private PlayerCardFactory, public PlayerDeckStatisticsSubject //PlayerCards Pool/Abstract Factory
{
private:
	enum class Difficulty
	{
		INVALID,
		EASY,
		MEDIUM,
		HARD
	};

	std::deque<PlayerCard::CardsList> m_Deck;
	std::deque<PlayerCard::CardsList> m_Discard;
	Difficulty m_Difficulty;

public:
	PlayerDeck();

	///Prevent Copy/Assignment
	PlayerDeck(const PlayerDeck&) = delete;
	void operator=(const PlayerDeck&) = delete;

	std::deque<PlayerCard::CardsList> GetDiscardPile() { return m_Discard; }
	void ReduceDeck(std::vector<CityList::CityID> cardstokeep);
	bool IsDeckEmpty() { return (m_Deck.size() == 0); }
	PlayerCard* RemoveFromDiscard(const PlayerCard::CardsList& id);
	PlayerCard* DrawCard();
	void DiscardCard(PlayerCard* pc);
	void IncreaseDifficulty(const uint16_t& dif);
	uint16_t GetNumberOfCardRemaining() { return uint16_t(m_Deck.size()); }
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<PlayerCard::CardsList> deck, std::deque<PlayerCard::CardsList> discard);

	class Builder final
	{
	private:
		std::deque<PlayerCard::CardsList> m_Deck;
		std::deque<PlayerCard::CardsList> m_Discard;

		void AddToDeck(PlayerCard::CardsList cardId) { m_Deck.emplace_back(cardId); }
		void AddToDiscard(PlayerCard::CardsList cardId) { m_Discard.emplace_back(cardId); }

	public:
		Builder() : m_Deck(), m_Discard() {}

		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		Builder& ParseDeck(std::string loaded);
		Builder& ParseDiscard(std::string loaded);

		std::deque<PlayerCard::CardsList> GetDeck() { return m_Deck; }
		std::deque<PlayerCard::CardsList> GetDiscard() { return m_Discard; }
	};
};

class RoleDeck final : public Deck //RoleCard Pool/Factory
{
private:
	std::deque<RoleCard::Roles> m_Deck;

public:
	RoleDeck();

	///Prevent Copy/Assignment
	RoleDeck(const RoleDeck&) = delete;
	void operator=(const RoleDeck&) = delete;

	RoleCard* DrawCard();
	std::string GetSaveOutput();  //FilePrint
	void InputLoadedGame(std::deque<RoleCard::Roles> deck);

	class Builder final
	{
	private:
		std::deque<RoleCard::Roles> m_Deck;

		Builder() : m_Deck() {}
		void AddToDeck(RoleCard::Roles cardId) { m_Deck.emplace_back(cardId); }

	public:
		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		static Builder& GetInstance() { static Builder builder; return builder; }
		Builder& ParseDeck(std::string loaded);
		std::deque<RoleCard::Roles> GetDeck() { return m_Deck; }
	};
};