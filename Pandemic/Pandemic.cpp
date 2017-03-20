// Pandemic.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <ctime>
#include <iostream>
#include "Sources\GameEngine.h"

void PrintOpening();

int main()
{
	SetConsoleTitle(L"Pandemic board Game by Chris McArthur");
	PrintOpening(); // Generic Welcome Message

	GameEngine Game; // New Game Board
	//Game.LoadGame();
	Game.Initialize();
	Game.Launch();

	//Game.SaveGame();

	std::cout << "\n\nDemontration finished press 'enter' key to exit...";
	std::cin.get();
	return 0;
}

void PrintOpening()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::cout << "Pandemic Board Game by: Christopher McArthur ~ " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << " @ " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << std::endl;
}
