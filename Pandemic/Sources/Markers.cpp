#include "Markers.h"

InfectionRate::Builder& InfectionRate::Builder::ParseInfectionRate(std::string loaded)
{
	switch (loaded.at(0))
	{
	case '0':
		m_Position = 0;
		break;
	case '1':
		m_Position = 1;
		break;
	case '2':
		m_Position = 2;
		break;
	case '3':
		m_Position = 3;
		break;
	case '4':
		m_Position = 4;
		break;
	case '5':
		m_Position = 5;
		break;
	case '6':
		m_Position = 6;
		break;
	default:
		m_Position = 0;
		break;
	}
	return *this;
}

OutbreakMarker::Builder& OutbreakMarker::Builder::ParseOutbreakMarker(std::string loaded)
{
	switch (loaded.at(0))
	{
	case '0':
		m_Position = 0;
		break;
	case '1':
		m_Position = 1;
		break;
	case '2':
		m_Position = 2;
		break;
	case '3':
		m_Position = 3;
		break;
	case '4':
		m_Position = 4;
		break;
	case '5':
		m_Position = 5;
		break;
	case '6':
		m_Position = 6;
		break;
	case '7':
		m_Position = 7;
		break;
	default:
		m_Position = 0;
		break;
	}

	return *this;
}
