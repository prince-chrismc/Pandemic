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

#include <iostream>
#include <string>
#include "Statistics.h"

bool GameStatistics::Print()
{
	std::cout << std::endl << GameStatistics::Statistics::Builder::GetInstance().InputCardsPerPlayer(dynamic_cast<PlayerStatisticsSubject*>(m_PlayersContainer)->GetAverageNumberOfCards()).InputCubesOnTheBoard(dynamic_cast<WorldMapStatisticsSubject*>(m_WorldMap)->GetNumberOfCubeOnBoard()).InputNumInfectedCities(dynamic_cast<WorldMapStatisticsSubject*>(m_WorldMap)->GetNumberOfInfectedCities()).InputResearchCentersNotUsed(dynamic_cast<ResearchStatisticsSubject*>(m_ResearchStations)->GetNumberOfUnusedCenters()).InputPlayerCardsLeft(dynamic_cast<PlayerDeckStatisticsSubject*>(m_PlayerDeck)->GetNumberOfCardRemaining()).InputInfectionCardsLeft(dynamic_cast<InfectionDeckStatisticsSubject*>(m_InfectionDeck)->GetNumberOfCardRemaining()).GetStatistics().GetPrintOutput(); return true;
}

void GameStatistics::ChangeFrequency(IGameStatsDisplay * deco)
{
	if (m_Display != nullptr) 
		delete m_Display; 
	
	m_Display = deco;
}

bool GameStatisticsExtended::Print()
{
	std::cout << GameStatisticsExtended::Statistics::Builder::GetInstance().InputNumInfectedCities(dynamic_cast<GameStatistics*>(m_Stats)->GetNumberOfInfectedCities()).GetStatistics().GetPrintOutput(); return true;
}

std::string GameStatisticsClocked::GetPrintOutput()
{
	clock_t dif = std::clock() - m_CurrentSessionStartTime;
	double min, sec, fraction;
	fraction = modf(dif / (double)(clock_t)1000 / 60.0, &min);
	fraction = modf(dif / (double)(clock_t)1000, &sec);
	sec = sec - (min*60.0);
	return "\n - Current Runtime (min:sec): " + std::to_string((long)min) + std::string((sec<10) ? ":0" : ":") + std::to_string((long)sec);
}

bool GameStatisticsClocked::Print()
{
	std::cout << GetPrintOutput() << std::endl << std::endl; return true;
}

