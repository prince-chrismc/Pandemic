#include "WorldMap.h"

WorldMap::WorldMap() : m_infectrate(), m_outbreeak(), m_cubepiles(), m_infecdeck(), m_playerdeck(), m_roledeck()
{
	City Algiers(City::ALGIERS, Card::getCardName(City::ALGIERS + CityCard::CITYCARD_MIN));
	City Atlanta(City::ATLANTA, Card::getCardName(City::ATLANTA + CityCard::CITYCARD_MIN));
	City Baghdad(City::BAGHDAD, Card::getCardName(City::BAGHDAD + CityCard::CITYCARD_MIN));
	City Bangkok(City::BANGKOK, Card::getCardName(City::BANGKOK + CityCard::CITYCARD_MIN));
	City Beijing(City::BEIJING, Card::getCardName(City::BEIJING + CityCard::CITYCARD_MIN));
	City Bogota(City::BOGOTA, Card::getCardName(City::BOGOTA + CityCard::CITYCARD_MIN));
	City BuenosAires(City::BUENOSAIRES, Card::getCardName(City::BUENOSAIRES + CityCard::CITYCARD_MIN));
	City Cairo(City::CAIRO, Card::getCardName(City::CAIRO + CityCard::CITYCARD_MIN));
	City Chennai(City::CHENNAI, Card::getCardName(City::CHENNAI + CityCard::CITYCARD_MIN));
	City Chicago(City::CHICAGO, Card::getCardName(City::CHICAGO + CityCard::CITYCARD_MIN));
	City Delhi(City::DELHI, Card::getCardName(City::DELHI + CityCard::CITYCARD_MIN));
	City Essen(City::ESSEN, Card::getCardName(City::ESSEN + CityCard::CITYCARD_MIN));
	City HoChiMinhCity(City::HOCHIMINH, Card::getCardName(City::HOCHIMINH + CityCard::CITYCARD_MIN));
	City HongKong(City::HONGKONG, Card::getCardName(City::HONGKONG + CityCard::CITYCARD_MIN));
	City Istanbul(City::ISTANBUL, Card::getCardName(City::ISTANBUL + CityCard::CITYCARD_MIN));
	City Jakarta(City::JAKARTA, Card::getCardName(City::JAKARTA + CityCard::CITYCARD_MIN));
	City Johannesburg(City::JOHANNESBURG, Card::getCardName(City::JOHANNESBURG + CityCard::CITYCARD_MIN));
	City Karachi(City::KARACHI, Card::getCardName(City::KARACHI + CityCard::CITYCARD_MIN));
	City Khartoum(City::KHARTOUM, Card::getCardName(City::KHARTOUM + CityCard::CITYCARD_MIN));
	City Kinshasa(City::KINSHASA, Card::getCardName(City::KINSHASA + CityCard::CITYCARD_MIN));
	City Kolkata(City::KOLKATA, Card::getCardName(City::KOLKATA + CityCard::CITYCARD_MIN));
	City Lagos(City::LAGOS, Card::getCardName(City::LAGOS + CityCard::CITYCARD_MIN));
	City Lima(City::LIMA, Card::getCardName(City::LIMA + CityCard::CITYCARD_MIN));
	City London(City::LONDON, Card::getCardName(City::LONDON + CityCard::CITYCARD_MIN));
	City LosAngeles(City::LOSANGELES, Card::getCardName(City::LOSANGELES + CityCard::CITYCARD_MIN));
	City Madrid(City::MADRID, Card::getCardName(City::MADRID + CityCard::CITYCARD_MIN));
	City Manila(City::MANILA, Card::getCardName(City::MANILA + CityCard::CITYCARD_MIN));
	City MexicoCity(City::MEXICO, Card::getCardName(City::MEXICO + CityCard::CITYCARD_MIN));
	City Miami(City::MIAMI, Card::getCardName(City::MIAMI + CityCard::CITYCARD_MIN));
	City Milan(City::MILAN, Card::getCardName(City::MILAN + CityCard::CITYCARD_MIN));
	City Montreal(City::MONTREAL, Card::getCardName(City::MONTREAL + CityCard::CITYCARD_MIN));
	City Moscow(City::MOSCOW, Card::getCardName(City::MOSCOW + CityCard::CITYCARD_MIN));
	City Mumbai(City::MUMBAI, Card::getCardName(City::MUMBAI + CityCard::CITYCARD_MIN));
	City NewYork(City::NEWYORK, Card::getCardName(City::NEWYORK + CityCard::CITYCARD_MIN));
	City Osaka(City::OSAKA, Card::getCardName(City::OSAKA + CityCard::CITYCARD_MIN));
	City Paris(City::PARIS, Card::getCardName(City::PARIS + CityCard::CITYCARD_MIN));
	City Riyadh(City::RIYADH, Card::getCardName(City::RIYADH + CityCard::CITYCARD_MIN));
	City SanFrancisco(City::SANFRAN, Card::getCardName(City::SANFRAN + CityCard::CITYCARD_MIN));
	City Santiago(City::SANTIAGO, Card::getCardName(City::SANTIAGO + CityCard::CITYCARD_MIN));
	City SaoPaulo(City::SAOPAULO, Card::getCardName(City::SAOPAULO + CityCard::CITYCARD_MIN));
	City Seoul(City::SEOUL, Card::getCardName(City::SEOUL + CityCard::CITYCARD_MIN));
	City Shanghai(City::SHANGHAI, Card::getCardName(City::SHANGHAI + CityCard::CITYCARD_MIN));
	City StPetersburg(City::STPETER, Card::getCardName(City::STPETER + CityCard::CITYCARD_MIN));
	City Sydney(City::SYDNEY, Card::getCardName(City::SYDNEY + CityCard::CITYCARD_MIN));
	City Taipei(City::TAIPEI, Card::getCardName(City::TAIPEI + CityCard::CITYCARD_MIN));
	City Tehran(City::TEHRAN, Card::getCardName(City::TEHRAN + CityCard::CITYCARD_MIN));
	City Tokyo(City::TOKYO, Card::getCardName(City::TOKYO + CityCard::CITYCARD_MIN));
	City Washington(City::WASHINGTON, Card::getCardName(City::WASHINGTON + CityCard::CITYCARD_MIN));

	Algiers.addNearByCity(&Madrid);
	Algiers.addNearByCity(&Paris);
	Algiers.addNearByCity(&Istanbul);
	Algiers.addNearByCity(&Cairo);

	Atlanta.addNearByCity(&Chicago);
	Atlanta.addNearByCity(&Washington);
	Atlanta.addNearByCity(&Miami);

	Baghdad.addNearByCity(&Istanbul);
	Baghdad.addNearByCity(&Tehran);
	Baghdad.addNearByCity(&Karachi);
	Baghdad.addNearByCity(&Riyadh);
	Baghdad.addNearByCity(&Cairo);

	Bangkok.addNearByCity(&Kolkata);
	Bangkok.addNearByCity(&HongKong);
	Bangkok.addNearByCity(&HoChiMinhCity);
	Bangkok.addNearByCity(&Jakarta);
	Bangkok.addNearByCity(&Chennai);

	Beijing.addNearByCity(&Seoul);
	Beijing.addNearByCity(&Shanghai);

	Bogota.addNearByCity(&Miami);
	Bogota.addNearByCity(&SaoPaulo);
	Bogota.addNearByCity(&BuenosAires);
	Bogota.addNearByCity(&Lima);
	Bogota.addNearByCity(&MexicoCity);

	BuenosAires.addNearByCity(&Bogota);
	BuenosAires.addNearByCity(&SaoPaulo);

	Cairo.addNearByCity(&Istanbul);
	Cairo.addNearByCity(&Baghdad);
	Cairo.addNearByCity(&Riyadh);
	Cairo.addNearByCity(&Khartoum);
	Cairo.addNearByCity(&Algiers);

	Chennai.addNearByCity(&Delhi);
	Chennai.addNearByCity(&Kolkata);
	Chennai.addNearByCity(&Bangkok);
	Chennai.addNearByCity(&Jakarta);
	Chennai.addNearByCity(&Mumbai);

	Chicago.addNearByCity(&Montreal);
	Chicago.addNearByCity(&Atlanta);
	Chicago.addNearByCity(&MexicoCity);
	Chicago.addNearByCity(&LosAngeles);
	Chicago.addNearByCity(&SanFrancisco);
}
