///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Card Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "Pandemic.h"

namespace std { typedef string hexadecimal; } //typedef for easier reading of my code  -- should always be a string containing a hex

class Card
{
private:
	std::hexadecimal m_id;
	std::string m_name;
	std::string m_description;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000UL, //"Invalid"
		MAX = 0xFFFFFFFUL   //"Max"
	};

	Card(const CardsList& id, const char* name);
	Card(const CardsList& id, const char* name, const char* desc);
};

class PlayerCard : Card
{
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"

		PLAYERCARD_MIN = 0xA000000UL, //"Invalid"
		PLAYERCARD_MAX = 0xAFFFFFFUL, //"Invalid"

		MAX = 0xFFFFFFFUL   //"Max"
	};
};


class CityCard final : PlayerCard
{
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"

		PLAYERCARD_MIN = 0xA000000UL, //"Invalid"
		CITYCARD_MIN = 0xAA00000UL,   //"Invalid"
		CITYCARD_MAX = 0xAAFFFFFUL,   //"Invalid"
		PLAYERCARD_MAX = 0xAFFFFFFUL, //"Invalid"

		MAX = 0xFFFFFFFUL   //"Max"
	};
};


class EventCard final : PlayerCard
{
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"

		PLAYERCARD_MIN = 0xA000000UL, //"Invalid"
		EVENTCARD_MIN = 0xAB00000UL,  //"Invalid"
		EVENTCARD_MAX = 0xABFFFFFUL,  //"Invalid"
		PLAYERCARD_MAX = 0xAFFFFFFUL, //"Invalid"

		MAX = 0xFFFFFFFUL   //"Max"
	};
};


class EpidemicCard final : PlayerCard
{
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"

		PLAYERCARD_MIN = 0xA000000UL,    //"Invalid"
		EPEDEMICCARD_MIN = 0xAC00000UL,  //"Invalid"
		EPEDEMICCARD_MAX = 0xACFFFFFUL,  //"Invalid"
		PLAYERCARD_MAX = 0xAFFFFFFUL,    //"Invalid"

		MAX = 0xFFFFFFFUL   //"Max"
	};
};


class RoleCard final : PlayerCard
{
private:
	std::vector<std::string> m_abilities;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"

		PLAYERCARD_MIN = 0xA000000UL,  //"Invalid"
		ROLECARD_MIN = 0xAD00000UL,    //"Invalid"
		ROLECARD_MAX = 0xADFFFFFUL,    //"Invalid"
		PLAYERCARD_MAX = 0xAFFFFFFUL,  //"Invalid"

		MAX = 0xFFFFFFFUL   //"Max"
	};
};


class ReferenceCards final : Card
{
private:
	std::vector<std::string> m_rules;
};


class InfectionCard final : Card
{
	/*
		TODO: fill in details
	*/
};