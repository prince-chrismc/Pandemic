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
	CureMakers m_cures;
	
	City* m_cities[48];
	std::vector<ResearchCenter> m_centers;
	std::vector<Player*> m_players;

public:
	WorldMap();
	~WorldMap();

	void RegisterPlayer(const std::string& newPlayerName) { m_players.emplace_back(new Player(newPlayerName, m_roledeck.DrawCard())); }
	void InfectCity(const uint8_t& cubesToAdd = 1);

	Player* GetPlayer(const uint8_t pos) { return m_players.at(pos); }
	void DrawPlayerCardFor(Player* joeur) { joeur->addCard(m_playerdeck.DrawCard()); }
	void DiscardPlayerCardFor(Player* joeur, const uint8_t pos) { m_playerdeck.DiscardCard(joeur->rmCard(pos)); }

	std::vector<City*> getCitiesConnectedTo(const City::CityID& id);
	City* getCityWithID(const City::CityID& id);
	void printCitiesStatus();
	/* TODO: HAVENT BEEN IMPLEMENTED */
	bool multipleResearchCentersExist() { return false; }
};

