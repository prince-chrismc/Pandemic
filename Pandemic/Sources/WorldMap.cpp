#include <sstream>
#include "Cards.h"
#include "WorldMap.h" 

WorldMap::WorldMap()
{
	// Create Cities ------------------------------------------------------------------------------
	City* Algiers = new City(City::ALGIERS, Card::GetCardName(CityCard::ALGIERS));
	City* Atlanta = new City(City::ATLANTA, Card::GetCardName(CityCard::ATLANTA));
	City* Baghdad = new City(City::BAGHDAD, Card::GetCardName(CityCard::BAGHDAD));
	City* Bangkok = new City(City::BANGKOK, Card::GetCardName(CityCard::BANGKOK));
	City* Beijing = new City(City::BEIJING, Card::GetCardName(CityCard::BEIJING));
	City* Bogota = new City(City::BOGOTA, Card::GetCardName(CityCard::BOGOTA));
	City* BuenosAires = new City(City::BUENOSAIRES, Card::GetCardName(CityCard::BUENOSAIRES));
	City* Cairo = new City(City::CAIRO, Card::GetCardName(CityCard::CAIRO));
	City* Chennai = new City(City::CHENNAI, Card::GetCardName(CityCard::CHENNAI));
	City* Chicago = new City(City::CHICAGO, Card::GetCardName(CityCard::CHICAGO));
	City* Delhi = new City(City::DELHI, Card::GetCardName(CityCard::DELHI));
	City* Essen = new City(City::ESSEN, Card::GetCardName(CityCard::ESSEN));
	City* HoChiMinhCity = new City(City::HOCHIMINH, Card::GetCardName(CityCard::HOCHIMINH));
	City* HongKong = new City(City::HONGKONG, Card::GetCardName(CityCard::HONGKONG));
	City* Istanbul = new City(City::ISTANBUL, Card::GetCardName(CityCard::ISTANBUL));
	City* Jakarta = new City(City::JAKARTA, Card::GetCardName(CityCard::JAKARTA));
	City* Johannesburg = new City(City::JOHANNESBURG, Card::GetCardName(CityCard::JOHANNESBURG));
	City* Karachi = new City(City::KARACHI, Card::GetCardName(CityCard::KARACHI));
	City* Khartoum = new City(City::KHARTOUM, Card::GetCardName(CityCard::KHARTOUM));
	City* Kinshasa = new City(City::KINSHASA, Card::GetCardName(CityCard::KINSHASA));
	City* Kolkata = new City(City::KOLKATA, Card::GetCardName(CityCard::KOLKATA));
	City* Lagos = new City(City::LAGOS, Card::GetCardName(CityCard::LAGOS));
	City* Lima = new City(City::LIMA, Card::GetCardName(CityCard::LIMA));
	City* London = new City(City::LONDON, Card::GetCardName(CityCard::LONDON));
	City* LosAngeles = new City(City::LOSANGELES, Card::GetCardName(CityCard::LOSANGELES));
	City* Madrid = new City(City::MADRID, Card::GetCardName(CityCard::MADRID));
	City* Manila = new City(City::MANILA, Card::GetCardName(CityCard::MANILA));
	City* MexicoCity = new City(City::MEXICO, Card::GetCardName(CityCard::MEXICO));
	City* Miami = new City(City::MIAMI, Card::GetCardName(CityCard::MIAMI));
	City* Milan = new City(City::MILAN, Card::GetCardName(CityCard::MILAN));
	City* Montreal = new City(City::MONTREAL, Card::GetCardName(CityCard::MONTREAL));
	City* Moscow = new City(City::MOSCOW, Card::GetCardName(CityCard::MOSCOW));
	City* Mumbai = new City(City::MUMBAI, Card::GetCardName(CityCard::MUMBAI));
	City* NewYork = new City(City::NEWYORK, Card::GetCardName(CityCard::NEWYORK));
	City* Osaka = new City(City::OSAKA, Card::GetCardName(CityCard::OSAKA));
	City* Paris = new City(City::PARIS, Card::GetCardName(CityCard::PARIS));
	City* Riyadh = new City(City::RIYADH, Card::GetCardName(CityCard::RIYADH));
	City* SanFrancisco = new City(City::SANFRAN, Card::GetCardName(CityCard::SANFRAN));
	City* Santiago = new City(City::SANTIAGO, Card::GetCardName(CityCard::SANTIAGO));
	City* SaoPaulo = new City(City::SAOPAULO, Card::GetCardName(CityCard::SAOPAULO));
	City* Seoul = new City(City::SEOUL, Card::GetCardName(CityCard::SEOUL));
	City* Shanghai = new City(City::SHANGHAI, Card::GetCardName(CityCard::SHANGHAI));
	City* StPetersburg = new City(City::STPETER, Card::GetCardName(CityCard::STPETER));
	City* Sydney = new City(City::SYDNEY, Card::GetCardName(CityCard::SYDNEY));
	City* Taipei = new City(City::TAIPEI, Card::GetCardName(CityCard::TAIPEI));
	City* Tehran = new City(City::TEHRAN, Card::GetCardName(CityCard::TEHRAN));
	City* Tokyo = new City(City::TOKYO, Card::GetCardName(CityCard::TOKYO));
	City* Washington = new City(City::WASHINGTON, Card::GetCardName(CityCard::WASHINGTON));

	Algiers->AddNearByCity(Madrid);
	Algiers->AddNearByCity(Paris);
	Algiers->AddNearByCity(Istanbul);
	Algiers->AddNearByCity(Cairo);

	Atlanta->AddNearByCity(Chicago);
	Atlanta->AddNearByCity(Washington);
	Atlanta->AddNearByCity(Miami);

	Baghdad->AddNearByCity(Istanbul);
	Baghdad->AddNearByCity(Tehran);
	Baghdad->AddNearByCity(Karachi);
	Baghdad->AddNearByCity(Riyadh);
	Baghdad->AddNearByCity(Cairo);

	Bangkok->AddNearByCity(Kolkata);
	Bangkok->AddNearByCity(HongKong);
	Bangkok->AddNearByCity(HoChiMinhCity);
	Bangkok->AddNearByCity(Jakarta);
	Bangkok->AddNearByCity(Chennai);

	Beijing->AddNearByCity(Seoul);
	Beijing->AddNearByCity(Shanghai);

	Bogota->AddNearByCity(Miami);
	Bogota->AddNearByCity(SaoPaulo);
	Bogota->AddNearByCity(BuenosAires);
	Bogota->AddNearByCity(Lima);
	Bogota->AddNearByCity(MexicoCity);

	BuenosAires->AddNearByCity(Bogota);
	BuenosAires->AddNearByCity(SaoPaulo);

	Cairo->AddNearByCity(Istanbul);
	Cairo->AddNearByCity(Baghdad);
	Cairo->AddNearByCity(Riyadh);
	Cairo->AddNearByCity(Khartoum);
	Cairo->AddNearByCity(Algiers);

	Chennai->AddNearByCity(Delhi);
	Chennai->AddNearByCity(Kolkata);
	Chennai->AddNearByCity(Bangkok);
	Chennai->AddNearByCity(Jakarta);
	Chennai->AddNearByCity(Mumbai);

	Chicago->AddNearByCity(Montreal);
	Chicago->AddNearByCity(Atlanta);
	Chicago->AddNearByCity(MexicoCity);
	Chicago->AddNearByCity(LosAngeles);
	Chicago->AddNearByCity(SanFrancisco);

	Delhi->AddNearByCity(Kolkata);
	Delhi->AddNearByCity(Chennai);
	Delhi->AddNearByCity(Mumbai);
	Delhi->AddNearByCity(Karachi);
	Delhi->AddNearByCity(Tehran);

	Essen->AddNearByCity(StPetersburg);
	Essen->AddNearByCity(Milan);
	Essen->AddNearByCity(Paris);
	Essen->AddNearByCity(London);

	HoChiMinhCity->AddNearByCity(HongKong);
	HoChiMinhCity->AddNearByCity(Manila);
	HoChiMinhCity->AddNearByCity(Jakarta);
	HoChiMinhCity->AddNearByCity(Bangkok);

	HongKong->AddNearByCity(Shanghai);
	HongKong->AddNearByCity(Taipei);
	HongKong->AddNearByCity(Manila);
	HongKong->AddNearByCity(HoChiMinhCity);
	HongKong->AddNearByCity(Bangkok);
	HongKong->AddNearByCity(Kolkata);

	Istanbul->AddNearByCity(StPetersburg);
	Istanbul->AddNearByCity(Moscow);
	Istanbul->AddNearByCity(Baghdad);
	Istanbul->AddNearByCity(Cairo);
	Istanbul->AddNearByCity(Algiers);
	Istanbul->AddNearByCity(Milan);

	Jakarta->AddNearByCity(Bangkok);
	Jakarta->AddNearByCity(HoChiMinhCity);
	Jakarta->AddNearByCity(Sydney);
	Jakarta->AddNearByCity(Chennai);

	Johannesburg->AddNearByCity(Khartoum);
	Johannesburg->AddNearByCity(Kinshasa);

	Karachi->AddNearByCity(Tehran);
	Karachi->AddNearByCity(Delhi);
	Karachi->AddNearByCity(Mumbai);
	Karachi->AddNearByCity(Riyadh);
	Karachi->AddNearByCity(Baghdad);

	Khartoum->AddNearByCity(Cairo);
	Khartoum->AddNearByCity(Johannesburg);
	Khartoum->AddNearByCity(Kinshasa);
	Khartoum->AddNearByCity(Lagos);

	Kinshasa->AddNearByCity(Khartoum);
	Kinshasa->AddNearByCity(Johannesburg);
	Kinshasa->AddNearByCity(Lagos);

	Kolkata->AddNearByCity(HongKong);
	Kolkata->AddNearByCity(Bangkok);
	Kolkata->AddNearByCity(Chennai);
	Kolkata->AddNearByCity(Delhi);

	Lagos->AddNearByCity(Khartoum);
	Lagos->AddNearByCity(Kinshasa);
	Lagos->AddNearByCity(SaoPaulo);

	Lima->AddNearByCity(Bogota);
	Lima->AddNearByCity(Santiago);
	Lima->AddNearByCity(MexicoCity);

	London->AddNearByCity(Essen);
	London->AddNearByCity(Paris);
	London->AddNearByCity(Madrid);
	London->AddNearByCity(NewYork);

	LosAngeles->AddNearByCity(SanFrancisco);
	LosAngeles->AddNearByCity(Chicago);
	LosAngeles->AddNearByCity(MexicoCity);
	LosAngeles->AddNearByCity(Sydney);

	Madrid->AddNearByCity(London);
	Madrid->AddNearByCity(Paris);
	Madrid->AddNearByCity(Algiers);
	Madrid->AddNearByCity(SaoPaulo);

	Manila->AddNearByCity(Taipei);
	Manila->AddNearByCity(SanFrancisco);
	Manila->AddNearByCity(Sydney);
	Manila->AddNearByCity(HoChiMinhCity);

	MexicoCity->AddNearByCity(Chicago);
	MexicoCity->AddNearByCity(Miami);
	MexicoCity->AddNearByCity(Bogota);
	MexicoCity->AddNearByCity(Lima);
	MexicoCity->AddNearByCity(LosAngeles);

	Miami->AddNearByCity(Washington);
	Miami->AddNearByCity(Bogota);
	Miami->AddNearByCity(MexicoCity);
	Miami->AddNearByCity(Atlanta);

	Milan->AddNearByCity(Istanbul);
	Milan->AddNearByCity(Paris);
	Milan->AddNearByCity(Essen);

	Montreal->AddNearByCity(NewYork);
	Montreal->AddNearByCity(Washington);
	Montreal->AddNearByCity(Chicago);

	Moscow->AddNearByCity(Tehran);
	Moscow->AddNearByCity(Istanbul);
	Moscow->AddNearByCity(StPetersburg);

	Mumbai->AddNearByCity(Karachi);
	Mumbai->AddNearByCity(Delhi);
	Mumbai->AddNearByCity(Chennai);

	NewYork->AddNearByCity(London);
	NewYork->AddNearByCity(Madrid);
	NewYork->AddNearByCity(Washington);
	NewYork->AddNearByCity(Montreal);

	Osaka->AddNearByCity(Tokyo);
	Osaka->AddNearByCity(Taipei);

	Paris->AddNearByCity(Essen);
	Paris->AddNearByCity(Milan);
	Paris->AddNearByCity(Algiers);
	Paris->AddNearByCity(Madrid);
	Paris->AddNearByCity(London);

	Riyadh->AddNearByCity(Baghdad);
	Riyadh->AddNearByCity(Karachi);
	Riyadh->AddNearByCity(Cairo);

	SanFrancisco->AddNearByCity(Chicago);
	SanFrancisco->AddNearByCity(LosAngeles);
	SanFrancisco->AddNearByCity(Manila);
	SanFrancisco->AddNearByCity(Tokyo);

	Santiago->AddNearByCity(Lima);

	SaoPaulo->AddNearByCity(Madrid);
	SaoPaulo->AddNearByCity(Lagos);
	SaoPaulo->AddNearByCity(BuenosAires);
	SaoPaulo->AddNearByCity(Bogota);

	Seoul->AddNearByCity(Tokyo);
	Seoul->AddNearByCity(Shanghai);
	Seoul->AddNearByCity(Beijing);

	Shanghai->AddNearByCity(Beijing);
	Shanghai->AddNearByCity(Seoul);
	Shanghai->AddNearByCity(Tokyo);
	Shanghai->AddNearByCity(Taipei);
	Shanghai->AddNearByCity(HongKong);

	StPetersburg->AddNearByCity(Moscow);
	StPetersburg->AddNearByCity(Istanbul);
	StPetersburg->AddNearByCity(Essen);

	Sydney->AddNearByCity(Manila);
	Sydney->AddNearByCity(LosAngeles);
	Sydney->AddNearByCity(Jakarta);

	Taipei->AddNearByCity(Osaka);
	Taipei->AddNearByCity(Manila);
	Taipei->AddNearByCity(HongKong);
	Taipei->AddNearByCity(Shanghai);

	Tehran->AddNearByCity(Delhi);
	Tehran->AddNearByCity(Karachi);
	Tehran->AddNearByCity(Baghdad);
	Tehran->AddNearByCity(Moscow);

	Tokyo->AddNearByCity(SanFrancisco);
	Tokyo->AddNearByCity(Osaka);
	Tokyo->AddNearByCity(Shanghai);
	Tokyo->AddNearByCity(Seoul);

	Washington->AddNearByCity(NewYork);
	Washington->AddNearByCity(Miami);
	Washington->AddNearByCity(Atlanta);
	Washington->AddNearByCity(Montreal);

	m_Cities[0] = Algiers;
	m_Cities[1] = Atlanta;
	m_Cities[2] = Baghdad;
	m_Cities[3] = Bangkok;
	m_Cities[4] = Beijing;
	m_Cities[5] = Bogota;
	m_Cities[6] = BuenosAires;
	m_Cities[7] = Cairo;
	m_Cities[8] = Chennai;
	m_Cities[9] = Chicago;
	m_Cities[10] = Delhi;
	m_Cities[11] = Essen;
	m_Cities[12] = HoChiMinhCity;
	m_Cities[13] = HongKong;
	m_Cities[14] = Istanbul;
	m_Cities[15] = Jakarta;
	m_Cities[16] = Johannesburg;
	m_Cities[17] = Karachi;
	m_Cities[18] = Khartoum;
	m_Cities[19] = Kinshasa;
	m_Cities[20] = Kolkata;
	m_Cities[21] = Lagos;
	m_Cities[22] = Lima;
	m_Cities[23] = London;
	m_Cities[24] = LosAngeles;
	m_Cities[25] = Madrid;
	m_Cities[26] = Manila;
	m_Cities[27] = MexicoCity;
	m_Cities[28] = Miami;
	m_Cities[29] = Milan;
	m_Cities[30] = Montreal;
	m_Cities[31] = Moscow;
	m_Cities[32] = Mumbai;
	m_Cities[33] = NewYork;
	m_Cities[34] = Osaka;
	m_Cities[35] = Paris;
	m_Cities[36] = Riyadh;
	m_Cities[37] = SanFrancisco;
	m_Cities[38] = Santiago;
	m_Cities[39] = SaoPaulo;
	m_Cities[40] = Seoul;
	m_Cities[41] = Shanghai;
	m_Cities[42] = StPetersburg;
	m_Cities[43] = Sydney;
	m_Cities[44] = Taipei;
	m_Cities[45] = Tehran;
	m_Cities[46] = Tokyo;
	m_Cities[47] = Washington;
}

WorldMap::~WorldMap()
{
	for (int i = 0; i < 48; i += 1)
	{
		delete m_Cities[i];
		m_Cities[i] = nullptr;
	}
}

std::vector<City*> WorldMap::GetCitiesConnectedTo(const City::CityID& id)
{
	for (int i = 0; i < 48; i += 1)
	{
		if (m_Cities[i]->CompareCityID(id))
		{
			return m_Cities[i]->GetNearByCities();
		}
	}
	std::vector<City*> result;
	return  result;
}

std::vector<City*> WorldMap::GetAllCities()
{
	std::vector<City*> all;
	for each (City* icity in m_Cities)
	{
		all.emplace_back(icity);
	}
	return all;
}

City* WorldMap::GetCityWithID(const City::CityID & id)
{
	for (int i = 0; i < 48; i += 1)
	{
		if (m_Cities[i]->CompareCityID(id))
		{
			return m_Cities[i];
		}
	}
	return nullptr;
}

std::string WorldMap::GetSaveOutput()
{
	std::stringstream ss;
	for each(City* city in m_Cities)
		ss << city->GetSaveOutput() << "/ ";
	return ss.str();
}

void WorldMap::PrintCitiesStatus()
{
	printf("\n");
	for (int i = 0; i < 48; i += 1)
	{
		m_Cities[i]->PrintInformation();
	}
}
