#include <cstdlib>
#include <ios> //std::hex
#include <sstream> //std::stringstream
#include "Cards.h"

uint64_t Card::getNumID()
{
	std::stringstream ss;
	ss << m_id;
	uint64_t num = 0;
	ss >> std::hex >> num;
	return num;
}

Card::Card(const CardsList& id, const char * name) : m_name(name)
{
	std::stringstream ss;
	ss << std::hex << id;
	m_id = ss.str();
}

Card::Card(const CardsList & id, const char * name, const char * desc) : m_description(desc)
{
	Card(id, name);
}

void Card::PrintInformation()
{
	printf("ID: %s \t Name: %s \t Desc: %s\n", m_id.c_str(), m_name.c_str(), m_description.c_str());
}

const char * Card::getCardName(Card card)
{
	const char* name = "";
		
	switch (card.getNumID())
	{
	case Card::INVALID:
	case PlayerCard::PLAYERCARD_MIN:
	case CityCard::CITYCARD_MIN:
	case CityCard::CITYCARD_MAX:
	case EventCard::EVENTCARD_MIN:
	case EventCard::EVENTCARD_MAX:
	case EpidemicCard::EPEDEMICCARD_MIN:
	case EpidemicCard::EPEDEMICCARD_MAX:
	case RoleCard::ROLECARD_MIN:
	case RoleCard::ROLECARD_MAX:
	case PlayerCard::PLAYERCARD_MAX:
	case ReferenceCards::REFERENCECARD_MIN:
	case ReferenceCards::REFERENCECARD_MAX:
	case InfectionCard::INFECTIONCARD_MIN:
	case InfectionCard::RED_MIN:
	case InfectionCard::RED_MAX:
	case InfectionCard::BLACK_MIN:
	case InfectionCard::BLACK_MAX:
	case InfectionCard::BLUE_MIN:
	case InfectionCard::BLUE_MAX:
	case InfectionCard::YELLOW_MIN:
	case InfectionCard::YELLOW_MAX:
	case InfectionCard::INFECTIONCARD_MAX:
	case Card::MAX:
		name = "Invalid";
		break;
	case InfectionCard::ALGIERS: name = "Algiers"; break;
	case InfectionCard::ATLANTA: name = "Atlanta"; break;
	case InfectionCard::BAGHDAD: name = "Baghdad"; break;
	case InfectionCard::BANGKOK: name = "Bangkok"; break;
	case InfectionCard::BEIJING: name = "Beijing"; break;
	case InfectionCard::BOGOTA: name = "Bogota"; break;
	case InfectionCard::BUENOSAIRES: name = "Buenos Aires"; break;
	case InfectionCard::CAIRO: name = "Cairo"; break;
	case InfectionCard::CHENNAI: name = "Chennai"; break;
	case InfectionCard::CHICAGO: name = "Chicago"; break;
	case InfectionCard::DELHI: name = "Delhi"; break;
	case InfectionCard::ESSEN: name = "Essen"; break;
	case InfectionCard::HOCHIMINH: name = "Ho Chi Minh City"; break;
	case InfectionCard::HONGKONG: name = "Hong Kong"; break;
	case InfectionCard::ISTANBUL: name = "Istanbul"; break;
	case InfectionCard::JAKARTA: name = "Jakarta"; break;
	case InfectionCard::JOHANNESBURG: name = "Johannesburg"; break;
	case InfectionCard::KARACHI: name = "Karachi"; break;
	case InfectionCard::KHARTOUM: name = "Khartoum"; break;
	case InfectionCard::KINSHASA: name = "Kinshasa"; break;
	case InfectionCard::KOLKATA: name = "Kolkata"; break;
	case InfectionCard::LAGOS: name = "Lagos"; break;
	case InfectionCard::LIMA: name = "Lima"; break;
	case InfectionCard::LONDON: name = "London"; break;
	case InfectionCard::LOSANGELES: name = "Los Angeles"; break;
	case InfectionCard::MADRID: name = "Madrid"; break;
	case InfectionCard::MANILA: name = "Manila"; break;
	case InfectionCard::MEXICO: name = "Mexico City"; break;
	case InfectionCard::MIAMI: name = "Miami"; break;
	case InfectionCard::MILAN: name = "Milan"; break;
	case InfectionCard::MONTREAL: name = "Montreal"; break;
	case InfectionCard::MOSCOW: name = "Moscow"; break;
	case InfectionCard::MUMBAI: name = "Mumbai"; break;
	case InfectionCard::NEWYORK: name = "NewYork"; break;
	case InfectionCard::OSAKA: name = "Osaka"; break;
	case InfectionCard::PARIS: name = "Paris"; break;
	case InfectionCard::RIYADH: name = "Riyadh"; break;
	case InfectionCard::SANFRAN: name = "San Francisco"; break;
	case InfectionCard::SANTIAGO: name = "Santiago"; break;
	case InfectionCard::SAOPAULO: name = "Sao Paulo"; break;
	case InfectionCard::SEOUL: name = "Seoul"; break;
	case InfectionCard::SHANGHAI: name = "Shanghai"; break;
	case InfectionCard::STPETER: name = "StPetersburg"; break;
	case InfectionCard::SYDNEY: name = "Sydney"; break;
	case InfectionCard::TAIPEI: name = "Taipei"; break;
	case InfectionCard::TEHRAN: name = "Tehran"; break;
	case InfectionCard::TOKYO: name = "Tokyo"; break;
	case InfectionCard::WASHINGTON: name = "Washington"; break;

	default:
		break;
	}
	return name;
}
