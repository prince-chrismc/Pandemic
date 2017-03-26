#include <cstdlib> //printf
#include <ios> //std::hex
#include <sstream> //std::stringstream
#include "Cards.h"

uint64_t Card::GetNumID()
{
	std::stringstream ss;
	ss << m_ID;
	uint64_t num = 0;
	ss >> std::hex >> num;
	return num;
}

Card::Card(const uint64_t& id, const char* name, const char* desc) : m_Name(name), m_Description(desc)
{
	std::stringstream ss;
	ss << std::hex << id;
	m_ID = ss.str();
}

void Card::PrintInformation()
{
	printf("ID: %s \t Name: %s \t Desc: %s\n", m_ID.c_str(), m_Name.c_str(), m_Description.c_str());
}

// In here lies very bad OOP but all definitions are public so for convience this is an easy out
const char* Card::GetCardName(const uint64_t& id)
{
	const char* name = "";
	switch (id)
	{
	case Card::CARD_INVALID:
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
	case ReferenceCard::REFERENCECARD_MIN:
	case ReferenceCard::REFERENCECARD_MAX:
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
	case Card::CARD_MAX:
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

const char* CityCard::GetCardDesc(const uint64_t & id)
{
	const char* desc = "";
	switch (id)
	{
	case CityCard::ALGIERS: desc = "The city of Algiers"; break;
	case CityCard::ATLANTA: desc = "The city of Atlanta"; break;
	case CityCard::BAGHDAD: desc = "The city of Baghdad"; break;
	case CityCard::BANGKOK: desc = "The city of Bangkok"; break;
	case CityCard::BEIJING: desc = "The city of Beijing"; break;
	case CityCard::BOGOTA: desc = "The city of Bogota"; break;
	case CityCard::BUENOSAIRES: desc = "The city of Buenos Aires"; break;
	case CityCard::CAIRO: desc = "The city of Cairo"; break;
	case CityCard::CHENNAI: desc = "The city of Chennai"; break;
	case CityCard::CHICAGO: desc = "The city of Chicago"; break;
	case CityCard::DELHI: desc = "The city of Delhi"; break;
	case CityCard::ESSEN: desc = "The city of Essen"; break;
	case CityCard::HOCHIMINH: desc = "The city of Ho Chi Minh"; break;
	case CityCard::HONGKONG: desc = "The city of Hong Kong"; break;
	case CityCard::ISTANBUL: desc = "The city of Istanbul"; break;
	case CityCard::JAKARTA: desc = "The city of Jakarta"; break;
	case CityCard::JOHANNESBURG: desc = "The city of Johannesburg"; break;
	case CityCard::KARACHI: desc = "The city of Karachi"; break;
	case CityCard::KHARTOUM: desc = "The city of Khartoum"; break;
	case CityCard::KINSHASA: desc = "The city of Kinshasa"; break;
	case CityCard::KOLKATA: desc = "The city of Kolkata"; break;
	case CityCard::LAGOS: desc = "Lagos"; break;
	case CityCard::LIMA: desc = "The city of Lima"; break;
	case CityCard::LONDON: desc = "The city of London"; break;
	case CityCard::LOSANGELES: desc = "The city of Los Angeles"; break;
	case CityCard::MADRID: desc = "The city of Madrid"; break;
	case CityCard::MANILA: desc = "The city of Manila"; break;
	case CityCard::MEXICO: desc = "The city of Mexico"; break;
	case CityCard::MIAMI: desc = "The city of Miami"; break;
	case CityCard::MILAN: desc = "The city of Milan"; break;
	case CityCard::MONTREAL: desc = "The city of Montreal"; break;
	case CityCard::MOSCOW: desc = "The city of Moscow"; break;
	case CityCard::MUMBAI: desc = "The city of Mumbai"; break;
	case CityCard::NEWYORK: desc = "The city of NewYork"; break;
	case CityCard::OSAKA: desc = "The city of Osaka"; break;
	case CityCard::PARIS: desc = "The city of Paris"; break;
	case CityCard::RIYADH: desc = "The city of Riyadh"; break;
	case CityCard::SANFRAN: desc = "The city of San Francisco"; break;
	case CityCard::SANTIAGO: desc = "The city of Santiago"; break;
	case CityCard::SAOPAULO: desc = "The city of Sao Paulo"; break;
	case CityCard::SEOUL: desc = "The city of Seoul"; break;
	case CityCard::SHANGHAI: desc = "The city of Shanghai"; break;
	case CityCard::STPETER: desc = "The city of St Petersburg"; break;
	case CityCard::SYDNEY: desc = "The city of Sydney"; break;
	case CityCard::TAIPEI: desc = "The city of Taipei"; break;
	case CityCard::TEHRAN: desc = "The city of Tehran"; break;
	case CityCard::TOKYO: desc = "The city of Tokyo"; break;
	case CityCard::WASHINGTON: desc = "The city of Washington"; break;
	}
	return desc;
}

Color CityCard::GetCityColor()
{
	uint64_t id = GetNumID();
	if (IsaRedCity(id)) return RED;
	else if (IsaYellowCity(id)) return YELLOW;
	else if (IsaBlueCity(id)) return BLUE;
	else if (IsaBlackCity(id)) return BLACK;
	else return INVALID;
}

const char* EventCard::GetCardDesc(const uint64_t& id)
{
	const char* desc = "";
	switch (id)
	{
	case EventCard::RESILLIENT: desc = "Remove a discarded infection card"; break;
	case EventCard::AIRLIFT: desc = "Move any pawn to any city; ask permission if neccessary"; break;
	case EventCard::FORECAST: desc = "Look at the top 6 cards of the infection deck and put them in any order you choose then put them back on top of the infection deck"; break;
	case EventCard::QUIETNIGHT: desc = "Skip the next infection phase"; break;
	case EventCard::GOVTGRANT: desc = "build a research station in any city"; break;
	}
	return desc;
}

const char* EpidemicCard::GetCardDesc(const uint64_t& id)
{
	const char* desc = "";
	switch (id)
	{
	case EpidemicCard::EPIDEMICCARDONE:
	case EpidemicCard::EPIDEMICCARDTWO:
	case EpidemicCard::EPIDEMICCARDTHREE:
	case EpidemicCard::EPIDEMICCARDFOUR:
	case EpidemicCard::EPIDEMICCARDFIVE:
	case EpidemicCard::EPIDEMICCARDSIX:
		desc = "A. Increase infection rate -- B. Infect last card of infection deck with 3 cubes -- C. Suffle discarded infection cards and readded to the top of the deck"; break;
	}
	return desc;
}

const char* RoleCard::GetCardDesc(const uint64_t & id)
{
	const char* desc = "";
	switch (id)
	{
	case RoleCard::CONTIGENCY: desc = "The Contingency Planner may, as an action, may take an Event card from anywhere in the Player Discard Pile and place it on his Role card. Only 1 Event card can be on his role card at a time. It does not count against his hand limit. When the Contingency Planner plays the Event card on his role card, remove this Event card from the game (instead of discarding it)."; break;
	case RoleCard::DISPATCHER: desc = "The Dispatcher may, as an action, either: A. move any pawn, if its owner agrees, to any city containing another pawn, or B.move another player’s pawn, if its owner agrees, as if it were his own. NOTE: When moving a player’s pawn as if it were your own, discard cards for Direct and Charter Flights from your hand.A card discarded for a Charter Flight must match the city the pawn is moving from."; break;
	case RoleCard::MEDIC: desc = "The Medic removes all cubes, not 1, of the same color when doing the Treat Disease action. If a disease has been cured, he automatically removes all cubes of that color from a city, simply by entering it or being there.This does not take an action. NOTE: The Medic’s automatic removal of cubes can occur on other players’ turns, if he is moved by the Dispatcher or the Airlift Event. The Medic also prevents placing disease cubes (and outbreaks) of cured diseases in his location."; break;
	case RoleCard::OPERATIONS: desc = "The Operations Expert may, as an action, either: A. build a research station in his current city without discarding(or using) a City card, or B. once per turn, move from a research station to any city by discarding any City card. NOTE: The Dispatcher may not use the Operations Expert’s special move ability when moving the Operation Expert’s pawn"; break;
	case RoleCard::QUARANTINE: desc = "The Quarantine Specialist prevents both outbreaks and the placement of disease cubes in the city she is in and all cities connected to that city.She does not affect cubes placed during setup."; break;
	case RoleCard::RESEARCHER: desc = "As an action, the Researcher may give any City card from her hand to another player in the same city as her, without this card having to match her city.The transfer must be from her hand to the other player’s hand, but it can occur on either player’s turn."; break;
	case RoleCard::SCIENTIST: desc = "The Scientist needs only 4 (not 5) City cards of the same disease color to Discover a Cure for that disease."; break;
	}
	return desc;
}

const char* ReferenceCard::GetCardDesc()
{
	return "\n\n --Movement Actions --\n  Drive / Ferry: Move to a city connected by a white line to the one you are in.\n Direct Flight: Discard a City card to move to the city named on the card.\n Charter Flight: Discard the City card that matches the city you are in to move to any city.\n Shuttle Flight:	Move from a city with a research station to any other city that has a research station.\n\n -- Player Actions --\n Build a Research Station: Discard the City card that matches the city you are in to place a research station there.Take the research station from the pile next to the board.If all 6 research stations have been built, take a research station from anywhere on the board.\n Treat Disease: Remove 1 disease cube from the city you are in, placing it in the cube supply next to the board.If this disease color has been cured(see Discover a Cure below), remove all cubes of that color from the city you are in. NOTE: If the last cube of a cured disease is removed from the board, this disease	is eradicated.Flip its cure marker from its “vial” side to its 'ERADICATED' side.\n Share Knowledge: You can do this action in two ways A. give the City card that matches the city you are in to another player, or B. take the City card that matches the city you are in from another player. The other player must also be in the city with you. Both of you need to agree to do this. If the player who gets the card now has more than 7 cards, that player must immediately discard a card or play an Event card\n Discover a Cure: At any research station, discard 5 City cards of the same color from your hand to cure the disease of that color. Move the disease’s cure marker to its Cure Indicator. If no cubes of this color are on the board, this disease is now eradicated. Flip its cure marker from its “vial” side to its 'ERADICATED' side.\n";
}

const char* InfectionCard::GetCardDesc(const uint64_t & id)
{
	const char* desc = "";
	switch (id)
	{
	case InfectionCard::ALGIERS: desc = "Infect the city of Algiers"; break;
	case InfectionCard::ATLANTA: desc = "Infect the city of Atlanta"; break;
	case InfectionCard::BAGHDAD: desc = "Infect the city of Baghdad"; break;
	case InfectionCard::BANGKOK: desc = "Infect the city of Bangkok"; break;
	case InfectionCard::BEIJING: desc = "Infect the city of Beijing"; break;
	case InfectionCard::BOGOTA: desc = "Infect the city of Bogota"; break;
	case InfectionCard::BUENOSAIRES: desc = "Infect the city of Buenos Aires"; break;
	case InfectionCard::CAIRO: desc = "Infect the city of Cairo"; break;
	case InfectionCard::CHENNAI: desc = "Infect the city of Chennai"; break;
	case InfectionCard::CHICAGO: desc = "Infect the city of Chicago"; break;
	case InfectionCard::DELHI: desc = "Infect the city of Delhi"; break;
	case InfectionCard::ESSEN: desc = "Infect the city of Essen"; break;
	case InfectionCard::HOCHIMINH: desc = "Infect the city of Ho Chi Minh "; break;
	case InfectionCard::HONGKONG: desc = "Infect the city of Hong Kong"; break;
	case InfectionCard::ISTANBUL: desc = "Infect the city of Istanbul"; break;
	case InfectionCard::JAKARTA: desc = "Infect the city of Jakarta"; break;
	case InfectionCard::JOHANNESBURG: desc = "Infect the city of Johannesburg"; break;
	case InfectionCard::KARACHI: desc = "Infect the city of Karachi"; break;
	case InfectionCard::KHARTOUM: desc = "Infect the city of Khartoum"; break;
	case InfectionCard::KINSHASA: desc = "Infect the city of Kinshasa"; break;
	case InfectionCard::KOLKATA: desc = "Infect the city of Kolkata"; break;
	case InfectionCard::LAGOS: desc = "Infect the city of Lagos"; break;
	case InfectionCard::LIMA: desc = "Infect the city of Lima"; break;
	case InfectionCard::LONDON: desc = "Infect the city of London"; break;
	case InfectionCard::LOSANGELES: desc = "Infect the city of Los Angeles"; break;
	case InfectionCard::MADRID: desc = "Infect the city of Madrid"; break;
	case InfectionCard::MANILA: desc = "Infect the city of Manila"; break;
	case InfectionCard::MEXICO: desc = "Infect the city of Mexico"; break;
	case InfectionCard::MIAMI: desc = "Infect the city of Miami"; break;
	case InfectionCard::MILAN: desc = "Infect the city of Milan"; break;
	case InfectionCard::MONTREAL: desc = "Infect the city of Montreal"; break;
	case InfectionCard::MOSCOW: desc = "Infect the city of Moscow"; break;
	case InfectionCard::MUMBAI: desc = "Infect the city of Mumbai"; break;
	case InfectionCard::NEWYORK: desc = "Infect the city of NewYork"; break;
	case InfectionCard::OSAKA: desc = "Infect the city of Osaka"; break;
	case InfectionCard::PARIS: desc = "Infect the city of Paris"; break;
	case InfectionCard::RIYADH: desc = "Infect the city of Riyadh"; break;
	case InfectionCard::SANFRAN: desc = "Infect the city of San Francisco"; break;
	case InfectionCard::SANTIAGO: desc = "Infect the city of Santiago"; break;
	case InfectionCard::SAOPAULO: desc = "Infect the city of Sao Paulo"; break;
	case InfectionCard::SEOUL: desc = "Infect the city of Seoul"; break;
	case InfectionCard::SHANGHAI: desc = "Infect the city of Shanghai"; break;
	case InfectionCard::STPETER: desc = "Infect the city of St Petersburg"; break;
	case InfectionCard::SYDNEY: desc = "Infect the city of Sydney"; break;
	case InfectionCard::TAIPEI: desc = "Infect the city of Taipei"; break;
	case InfectionCard::TEHRAN: desc = "Infect the city of Tehran"; break;
	case InfectionCard::TOKYO: desc = "Infect the city of Tokyo"; break;
	case InfectionCard::WASHINGTON: desc = "Infect the city of Washington"; break;
	}
	return desc;
}

Color InfectionCard::GetCityColor()
{
	uint64_t id = GetNumID();
	if (IsaRedCity(id)) return RED;
	else if (IsaYellowCity(id)) return YELLOW;
	else if (IsaBlueCity(id)) return BLUE;
	else if (IsaBlackCity(id)) return BLACK;
	else return INVALID;
}

PlayerCard* PlayerCardFactory::MakeCard(const uint64_t& id)
{
	if (IsaCityCard(id))
		return new CityCard((CityCard::CardsList)id);
	if (IsaEventCard(id))
		return new EventCard((EventCard::CardsList)id);
	if (IsaEpidemicCard(id))
		return new EpidemicCard((EpidemicCard::CardsList)id);
	else
		return nullptr;
}

bool PlayerCardFactory::IsaCityCard(const uint64_t& id)
{
	return (id > CityCard::CITYCARD_MIN) && (id < CityCard::CITYCARD_MAX);
}

bool PlayerCardFactory::IsaEventCard(const uint64_t& id)
{
	return (id > EventCard::EVENTCARD_MIN) && (id < EventCard::EVENTCARD_MAX);
}

bool PlayerCardFactory::IsaEpidemicCard(const uint64_t& id)
{
	return (id > EpidemicCard::EPIDEMICCARD_MIN) && (id < EpidemicCard::EPIDEMICCARD_MAX);
}