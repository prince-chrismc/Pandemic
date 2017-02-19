///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Wold Map Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Deck.h"
#include "Player.h"
#include "Token.h"

class WorldMap final
{
private:
	InfectionRate m_infectrate;
	OutbreakMarker m_outbreeak;
	DiseaseCubePile m_cubepiles;
	InfectionDeck m_infecdeck;
	PlayerDeck m_playerdeck;
	RoleDeck m_roledeck;
	
	City* m_cities[48];
	Cure* m_cures[4];
	std::vector<Player> m_players;

public:
	WorldMap();
	~WorldMap();
};

