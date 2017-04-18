// Pandemic.cpp : Defines the entry point for the console application.
//

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"  
#endif // _WIN32

#include "Sources\GameEngine.h"

void PrintOpening();

int main()
{
#if _WIN32
	SetConsoleTitle(L"Pandemic board Game by Chris McArthur");
#endif // _WIN32

	PrintOpening(); // Generic Welcome Message

	GameEngine Game; // New Game Board
	Game.Initialize();
	Game.Launch();
	
	std::cout << "\n\nDemontration finished press 'enter' key to exit...";
	std::cin.get();
	return 0;
}

void PrintOpening()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::cout << "Pandemic Board Game by: Christopher McArthur ~ " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << " @ " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << std::endl << std::endl;
}
