///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Board Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Deck.h"
#include "Token.h"
#include "WorldMap.h"

class Board
{
	friend class GameEngine;
private:
	WorldMap m_Map;
	InfectionRate m_InfectRate;
	OutbreakMarker m_OutBreak;
	DiseaseCubePile m_Cubes;
	InfectionDeck m_InfecDeck;
	PlayerDeck m_PlayerDeck;
	RoleDeck m_RoleDeck;
	CureMakers m_Cures;
	ResearchStations m_Centers;

protected:

public:
	Board() : m_Map(), m_InfectRate(), m_OutBreak(), m_Cubes(), m_InfecDeck(), m_PlayerDeck(), m_RoleDeck(), m_Cures(), m_Centers()  {}
	~Board() {}

	void InfectCity(const uint8_t& cubesToAdd = 1); // Draw infection card and infect city with X cubes of its color
	void AddResearchCenter(const CityList::CityID& id) { m_Centers.AddStation(m_Map.getCityWithID(id)); }
	void Outbreak(City* city); //add one cube of that city's color to all connected cities
	void Epidemic(); //Increase, Infect, Intensify
	PlayerCard* DrawPlayerCard() { return m_PlayerDeck.DrawCard(); }
	void DiscardPlayerCard(PlayerCard* pc) { m_PlayerDeck.DiscardCard(pc); }

};

