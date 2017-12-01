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

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Card Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Pandemic.h"

namespace std { typedef string hexadecimal; } //hex value (stored as a string) done for easier code reading


class Card abstract //Basic Object hold primary definition
{
private:
	std::hexadecimal m_ID;
	std::string m_Name;
	std::string m_Description;

protected:
	Card(const uint64_t& id, const char* name, const char* desc);

public:
	///EXAMPLE = 0x0A89CFCUL
	enum CardsList	//Important definition to define ranges for types and the IDs themselves
	{
		CARD_INVALID = 0x0000000UL, //Invalid
		CARD_MAX = 0xFFFFFFFUL      //Invalid
	};

	static const char* GetCardName(const uint64_t& id);
	uint64_t GetNumID();
	std::string GetCardInfo();
};


class PlayerCard abstract : public Card //One of three basic card types
{
protected:
	PlayerCard(const uint64_t& id, const char* name, const char* desc) : Card(id, name, desc) {}

public:
	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		PLAYERCARD_MIN = 0x2000000UL, //Invalid
		PLAYERCARD_MAX = 0x2FFFFFFUL, //Invalid
	};
	virtual std::string GetCardInfo() = 0;
};


class PlayerCardFactory abstract //Generates the various player cards with various support functions
{
	friend class GameEngine;
protected:
	static PlayerCard* MakeCard(const uint64_t& id);

public:
	static bool IsaCityCard(const uint64_t& id);
	static bool IsaEventCard(const uint64_t& id);
	static bool IsaEpidemicCard(const uint64_t& id);
};


class CityCard final : public PlayerCard, private CityList //One of three player card types
{
private:
	static bool IsaRedCity(const uint64_t& id) { return (id > RED_MIN) && (id < RED_MAX); }
	static bool IsaYellowCity(const uint64_t& id) { return (id > YELLOW_MIN) && (id < YELLOW_MAX); }
	static bool IsaBlueCity(const uint64_t& id) { return (id > BLUE_MIN) && (id < BLUE_MAX); }
	static bool IsaBlackCity(const uint64_t& id) { return (id > BLACK_MIN) && (id < BLACK_MAX); }
	static const char* GetCardDesc(const uint64_t& id);

public:
	///Prevent Copy/Assignment
	CityCard(const CityCard&) = delete;
	void operator=(const CityCard&) = delete;

	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		CITYCARD_MIN = 0x2400000UL,   //Invalid
		ALGIERS = CityList::ALGIERS + CITYCARD_MIN,  //Algiers
		ATLANTA = CityList::ATLANTA + CITYCARD_MIN,  //Atlanta
		BAGHDAD = CityList::BAGHDAD + CITYCARD_MIN,  //Baghdad
		BANGKOK = CityList::BANGKOK + CITYCARD_MIN,  //Bangkok
		BEIJING = CityList::BEIJING + CITYCARD_MIN,  //Beijing
		BOGOTA = CityList::BOGOTA + CITYCARD_MIN,  //Bogota
		BUENOSAIRES = CityList::BUENOSAIRES + CITYCARD_MIN,  //Buenos Aires
		CAIRO = CityList::CAIRO + CITYCARD_MIN,  //Cairo
		CHENNAI = CityList::CHENNAI + CITYCARD_MIN,  //Chennai
		CHICAGO = CityList::CHICAGO + CITYCARD_MIN,  //Chicago
		DELHI = CityList::DELHI + CITYCARD_MIN,  //Delhi
		ESSEN = CityList::ESSEN + CITYCARD_MIN,  //Essen
		HOCHIMINH = CityList::HOCHIMINH + CITYCARD_MIN,  //Ho Chi Minh City
		HONGKONG = CityList::HONGKONG + CITYCARD_MIN,  //Hong Kong
		ISTANBUL = CityList::ISTANBUL + CITYCARD_MIN,  //Istanbul
		JAKARTA = CityList::JAKARTA + CITYCARD_MIN,  //Jakarta
		JOHANNESBURG = CityList::JOHANNESBURG + CITYCARD_MIN,  //Johannesburg
		KARACHI = CityList::KARACHI + CITYCARD_MIN,  //Karachi
		KHARTOUM = CityList::KHARTOUM + CITYCARD_MIN,  //Khartoum
		KINSHASA = CityList::KINSHASA + CITYCARD_MIN,  //Kinshasa
		KOLKATA = CityList::KOLKATA + CITYCARD_MIN,  //Kolkata
		LAGOS = CityList::LAGOS + CITYCARD_MIN,  //Lagos
		LIMA = CityList::LIMA + CITYCARD_MIN,  //Lima
		LONDON = CityList::LONDON + CITYCARD_MIN,  //London
		LOSANGELES = CityList::LOSANGELES + CITYCARD_MIN,  //Los Angeles
		MADRID = CityList::MADRID + CITYCARD_MIN,  //Madrid
		MANILA = CityList::MANILA + CITYCARD_MIN,  //Manila
		MEXICO = CityList::MEXICO + CITYCARD_MIN,  //Mexico City
		MIAMI = CityList::MIAMI + CITYCARD_MIN,  //Miami
		MILAN = CityList::MILAN + CITYCARD_MIN,  //Milan
		MONTREAL = CityList::MONTREAL + CITYCARD_MIN,  //Montreal
		MOSCOW = CityList::MOSCOW + CITYCARD_MIN,  //Moscow
		MUMBAI = CityList::MUMBAI + CITYCARD_MIN,  //Mumbai
		NEWYORK = CityList::NEWYORK + CITYCARD_MIN,  //NewYork
		OSAKA = CityList::OSAKA + CITYCARD_MIN,  //Osaka
		PARIS = CityList::PARIS + CITYCARD_MIN,  //Paris
		RIYADH = CityList::RIYADH + CITYCARD_MIN,  //Riyadh
		SANFRAN = CityList::SANFRAN + CITYCARD_MIN,  //San Francisco
		SANTIAGO = CityList::SANTIAGO + CITYCARD_MIN,  //Santiago
		SAOPAULO = CityList::SAOPAULO + CITYCARD_MIN,  //Sao Paulo
		SEOUL = CityList::SEOUL + CITYCARD_MIN,  //Seoul
		SHANGHAI = CityList::SHANGHAI + CITYCARD_MIN,  //Shanghai
		STPETER = CityList::STPETER + CITYCARD_MIN,  //StPetersburg
		SYDNEY = CityList::SYDNEY + CITYCARD_MIN,  //Sydney
		TAIPEI = CityList::TAIPEI + CITYCARD_MIN,  //Taipei
		TEHRAN = CityList::TEHRAN + CITYCARD_MIN,  //Tehran
		TOKYO = CityList::TOKYO + CITYCARD_MIN,  //Tokyo
		WASHINGTON = CityList::WASHINGTON + CITYCARD_MIN,  //Washington
		RED_MIN = CityList::RED_MIN + CITYCARD_MIN,  //Invalid
		RED_MAX = CityList::RED_MAX + CITYCARD_MIN,  //Invalid
		BLACK_MIN = CityList::BLACK_MIN + CITYCARD_MIN,  //Invalid
		BLACK_MAX = CityList::BLACK_MAX + CITYCARD_MIN,  //Invalid
		BLUE_MIN = CityList::BLUE_MIN + CITYCARD_MIN,  //Invalid
		BLUE_MAX = CityList::BLUE_MAX + CITYCARD_MIN,  //Invalid
		YELLOW_MIN = CityList::YELLOW_MIN + CITYCARD_MIN,  //Invalid
		YELLOW_MAX = CityList::YELLOW_MAX + CITYCARD_MIN,  //Invalid
		CITYCARD_MAX = 0x24FFFFFUL,   //Invalid
	};

	CityCard(const CardsList& id) : PlayerCard(id, GetCardName(id), GetCardDesc(id)) {}

	Color GetCityColor();

	std::string GetCardInfo();
};


class EventCard final : public PlayerCard //Two of three player card types
{
private:
	static const char* GetCardDesc(const uint64_t& id);

public:
	///Prevent Copy/Assignment
	EventCard(const EventCard&) = delete;
	void operator=(const EventCard&) = delete;

	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EVENTCARD_MIN = 0x2800000UL,  //Invalid

		RESILLIENT = 0x2800123UL,
		AIRLIFT = 0x2800246UL,
		FORECAST = 0x2800369UL,
		QUIETNIGHT = 0x280048C,
		GOVTGRANT = 0x28006AF,

		EVENTCARD_MAX = 0x28FFFFFUL,  //Invalid
	};

	EventCard(const CardsList& id) : PlayerCard(id, GetCardName(id), GetCardDesc(id)) {}

	std::string GetCardInfo();
};


class EpidemicCard final : public PlayerCard //Three of three player card types
{
private:
	static const char* GetCardDesc(const uint64_t& id);

public:
	///Prevent Copy/Assignment
	EpidemicCard(const EpidemicCard&) = delete;
	void operator=(const EpidemicCard&) = delete;

	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		EPIDEMICCARD_MIN = 0x2B00000UL,  //Invalid
		EPIDEMICCARDONE = 0x2B00333UL,	 //Epidemic Card
		EPIDEMICCARDTWO = 0x2B00888UL,	 //Epidemic Card
		EPIDEMICCARDTHREE = 0x2B00AAAUL, //Epidemic Card
		EPIDEMICCARDFOUR = 0x2B00CCCUL,	 //Epidemic Card
		EPIDEMICCARDFIVE = 0x2B00DDDUL,	 //Epidemic Card
		EPIDEMICCARDSIX = 0x2B00EEEUL,	 //Epidemic Card
		EPIDEMICCARD_MAX = 0x2BFFFFFUL,  //Invalid
	};

	EpidemicCard(const CardsList& id) : PlayerCard(id, GetCardName(id), GetCardDesc(id)) {}

	std::string GetCardInfo();
};


class RoleCard final : public Card, public RoleList //Two of three basic card types
{
private:
	static const char* GetCardDesc(const uint64_t& id);

public:
	///Prevent Copy/Assignment
	RoleCard(const RoleCard&) = delete;
	void operator=(const RoleCard&) = delete;

	RoleCard(const Roles& id) : Card(id, GetCardName(id), GetCardDesc(id)) {}
};


class ReferenceCard final : public Card //The card explaining the base actions
{
private:
	static const char* GetCardDesc();

public:
	///Prevent Copy/Assignment
	ReferenceCard(const ReferenceCard&) = delete;
	void operator=(const ReferenceCard&) = delete;

	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		REFERENCECARD_MIN = 0xA000000UL, //Invalid
		REFERENCECARD = 0xAABCDEFUL,	 //Reference Card
		REFERENCECARD_MAX = 0xAFFFFFFUL, //Invalid
	};

	ReferenceCard() : Card(REFERENCECARD, "Reference Card", GetCardDesc()) {}
};


class InfectionCard final : public Card, private CityList //Three of three basic card types
{
private:
	CityID m_CityID;
	Color m_Color;

	static const char* GetCardDesc(const uint64_t& id);
	static bool IsaRedCity(const uint64_t& id) { return (id > RED_MIN) && (id < RED_MAX); }
	static bool IsaYellowCity(const uint64_t& id) { return (id > YELLOW_MIN) && (id < YELLOW_MAX); }
	static bool IsaBlueCity(const uint64_t& id) { return (id > BLUE_MIN) && (id < BLUE_MAX); }
	static bool IsaBlackCity(const uint64_t& id) { return (id > BLACK_MIN) && (id < BLACK_MAX); }

public:
	///Prevent Copy/Assignment
	InfectionCard(const InfectionCard&) = delete;
	void operator=(const InfectionCard&) = delete;

	///EXAMPLE = 0x0A89CFCUL
	enum CardsList
	{
		INFECTIONCARD_MIN = 0xC000000UL, //Invalid
		ALGIERS = CityList::ALGIERS + INFECTIONCARD_MIN,  //Algiers
		ATLANTA = CityList::ATLANTA + INFECTIONCARD_MIN,  //Atlanta
		BAGHDAD = CityList::BAGHDAD + INFECTIONCARD_MIN,  //Baghdad
		BANGKOK = CityList::BANGKOK + INFECTIONCARD_MIN,  //Bangkok
		BEIJING = CityList::BEIJING + INFECTIONCARD_MIN,  //Beijing
		BOGOTA = CityList::BOGOTA + INFECTIONCARD_MIN,  //Bogota
		BUENOSAIRES = CityList::BUENOSAIRES + INFECTIONCARD_MIN,  //Buenos Aires
		CAIRO = CityList::CAIRO + INFECTIONCARD_MIN,  //Cairo
		CHENNAI = CityList::CHENNAI + INFECTIONCARD_MIN,  //Chennai
		CHICAGO = CityList::CHICAGO + INFECTIONCARD_MIN,  //Chicago
		DELHI = CityList::DELHI + INFECTIONCARD_MIN,  //Delhi
		ESSEN = CityList::ESSEN + INFECTIONCARD_MIN,  //Essen
		HOCHIMINH = CityList::HOCHIMINH + INFECTIONCARD_MIN,  //Ho Chi Minh City
		HONGKONG = CityList::HONGKONG + INFECTIONCARD_MIN,  //Hong Kong
		ISTANBUL = CityList::ISTANBUL + INFECTIONCARD_MIN,  //Istanbul
		JAKARTA = CityList::JAKARTA + INFECTIONCARD_MIN,  //Jakarta
		JOHANNESBURG = CityList::JOHANNESBURG + INFECTIONCARD_MIN,  //Johannesburg
		KARACHI = CityList::KARACHI + INFECTIONCARD_MIN,  //Karachi
		KHARTOUM = CityList::KHARTOUM + INFECTIONCARD_MIN,  //Khartoum
		KINSHASA = CityList::KINSHASA + INFECTIONCARD_MIN,  //Kinshasa
		KOLKATA = CityList::KOLKATA + INFECTIONCARD_MIN,  //Kolkata
		LAGOS = CityList::LAGOS + INFECTIONCARD_MIN,  //Lagos
		LIMA = CityList::LIMA + INFECTIONCARD_MIN,  //Lima
		LONDON = CityList::LONDON + INFECTIONCARD_MIN,  //London
		LOSANGELES = CityList::LOSANGELES + INFECTIONCARD_MIN,  //Los Angeles
		MADRID = CityList::MADRID + INFECTIONCARD_MIN,  //Madrid
		MANILA = CityList::MANILA + INFECTIONCARD_MIN,  //Manila
		MEXICO = CityList::MEXICO + INFECTIONCARD_MIN,  //Mexico City
		MIAMI = CityList::MIAMI + INFECTIONCARD_MIN,  //Miami
		MILAN = CityList::MILAN + INFECTIONCARD_MIN,  //Milan
		MONTREAL = CityList::MONTREAL + INFECTIONCARD_MIN,  //Montreal
		MOSCOW = CityList::MOSCOW + INFECTIONCARD_MIN,  //Moscow
		MUMBAI = CityList::MUMBAI + INFECTIONCARD_MIN,  //Mumbai
		NEWYORK = CityList::NEWYORK + INFECTIONCARD_MIN,  //NewYork
		OSAKA = CityList::OSAKA + INFECTIONCARD_MIN,  //Osaka
		PARIS = CityList::PARIS + INFECTIONCARD_MIN,  //Paris
		RIYADH = CityList::RIYADH + INFECTIONCARD_MIN,  //Riyadh
		SANFRAN = CityList::SANFRAN + INFECTIONCARD_MIN,  //San Francisco
		SANTIAGO = CityList::SANTIAGO + INFECTIONCARD_MIN,  //Santiago
		SAOPAULO = CityList::SAOPAULO + INFECTIONCARD_MIN,  //Sao Paulo
		SEOUL = CityList::SEOUL + INFECTIONCARD_MIN,  //Seoul
		SHANGHAI = CityList::SHANGHAI + INFECTIONCARD_MIN,  //Shanghai
		STPETER = CityList::STPETER + INFECTIONCARD_MIN,  //StPetersburg
		SYDNEY = CityList::SYDNEY + INFECTIONCARD_MIN,  //Sydney
		TAIPEI = CityList::TAIPEI + INFECTIONCARD_MIN,  //Taipei
		TEHRAN = CityList::TEHRAN + INFECTIONCARD_MIN,  //Tehran
		TOKYO = CityList::TOKYO + INFECTIONCARD_MIN,  //Tokyo
		WASHINGTON = CityList::WASHINGTON + INFECTIONCARD_MIN,  //Washington
		RED_MIN = CityList::RED_MIN + INFECTIONCARD_MIN,  //Invalid
		RED_MAX = CityList::RED_MAX + INFECTIONCARD_MIN,  //Invalid
		BLACK_MIN = CityList::BLACK_MIN + INFECTIONCARD_MIN,  //Invalid
		BLACK_MAX = CityList::BLACK_MAX + INFECTIONCARD_MIN,  //Invalid
		BLUE_MIN = CityList::BLUE_MIN + INFECTIONCARD_MIN,  //Invalid
		BLUE_MAX = CityList::BLUE_MAX + INFECTIONCARD_MIN,  //Invalid
		YELLOW_MIN = CityList::YELLOW_MIN + INFECTIONCARD_MIN,  //Invalid
		YELLOW_MAX = CityList::YELLOW_MAX + INFECTIONCARD_MIN,  //Invalid
		INFECTIONCARD_MAX = 0xCFFFFFFUL, //Invalid
	};

	InfectionCard(const CardsList& id) : Card(id, GetCardName(id), GetCardDesc(id)), m_Color(GetCityColor()), m_CityID((CityID)(id - INFECTIONCARD_MIN)) {}

	Color GetCityColor();
};
