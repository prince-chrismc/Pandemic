// Pandemic.cpp : Defines the entry point for the console application.
//

#include "Sources\Deck.h"
#include "Sources\Player.h"

int main()
{
	InfectionDeck id;
	PlayerDeck pd;
	RoleDeck rd;

	Player jouer("chris", rd.DrawCard());
	jouer.addCard(pd.DrawCard());
	jouer.addCard(pd.DrawCard());
	jouer.addCard(pd.DrawCard());
	jouer.addCard(pd.DrawCard());
	jouer.addCard(pd.DrawCard());
	
	pd.DiscardCard(jouer.rmCard(2));
	pd.DiscardCard(jouer.rmCard(4));

    return 0;
}

