///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Card Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Pandemic.h"

namespace std { typedef string hexadecimal; } //typedef for easier reading of my code  -- should always be a string containing a hex


class Card
{
private:
	std::hexadecimal m_id;
	std::string m_name;
	std::string m_description;

protected:
	Card(const uint64_t& id, const char* name, const char* desc);

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INVALID = 0x0000000UL, //"Invalid"
		MAX = 0xFFFFFFFUL   //"Max"
	};

	Card(const CardsList& id, const char* name);
	Card(const CardsList& id, const char* name, const char* desc);

	static const char* getCardName(const uint64_t id);
	uint64_t getNumID();
	virtual void PrintInformation();
};

class PlayerCard abstract : public Card
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		PLAYERCARD_MIN = 0x2000000UL, //"Invalid"
		PLAYERCARD_MAX = 0x2FFFFFFUL, //"Invalid"
	};

protected:
	PlayerCard(const uint64_t& id, const char* name, const char* desc);
};


class CityCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		CITYCARD_MIN = 0x2400000UL,   //"Invalid"

		ALGIERS = CityList::ALGIERS + CITYCARD_MIN,
		ATLANTA = CityList::ATLANTA + CITYCARD_MIN,
		BAGHDAD = CityList::BAGHDAD + CITYCARD_MIN,
		BANGKOK = CityList::BANGKOK + CITYCARD_MIN,
		BEIJING = CityList::BEIJING + CITYCARD_MIN,
		BOGOTA = CityList::BOGOTA + CITYCARD_MIN,
		BUENOSAIRES = CityList::BUENOSAIRES + CITYCARD_MIN,
		CAIRO = CityList::CAIRO + CITYCARD_MIN,
		CHENNAI = CityList::CHENNAI + CITYCARD_MIN,
		CHICAGO = CityList::CHICAGO + CITYCARD_MIN,
		DELHI = CityList::DELHI + CITYCARD_MIN,
		ESSEN = CityList::ESSEN + CITYCARD_MIN,
		HOCHIMINH = CityList::HOCHIMINH + CITYCARD_MIN,
		HONGKONG = CityList::HONGKONG + CITYCARD_MIN,
		ISTANBUL = CityList::ISTANBUL + CITYCARD_MIN,
		JAKARTA = CityList::JAKARTA + CITYCARD_MIN,
		JOHANNESBURG = CityList::JOHANNESBURG + CITYCARD_MIN,
		KARACHI = CityList::KARACHI + CITYCARD_MIN,
		KHARTOUM = CityList::KHARTOUM + CITYCARD_MIN,
		KINSHASA = CityList::KINSHASA + CITYCARD_MIN,
		KOLKATA = CityList::KOLKATA + CITYCARD_MIN,
		LAGOS = CityList::LAGOS + CITYCARD_MIN,
		LIMA = CityList::LIMA + CITYCARD_MIN,
		LONDON = CityList::LONDON + CITYCARD_MIN,
		LOSANGELES = CityList::LOSANGELES + CITYCARD_MIN,
		MADRID = CityList::MADRID + CITYCARD_MIN,
		MANILA = CityList::MANILA + CITYCARD_MIN,
		MEXICO = CityList::MEXICO + CITYCARD_MIN,
		MIAMI = CityList::MIAMI + CITYCARD_MIN,
		MILAN = CityList::MILAN + CITYCARD_MIN,
		MONTREAL = CityList::MONTREAL + CITYCARD_MIN,
		MOSCOW = CityList::MOSCOW + CITYCARD_MIN,
		MUMBAI = CityList::MUMBAI + CITYCARD_MIN,
		NEWYORK = CityList::NEWYORK + CITYCARD_MIN,
		OSAKA = CityList::OSAKA + CITYCARD_MIN,
		PARIS = CityList::PARIS + CITYCARD_MIN,
		RIYADH = CityList::RIYADH + CITYCARD_MIN,
		SANFRAN = CityList::SANFRAN + CITYCARD_MIN,
		SANTIAGO = CityList::SANTIAGO + CITYCARD_MIN,
		SAOPAULO = CityList::SAOPAULO + CITYCARD_MIN,
		SEOUL = CityList::SEOUL + CITYCARD_MIN,
		SHANGHAI = CityList::SHANGHAI + CITYCARD_MIN,
		STPETER = CityList::STPETER + CITYCARD_MIN,
		SYDNEY = CityList::SYDNEY + CITYCARD_MIN,
		TAIPEI = CityList::TAIPEI + CITYCARD_MIN,
		TEHRAN = CityList::TEHRAN + CITYCARD_MIN,
		TOKYO = CityList::TOKYO + CITYCARD_MIN,
		WASHINGTON = CityList::WASHINGTON + CITYCARD_MIN,
		RED_MIN = CityList::RED_MIN + CITYCARD_MIN,
		RED_MAX = CityList::RED_MAX + CITYCARD_MIN,
		BLACK_MIN = CityList::BLACK_MIN + CITYCARD_MIN,
		BLACK_MAX = CityList::BLACK_MAX + CITYCARD_MIN,
		BLUE_MIN = CityList::BLUE_MIN + CITYCARD_MIN,
		BLUE_MAX = CityList::BLUE_MAX + CITYCARD_MIN,
		YELLOW_MIN = CityList::YELLOW_MIN + CITYCARD_MIN,
		YELLOW_MAX = CityList::YELLOW_MAX + CITYCARD_MIN,

		CITYCARD_MAX = 0x24FFFFFUL,   //"Invalid"
	};

	CityCard(const CardsList& id);
};


class EventCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EVENTCARD_MIN = 0x2800000UL,  //"Invalid"

		RESILLIENTPOP = 0x2800123UL,
		AIRLIFT = 0x2800246UL,
		FORECAST = 0x2800369UL,
		QUIETNIGHT = 0x280048C,
		GOVTGRANT = 0x28006AF,

		EVENTCARD_MAX = 0x28FFFFFUL,  //"Invalid"
	};

	EventCard(const CardsList& id);
	const char* getCardDesc(const uint64_t& id);
};


class EpidemicCard final : public PlayerCard
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EPIDEMICCARD_MIN = 0x2B00000UL,  //"Invalid"
		EPIDEMICCARDONE = 0x2B00555UL,
		EPIDEMICCARDTWO = 0x2B00AAAUL,
		EPIDEMICCARDTHREE = 0x2B00CCCUL,
		EPIDEMICCARDFOUR = 0x2B00EEEUL,
		EPIDEMICCARD_MAX = 0x2BFFFFFUL,  //"Invalid"
	};

	EpidemicCard(const CardsList& id);
	const char* getCardDesc(const uint64_t& id);
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

		CONTIGENCY = 0x2E01234UL,
		DISPATCHER = 0x2E02468UL,
		MEDIC = 0x2E0369CUL,
		OPERATIONS = 0x2E048D0UL,
		QUARANTINE = 0x2E05B04UL,
		RESEARCHER = 0x2E06D38UL,
		SCIENTIST = 0x2E07F6CUL,

		ROLECARD_MAX = 0x2EFFFFFUL,    //"Invalid"
	};
	const char* getCardDesc(const uint64_t& id);
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

class InfectionCard final : public Card
{
private:
	std::hexadecimal m_cityID;
	Color m_color;

public:
	//EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INFECTIONCARD_MIN = 0xC000000UL, //"Invalid"
		ALGIERS = CityList::ALGIERS + INFECTIONCARD_MIN,
		ATLANTA = CityList::ATLANTA + INFECTIONCARD_MIN,
		BAGHDAD = CityList::BAGHDAD + INFECTIONCARD_MIN,
		BANGKOK = CityList::BANGKOK + INFECTIONCARD_MIN,
		BEIJING = CityList::BEIJING + INFECTIONCARD_MIN,
		BOGOTA = CityList::BOGOTA + INFECTIONCARD_MIN,
		BUENOSAIRES = CityList::BUENOSAIRES + INFECTIONCARD_MIN,
		CAIRO = CityList::CAIRO + INFECTIONCARD_MIN,
		CHENNAI = CityList::CHENNAI + INFECTIONCARD_MIN,
		CHICAGO = CityList::CHICAGO + INFECTIONCARD_MIN,
		DELHI = CityList::DELHI + INFECTIONCARD_MIN,
		ESSEN = CityList::ESSEN + INFECTIONCARD_MIN,
		HOCHIMINH = CityList::HOCHIMINH + INFECTIONCARD_MIN,
		HONGKONG = CityList::HONGKONG + INFECTIONCARD_MIN,
		ISTANBUL = CityList::ISTANBUL + INFECTIONCARD_MIN,
		JAKARTA = CityList::JAKARTA + INFECTIONCARD_MIN,
		JOHANNESBURG = CityList::JOHANNESBURG + INFECTIONCARD_MIN,
		KARACHI = CityList::KARACHI + INFECTIONCARD_MIN,
		KHARTOUM = CityList::KHARTOUM + INFECTIONCARD_MIN,
		KINSHASA = CityList::KINSHASA + INFECTIONCARD_MIN,
		KOLKATA = CityList::KOLKATA + INFECTIONCARD_MIN,
		LAGOS = CityList::LAGOS + INFECTIONCARD_MIN,
		LIMA = CityList::LIMA + INFECTIONCARD_MIN,
		LONDON = CityList::LONDON + INFECTIONCARD_MIN,
		LOSANGELES = CityList::LOSANGELES + INFECTIONCARD_MIN,
		MADRID = CityList::MADRID + INFECTIONCARD_MIN,
		MANILA = CityList::MANILA + INFECTIONCARD_MIN,
		MEXICO = CityList::MEXICO + INFECTIONCARD_MIN,
		MIAMI = CityList::MIAMI + INFECTIONCARD_MIN,
		MILAN = CityList::MILAN + INFECTIONCARD_MIN,
		MONTREAL = CityList::MONTREAL + INFECTIONCARD_MIN,
		MOSCOW = CityList::MOSCOW + INFECTIONCARD_MIN,
		MUMBAI = CityList::MUMBAI + INFECTIONCARD_MIN,
		NEWYORK = CityList::NEWYORK + INFECTIONCARD_MIN,
		OSAKA = CityList::OSAKA + INFECTIONCARD_MIN,
		PARIS = CityList::PARIS + INFECTIONCARD_MIN,
		RIYADH = CityList::RIYADH + INFECTIONCARD_MIN,
		SANFRAN = CityList::SANFRAN + INFECTIONCARD_MIN,
		SANTIAGO = CityList::SANTIAGO + INFECTIONCARD_MIN,
		SAOPAULO = CityList::SAOPAULO + INFECTIONCARD_MIN,
		SEOUL = CityList::SEOUL + INFECTIONCARD_MIN,
		SHANGHAI = CityList::SHANGHAI + INFECTIONCARD_MIN,
		STPETER = CityList::STPETER + INFECTIONCARD_MIN,
		SYDNEY = CityList::SYDNEY + INFECTIONCARD_MIN,
		TAIPEI = CityList::TAIPEI + INFECTIONCARD_MIN,
		TEHRAN = CityList::TEHRAN + INFECTIONCARD_MIN,
		TOKYO = CityList::TOKYO + INFECTIONCARD_MIN,
		WASHINGTON = CityList::WASHINGTON + INFECTIONCARD_MIN,
		RED_MIN = CityList::RED_MIN + INFECTIONCARD_MIN,
		RED_MAX = CityList::RED_MAX + INFECTIONCARD_MIN,
		BLACK_MIN = CityList::BLACK_MIN + INFECTIONCARD_MIN,
		BLACK_MAX = CityList::BLACK_MAX + INFECTIONCARD_MIN,
		BLUE_MIN = CityList::BLUE_MIN + INFECTIONCARD_MIN,
		BLUE_MAX = CityList::BLUE_MAX + INFECTIONCARD_MIN,
		YELLOW_MIN = CityList::YELLOW_MIN + INFECTIONCARD_MIN,
		YELLOW_MAX = CityList::YELLOW_MAX + INFECTIONCARD_MIN,
		INFECTIONCARD_MAX = 0xCFFFFFFUL, //"Invalid"
	};

	InfectionCard(const CardsList& id);
};
