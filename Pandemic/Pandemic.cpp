// Pandemic.cpp : Defines the entry point for the console application.
//

#include "Sources\Deck.h"
#include "Sources\Player.h"

int main()
{
	InfectionDeck deck;
	PlayerDeck player;

	Player jouer("chris", new Role(RoleList::MEDIC), new Pawn());
	jouer.addCard(player.DrawCard());
	jouer.addCard(player.DrawCard());
	jouer.addCard(player.DrawCard());
	jouer.addCard(player.DrawCard());
	jouer.addCard(player.DrawCard());
	
    return 0;
}

