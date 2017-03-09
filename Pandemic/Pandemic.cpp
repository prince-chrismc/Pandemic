// Pandemic.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <ctime>
#include <iostream>
#include "Sources\GameEngine.h"

void PrintOpening();
void PrintPlayerOptions(Player* joeur, WorldMap* map);

int main()
{
	SetConsoleTitle(L"Pandemic board Game by Chris McArthur");
	PrintOpening(); //Generic Welcome Message

	GameEngine Game; //New Game Board

	Game.Initialize();

	Player* Chris = Game.GetPlayer(0);
	Player* Barclay = Game.GetPlayer(1);

	Chris;
	Barclay;

	std::cout << "\n\nDemontration finished press any key to exit...";
	std::cin.get();
    return 0;
}

void PrintOpening()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::cout << "Pandemic Board Game by: Christopher McArthur ~ " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << " @ " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << std::endl;
}

// Sample test for outputting player options - TODO: move
//void PrintPlayerOptions(Player* joeur, WorldMap* map)
//{
//	printf("\n\n");
//	joeur->printInfo();
//	int i = 1;
//	printf("  A. Drive/Ferry Options\n");
//	const std::vector<City*> nbc = map->getCitiesConnectedTo(joeur->getCityID());
//	for (size_t s = 0; s < nbc.size(); s += 1)
//	{
//		printf("    %d: ", i++);
//		nbc.at(s)->PrintInformation();
//	}
//
//	std::vector<CityList::CityID> dfcID = joeur->getDirectFlightCities();
//	if (dfcID.size() > 0)
//	{
//		printf("  B. Direct Flight Options\n");
//		for (size_t s = 0; s < dfcID.size(); s += 1)
//		{
//			printf("    %d: ", i++);
//			if (map->getCityWithID(dfcID.at(s)) != nullptr)
//				map->getCityWithID(dfcID.at(s))->PrintInformation();
//			else
//				break;
//		}
//	}
//
//	if (joeur->hasCurrentCityCard())
//	{
//		printf("  C. Charter Flight.\n    %d: Pick Any City!\n", i++);
//	}
//
//	if (map->multipleResearchCentersExist())
//	{
//		printf("  D. Shuttle Flight.\n    %d: NOT IMPLEMENTED !\n", i++);
//	}
//
//	if (joeur->canBuildResearchCenter())
//	{
//		printf("  D. Shuttle Flight.\n    %d: NOT IMPLEMENTED !\n", i++);
//	}
//
//	printf("  F. Treat Disease.\n    %d: Remove Cube(s)\n", i++);
//
//	printf("  E. Share Knowledge.\n    %d: NOT IMPLEMENTED !\n", i++);
//
//	if (joeur->canDiscoverCure())
//	{
//		printf("  E. Discover Cure.\n    %d: NOT IMPLEMENTED !\n", i++);
//	}
//}