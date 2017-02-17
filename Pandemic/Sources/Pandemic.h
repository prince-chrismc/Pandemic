///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

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
		CITYID_MIN = 0xC000000UL, //Invalid

		BLUE_MIN = 0xC100000UL, //Invalid
		ATLANTA = 0xC100123UL, //Atlanta
		CHICAGO = 0xC100246UL, //Chicago
		ESSEN = 0xC100369UL, //Essen
		LONDON = 0xC10048CUL, //London
		MADRID = 0xC1005AFUL, //Madrid
		MILAN = 0xC1006D2UL, //Milan
		NEWYORK = 0xC1007F5UL, //New York
		PARIS = 0xC100918UL, //Paris
		SANFRAN = 0xC100A3BUL, //San Francisco
		STPETER = 0xC100B5EUL, //St Petersburg
		MONTREAL = 0xC100C81UL, //Montreal
		WASHINGTON = 0xC100D04UL, //Washington
		BLUE_MAX = 0xC1FFFFFUL, //Invalid

		YELLOW_MIN = 0xC200000UL, //Invalid
		BOGOTA = 0xC200123UL, //Bogota
		BUENOSAIRES = 0xC200246UL, //Buenos Aires
		JOHANNESBURG = 0xC200369UL, //Johannesburg
		KHARTOUM = 0xC20048CUL, //Khartoum
		KINSHASA = 0xC2005AFUL, //Kinshasa
		LAGOS = 0xC2006D2UL, //Lagos
		LIMA = 0xC2007F5UL, //Lima
		LOSANGELES = 0xC200918UL, //Los Angeles
		MEXICO = 0xC200A3BUL, //Mexico City
		MIAMI = 0xC200B5EUL, //Miami
		SANTIAGO = 0xC200C81UL, //Santiago
		SAOPAULO = 0xC200D04UL, //Sao Paulo
		YELLOW_MAX = 0xC2FFFFFUL, //Invalid

		BLACK_MIN = 0xC300000UL, //Invalid
		ALGIERS = 0xC300123UL, //Algiers
		BAGHDAD = 0xC300246UL, //Baghdad
		CAIRO = 0xC300369UL, //Cairo
		CHENNAI = 0xC30048CUL, //Chennai
		DELHI = 0xC3005AFUL, //Delhi
		ISTANBUL = 0xC3006D2UL, //Istanbul
		KARACHI = 0xC3007F5UL, //Karachi
		KOLKATA = 0xC300918UL, //Kolkata
		MOSCOW = 0xC300A3BUL, //Moscow
		MUMBAI = 0xC300B5EUL, //Mumbai
		RIYADH = 0xC300C81UL, //Riyadh
		TEHRAN = 0xC300D04UL, //Tehran
		BLACK_MAX = 0xC3FFFFFUL, //Invalid

		RED_MIN = 0xC400000UL, //Invalid
		BANGKOK = 0xC400123UL, //Bangkok
		BEIJING = 0xC400246UL, //Beijing
		HOCHIMINH = 0xC400369UL, //Ho Chi Minh City
		HONGKONG = 0xC40048CUL, //Hong Kong
		JAKARTA = 0xC4005AFUL, //Jakarta
		MANILA = 0xC4006D2UL, //Manila
		OSAKA = 0xC4007F5UL, //Osaka
		SEOUL = 0xC400918UL, //Seoul
		SHANGHAI = 0xC400A3BUL, //Shanghai
		SYDNEY = 0xC400B5EUL, //Sydney
		TAIPEI = 0xC400C81UL, //Taipei
		TOKYO = 0xC400D04UL, //Tokyo
		RED_MAX = 0xC4FFFFFUL, //Invalid

		CITYID_MAX = 0xCFFFFFFUL, //Invalid
	};
};
