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

class Board final // Container Class
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
	CureMarkers m_Cures;
	ResearchStations m_Centers;
	WorldObserver m_WorldObserver;
	CureObserver m_CureObserver;
	
public:
	Board() : m_Map(), m_InfectRate(), m_OutBreak(), m_Cubes(), m_InfecDeck(), m_PlayerDeck(), m_RoleDeck(), m_Cures(), m_Centers(), m_WorldObserver(&m_Centers, &m_Map), m_CureObserver(&m_Cures) { m_Map.MapSubject::RegistarObserver(&m_WorldObserver); m_Centers.StationsSubject::RegistarObserver(&m_WorldObserver); m_Cures.RegistarObserver(&m_CureObserver); }
	~Board() {}

	///Prevent Copy/Assignment
	Board(const Board&) = delete;
	void operator=(const Board&) = delete;
};

