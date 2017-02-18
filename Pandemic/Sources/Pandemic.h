///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>

enum Color
{
	RED,
	BLUE,
	YELLOW,
	BLACK
};

class CityList
{
public:
	enum CityID
	{
		CITYID_MIN = 0x00000UL, //Invalid

		BLUE_MIN = 0x10000UL, //Invalid
		ATLANTA = 0x10123UL, //Atlanta
		CHICAGO = 0x10246UL, //Chicago
		ESSEN = 0x10369UL, //Essen
		LONDON = 0x1048CUL, //London
		MADRID = 0x105AFUL, //Madrid
		MILAN = 0x106D2UL, //Milan
		NEWYORK = 0x107F5UL, //New York
		PARIS = 0x10918UL, //Paris
		SANFRAN = 0x10A3BUL, //San Francisco
		STPETER = 0x10B5EUL, //St Petersburg
		MONTREAL = 0x10C81UL, //Montreal
		WASHINGTON = 0x10D04UL, //Washington
		BLUE_MAX = 0x1FFFFUL, //Invalid

		YELLOW_MIN = 0x20000UL, //Invalid
		BOGOTA = 0x20123UL, //Bogota
		BUENOSAIRES = 0x20246UL, //Buenos Aires
		JOHANNESBURG = 0x20369UL, //Johannesburg
		KHARTOUM = 0x2048CUL, //Khartoum
		KINSHASA = 0x205AFUL, //Kinshasa
		LAGOS = 0x206D2UL, //Lagos
		LIMA = 0x207F5UL, //Lima
		LOSANGELES = 0x20918UL, //Los Angeles
		MEXICO = 0x20A3BUL, //Mexico City
		MIAMI = 0x20B5EUL, //Miami
		SANTIAGO = 0x20C81UL, //Santiago
		SAOPAULO = 0x20D04UL, //Sao Paulo
		YELLOW_MAX = 0x2FFFFUL, //Invalid

		BLACK_MIN = 0x30000UL, //Invalid
		ALGIERS = 0x30123UL, //Algiers
		BAGHDAD = 0x30246UL, //Baghdad
		CAIRO = 0x30369UL, //Cairo
		CHENNAI = 0x3048CUL, //Chennai
		DELHI = 0x305AFUL, //Delhi
		ISTANBUL = 0x306D2UL, //Istanbul
		KARACHI = 0x307F5UL, //Karachi
		KOLKATA = 0x30918UL, //Kolkata
		MOSCOW = 0x30A3BUL, //Moscow
		MUMBAI = 0x30B5EUL, //Mumbai
		RIYADH = 0x30C81UL, //Riyadh
		TEHRAN = 0x30D04UL, //Tehran
		BLACK_MAX = 0x3FFFFUL, //Invalid

		RED_MIN = 0x40000UL, //Invalid
		BANGKOK = 0x40123UL, //Bangkok
		BEIJING = 0x40246UL, //Beijing
		HOCHIMINH = 0x40369UL, //Ho Chi Minh City
		HONGKONG = 0x4048CUL, //Hong Kong
		JAKARTA = 0x405AFUL, //Jakarta
		MANILA = 0x406D2UL, //Manila
		OSAKA = 0x407F5UL, //Osaka
		SEOUL = 0x40918UL, //Seoul
		SHANGHAI = 0x40A3BUL, //Shanghai
		SYDNEY = 0x40B5EUL, //Sydney
		TAIPEI = 0x40C81UL, //Taipei
		TOKYO = 0x40D04UL, //Tokyo
		RED_MAX = 0x4FFFFUL, //Invalid

		CITYID_MAX = 0xFFFFFUL, //Invalid
	};

	static bool IsRedCity(const CityID& id) { return (id > RED_MIN) && (id < RED_MAX); }
	static bool IsYellowCity(const CityID& id) { return (id > YELLOW_MIN) && (id < YELLOW_MAX); }
	static bool IsBlueCity(const CityID& id) { return (id > BLUE_MIN) && (id < BLUE_MAX); }
	static bool IsBlackCity(const CityID& id) { return (id > BLACK_MIN) && (id < BLACK_MAX); }

};



class RoleList
{
public:
	//EXAMPLE = 0x0A89CFCUL
	enum Roles
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
};