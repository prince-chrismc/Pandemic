#include <cstdlib> //printf
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

Card::Card(const uint64_t & id, const char* name, const char* desc) : m_name(name), m_description(desc)
{
	std::stringstream ss;
	ss << std::hex << id;
	m_id = ss.str();
}

void Card::PrintInformation()
{
	printf("ID: %s \t Name: %s \t Desc: %s\n", m_id.c_str(), m_name.c_str(), m_description.c_str());
}

// In here lies very bad OOP but all definitions are public so for convience this is an easy out
const char* Card::getCardName(const uint64_t id)
{
	const char* name = "";
		
	switch (id)
	{
	case Card::INVALID:
	case PlayerCard::PLAYERCARD_MIN:
	case CityCard::CITYCARD_MIN:
	case CityCard::RED_MIN:
	case CityCard::RED_MAX:
	case CityCard::BLACK_MIN:
	case CityCard::BLACK_MAX:
	case CityCard::BLUE_MIN:
	case CityCard::BLUE_MAX:
	case CityCard::YELLOW_MIN:
	case CityCard::YELLOW_MAX:
	case CityCard::CITYCARD_MAX:
	case EventCard::EVENTCARD_MIN:
	case EventCard::EVENTCARD_MAX:
	case EpidemicCard::EPIDEMICCARD_MIN:
	case EpidemicCard::EPIDEMICCARD_MAX:
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
		name = "Invalid"; break;

	case CityCard::ALGIERS: name = "Algiers"; break;
	case CityCard::ATLANTA: name = "Atlanta"; break;
	case CityCard::BAGHDAD: name = "Baghdad"; break;
	case CityCard::BANGKOK: name = "Bangkok"; break;
	case CityCard::BEIJING: name = "Beijing"; break;
	case CityCard::BOGOTA: name = "Bogota"; break;
	case CityCard::BUENOSAIRES: name = "Buenos Aires"; break;
	case CityCard::CAIRO: name = "Cairo"; break;
	case CityCard::CHENNAI: name = "Chennai"; break;
	case CityCard::CHICAGO: name = "Chicago"; break;
	case CityCard::DELHI: name = "Delhi"; break;
	case CityCard::ESSEN: name = "Essen"; break;
	case CityCard::HOCHIMINH: name = "Ho Chi Minh City"; break;
	case CityCard::HONGKONG: name = "Hong Kong"; break;
	case CityCard::ISTANBUL: name = "Istanbul"; break;
	case CityCard::JAKARTA: name = "Jakarta"; break;
	case CityCard::JOHANNESBURG: name = "Johannesburg"; break;
	case CityCard::KARACHI: name = "Karachi"; break;
	case CityCard::KHARTOUM: name = "Khartoum"; break;
	case CityCard::KINSHASA: name = "Kinshasa"; break;
	case CityCard::KOLKATA: name = "Kolkata"; break;
	case CityCard::LAGOS: name = "Lagos"; break;
	case CityCard::LIMA: name = "Lima"; break;
	case CityCard::LONDON: name = "London"; break;
	case CityCard::LOSANGELES: name = "Los Angeles"; break;
	case CityCard::MADRID: name = "Madrid"; break;
	case CityCard::MANILA: name = "Manila"; break;
	case CityCard::MEXICO: name = "Mexico City"; break;
	case CityCard::MIAMI: name = "Miami"; break;
	case CityCard::MILAN: name = "Milan"; break;
	case CityCard::MONTREAL: name = "Montreal"; break;
	case CityCard::MOSCOW: name = "Moscow"; break;
	case CityCard::MUMBAI: name = "Mumbai"; break;
	case CityCard::NEWYORK: name = "NewYork"; break;
	case CityCard::OSAKA: name = "Osaka"; break;
	case CityCard::PARIS: name = "Paris"; break;
	case CityCard::RIYADH: name = "Riyadh"; break;
	case CityCard::SANFRAN: name = "San Francisco"; break;
	case CityCard::SANTIAGO: name = "Santiago"; break;
	case CityCard::SAOPAULO: name = "Sao Paulo"; break;
	case CityCard::SEOUL: name = "Seoul"; break;
	case CityCard::SHANGHAI: name = "Shanghai"; break;
	case CityCard::STPETER: name = "St Petersburg"; break;
	case CityCard::SYDNEY: name = "Sydney"; break;
	case CityCard::TAIPEI: name = "Taipei"; break;
	case CityCard::TEHRAN: name = "Tehran"; break;
	case CityCard::TOKYO: name = "Tokyo"; break;
	case CityCard::WASHINGTON: name = "Washington"; break;

	case EventCard::RESILLIENT: name = "Resillient Population"; break;
	case EventCard::AIRLIFT: name = "Air Lift"; break;
	case EventCard::FORECAST: name = "Forecast"; break;
	case EventCard::QUIETNIGHT: name = "One Quiet Night"; break;
	case EventCard::GOVTGRANT: name = "Government Grant"; break;

	case EpidemicCard::EPIDEMICCARDONE:
	case EpidemicCard::EPIDEMICCARDTWO:
	case EpidemicCard::EPIDEMICCARDTHREE:
	case EpidemicCard::EPIDEMICCARDFOUR: 
		name = "Epidemic Card"; break;

	case RoleCard::CONTIGENCY: name = "Contingency Planner"; break;
	case RoleCard::DISPATCHER: name = "Dispatcher"; break;
	case RoleCard::MEDIC: name = "Medic"; break;
	case RoleCard::QUARANTINE: name = "Quarantine Specalist"; break;
	case RoleCard::RESEARCHER: name = "Reseacher"; break;
	case RoleCard::SCIENTIST: name = "Scientist"; break;

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
	case InfectionCard::STPETER: name = "St Petersburg"; break;
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

Color CityCard::getCityColor(const uint64_t & id)
{
	if (IsRedCity(id)) return RED;
	else if (IsYellowCity(id)) return YELLOW;
	else if (IsBlueCity(id)) return BLUE;
	else if (IsBlackCity(id)) return BLACK;
}

const char* EventCard::getCardDesc(const uint64_t& id)
{
	const char* desc = "";
	switch(id)
	{
	case EventCard::RESILLIENT: desc = "Remove a discarded infection card"; break;
	case EventCard::AIRLIFT: desc = "Move any pawn to any city; ask permission if neccessary"; break;
	case EventCard::FORECAST: desc = "Look at the top 6 cards of the infection deck and put them in any order you choose then put them back on top of the infection deck"; break;
	case EventCard::QUIETNIGHT: desc = "Skip the next infection phase"; break;
	case EventCard::GOVTGRANT: desc = "build a research station in any city"; break;
	}
	return desc;
}

Color InfectionCard::getCityColor(const uint64_t & id)
{
	if (IsRedCity(id)) return RED;
	else if (IsYellowCity(id)) return YELLOW;
	else if (IsBlueCity(id)) return BLUE;
	else if (IsBlackCity(id)) return BLACK;
}

InfectionCard::InfectionCard(const CardsList& id) : Card( id, getCardName(id), getCardName(id)), m_color(getCityColor(id))
{
	std::stringstream ss;
	ss << std::hex << id;
	m_cityID = ss.str();
}

const char* EpidemicCard::getCardDesc(const uint64_t& id)
{
	const char* desc = "";
	switch (id)
	{
	case EpidemicCard::EPIDEMICCARDONE:
	case EpidemicCard::EPIDEMICCARDTWO:
	case EpidemicCard::EPIDEMICCARDTHREE:
	case EpidemicCard::EPIDEMICCARDFOUR: desc = "A. Increase infection rate -- B. Infect last card of infection deck with 3 cubes -- C. Suffle discarded infection cards and readded to the top of the deck"; break;
	}
	return desc;
}

const char * RoleCard::getCardDesc(const uint64_t & id)
{
	const char* desc = "";
	switch (id)
	{
	case RoleCard::CONTIGENCY: desc = "The Contingency Planner may, as an action, take an Event card from anywhere in the Player Discard Pile and place it on his Role card.Only 1 Event card can be on his role card at a time.It does not count against his hand limit. When the Contingency Planner plays the Event card on his role card, remove this Event card from the game(instead of discarding it)."; break;
	case RoleCard::DISPATCHER: desc = "The Dispatcher may, as an action, either: A. move any pawn, if its owner agrees, to any city containing another pawn, or B.move another player’s pawn, if its owner agrees, as if it were his own. NOTE: When moving a player’s pawn as if it were your own, discard cards for Direct and Charter Flights from your hand.A card discarded for a Charter Flight must match the city the pawn is moving from."; break;
	case RoleCard::MEDIC: desc = "The Medic removes all cubes, not 1, of the same color when doing the Treat Disease action. If a disease has been cured, he automatically removes all cubes of that color from a city, simply by entering it or being there.This does not take an action. NOTE: The Medic’s automatic removal of cubes can occur on other players’ turns, if he is moved by the Dispatcher or the Airlift Event. The Medic also prevents placing disease cubes (and outbreaks) of cured diseases in his location."; break;
	case RoleCard::OPERATIONS: desc = "The Operations Expert may, as an action, either: A. build a research station in his current city without discarding(or using) a City card, or B. once per turn, move from a research station to any city by discarding any City card. NOTE: The Dispatcher may not use the Operations Expert’s special move ability when moving the Operation Expert’s pawn"; break;
	case RoleCard::QUARANTINE: desc = "The Quarantine Specialist prevents both outbreaks and the placement of disease cubes in the city she is in and all cities connected to that city.She does not affect cubes placed during setup."; break;
	case RoleCard::RESEARCHER: desc = "As an action, the Researcher may give any City card from her hand to another player in the same city as her, without this card having to match her city.The transfer must be from her hand to the other player’s hand, but it can occur on either player’s turn."; break; 
	case RoleCard::SCIENTIST: desc = "The Scientist needs only 4 (not 5) City cards of the same disease color to Discover a Cure for that disease."; break;
	}
	return desc;
}
