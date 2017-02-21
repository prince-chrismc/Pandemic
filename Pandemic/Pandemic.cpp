// Pandemic.cpp : Defines the entry point for the console application.
//

#include <ctime>
#include <iostream>
#include "Sources\WorldMap.h"

void PrintOpening();
void PrintPlayerOptions(Player* joeur, WorldMap map);

int main()
{
	PrintOpening();

	WorldMap wm;
	wm.RegisterPlayer("Chris");
	Player* Chris = wm.GetPlayer(0);
	
	wm.RegisterPlayer("Barclay");
	Player* Barclay = wm.GetPlayer(1);
	
	Chris->printInfo();
	Barclay->printInfo();
	Barclay->printRefCard();

	wm.DrawPlayerCardFor(Chris);
	wm.DrawPlayerCardFor(Chris);
	wm.DrawPlayerCardFor(Chris);
	wm.DrawPlayerCardFor(Chris);
	wm.DrawPlayerCardFor(Chris);

	wm.DrawPlayerCardFor(Barclay);
	wm.DrawPlayerCardFor(Barclay);
	wm.DrawPlayerCardFor(Barclay);
	wm.DrawPlayerCardFor(Barclay);
	wm.DrawPlayerCardFor(Barclay);

	Chris->printHand();
	PrintPlayerOptions(Chris, wm);

	Barclay->printHand();
	PrintPlayerOptions(Barclay, wm);

	wm.printCitiesStatus();
	wm.InfectCity(3);
	wm.InfectCity(3);
	wm.InfectCity(3);
	wm.InfectCity(2);
	wm.InfectCity(2);
	wm.InfectCity(2);
	wm.InfectCity(1);
	wm.InfectCity(1);
	wm.InfectCity(1);
	wm.printCitiesStatus();

    return 0;
}

void PrintOpening()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::cout << "Pandemic Board Game by: Christopher McArthur ~ " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << " @ " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << std::endl;
}

// Sample test for outputting player options to move...
void PrintPlayerOptions(Player* joeur, WorldMap map)
{
	joeur->printInfo();
	int i = 1;
	printf("  A. Drive/Ferry Options\n");
	const std::vector<City*> nbc = map.getCitiesConnectedTo(joeur->getCityID());
	for (size_t s = 0; s < nbc.size(); s += 1)
	{
		printf("    %d: ", i++);
		nbc.at(s)->PrintInformation();
	}

	std::vector<CityList::CityID> dfcID = joeur->getDirectFlightCities();
	if (dfcID.size() > 0)
	{
		printf("  B. Direct Flight Options\n");
		for (size_t s = 0; s < dfcID.size(); s += 1)
		{
			printf("    %d: ", i++);
			if (map.getCityWithID(dfcID.at(s)) != NULL)
				map.getCityWithID(dfcID.at(s))->PrintInformation();
			else
				break;
		}
	}

	if (joeur->hasCurrentCityCard())
	{
		printf("  C. Charter Flight.\n    %d: Pick Any City!\n", i++);
	}

	if (map.multipleResearchCentersExist())
	{
		printf("  D. Shuttle Flight.\n    %d: NOT IMPLEMENTED !\n", i++);
	}

	if (joeur->canBuildResearchCenter())
	{
		printf("  D. Shuttle Flight.\n    %d: NOT IMPLEMENTED !\n", i++);
	}

	printf("  F. Treat Disease.\n    %d: Remove Cube(s)\n", i++);

	printf("  E. Share Knowledge.\n    %d: NOT IMPLEMENTED !\n", i++);

	if (joeur->canDiscoverCure())
	{
		printf("  E. Discover Cure.\n    %d: NOT IMPLEMENTED !\n", i++);
	}
}