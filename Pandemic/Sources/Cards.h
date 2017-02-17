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
		INVALID = 0x0000000UL, //"Invalid"
		MAX = 0xFFFFFFFUL   //"Max"
	};

	Card(const CardsList& id, const char* name);
	Card(const CardsList& id, const char* name, const char* desc);

	static const char* getCardName(Card card);
	uint64_t getNumID();
	virtual void PrintInformation();
};

class PlayerCard : public Card
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		PLAYERCARD_MIN = 0x2000000UL, //"Invalid"
		PLAYERCARD_MAX = 0x2FFFFFFUL, //"Invalid"
	};
};


class CityCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		CITYCARD_MIN = 0x2400000UL,   //"Invalid"
		CITYCARD_MAX = 0x24FFFFFUL,   //"Invalid"
	};
};


class EventCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EVENTCARD_MIN = 0x2800000UL,  //"Invalid"
		EVENTCARD_MAX = 0x28FFFFFUL,  //"Invalid"
	};
};


class EpidemicCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EPEDEMICCARD_MIN = 0x2B00000UL,  //"Invalid"
		EPEDEMICCARD_MAX = 0x2BFFFFFUL,  //"Invalid"
	};
};


class RoleCard final : public PlayerCard
{
private:
	std::vector<std::string> m_abilities;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		ROLECARD_MIN = 0x2E00000UL,    //"Invalid"
		ROLECARD_MAX = 0x2EFFFFFUL,    //"Invalid"
	};
};


class ReferenceCards final : public Card
{
private:
	std::vector<std::string> m_rules;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		REFERENCECARD_MIN = 0xA000000UL, //"Invalid"
		REFERENCECARD_MAX = 0xAFFFFFFUL, //"Invalid"
	};
};

class InfectionCard final : public Card, public CityList
{
private:
	std::hexadecimal m_cityID;
	Color m_color;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INFECTIONCARD_MIN = 0xC000000UL, //"Invalid"
		//inherits all citys and limiters via CityList
		INFECTIONCARD_MAX = 0xCFFFFFFUL, //"Invalid"
	};
};
 