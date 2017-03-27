///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Board Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "WorldMap.h"
#include "Markers.h"
#include "Deck.h"
#include "Cure.h"

class Board // Container Class
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
	Board() : m_Map(), m_InfectRate(), m_OutBreak(), m_Cubes(), m_InfecDeck(), m_PlayerDeck(), m_RoleDeck(), m_Cures(), m_Centers() {}
	~Board() {}
};

