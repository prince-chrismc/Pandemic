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

