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

