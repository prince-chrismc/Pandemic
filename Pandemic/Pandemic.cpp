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

// Pandemic.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"  
#endif // _WIN32

#include "Sources\GameEngine.h"

void PrintOpening();

int main()
{
#ifdef _WIN32
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
