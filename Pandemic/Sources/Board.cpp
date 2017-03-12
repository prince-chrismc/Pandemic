#include <algorithm> //std::shuffle
#include <random> //std::mt19937
#include "Board.h"

void Board::InfectCity(const uint16_t& cubesToAdd)
{
	InfectionCard* ic = m_InfecDeck.DrawCard();
	City::CityID cid = (City::CityID)(ic->getNumID() - InfectionCard::INFECTIONCARD_MIN);
	delete ic; ic = nullptr;

	City* city = m_Map.getCityWithID(cid);

	for (uint16_t i = 0; i < cubesToAdd; i += 1)
	{
		if (city->GetNumberOfCubes() == 3)
		{
			Outbreak(city);
			break;
		}
		else
		{
			city->addCube(m_Cubes.takeCube(city->getCityColor()));
		}
	}
}

void Board::Outbreak(City* city)
{
	m_OutBreak.IncreaseRate();

	for each(City* connected in city->getNearByCities())
	{
		connected->addCube(m_Cubes.takeCube(city->getCityColor()));
	}
}

void Board::Epidemic()
{
	// 1. Increase Infection Rate
	m_InfectRate.IncreaseRate();

	// 2. Infect Last Card of InfectionDeck with at most 3 Cubes
	InfectionCard* ic = m_InfecDeck.DrawCardForEpidemic();
	Color c = ic->getCityColor();
	if(m_Cures.IsNotEradicated(c))
	{
		City::CityID cid = (City::CityID)(ic->getNumID() - InfectionCard::INFECTIONCARD_MIN);
		delete ic; ic = nullptr;

		City* city = m_Map.getCityWithID(cid);

		for (uint16_t i = city->GetNumberOfCubes(); i < 3; i += 1)
			city->addCube(m_Cubes.takeCube(city->getCityColor()));

		// 2.1. Otbreaks if Need be
		if (city->GetNumberOfCubes() > 0)
		{
			Outbreak(city);
		}

		// 3. Intensify reshuffle infect discard and add on top of deck
		m_InfecDeck.Intensify();
	}
}
