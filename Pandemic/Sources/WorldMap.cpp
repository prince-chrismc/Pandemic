#include <fstream> //file io
#include <ctime> //time
#include "boost\filesystem.hpp"
#include "WorldMap.h" 

WorldMap::WorldMap() : m_infectrate(), m_outbreeak(), m_cubepiles(), m_infecdeck(), m_playerdeck(), m_roledeck(), m_players(), m_cures(), m_centers()
{
	// Create Cities ------------------------------------------------------------------------------
	City* Algiers = new City(City::ALGIERS, Card::getCardName(CityCard::ALGIERS));
	City* Atlanta = new City(City::ATLANTA, Card::getCardName(CityCard::ATLANTA));
	City* Baghdad = new City(City::BAGHDAD, Card::getCardName(CityCard::BAGHDAD));
	City* Bangkok = new City(City::BANGKOK, Card::getCardName(CityCard::BANGKOK));
	City* Beijing = new City(City::BEIJING, Card::getCardName(CityCard::BEIJING));
	City* Bogota = new City(City::BOGOTA, Card::getCardName(CityCard::BOGOTA));
	City* BuenosAires = new City(City::BUENOSAIRES, Card::getCardName(CityCard::BUENOSAIRES));
	City* Cairo = new City(City::CAIRO, Card::getCardName(CityCard::CAIRO));
	City* Chennai = new City(City::CHENNAI, Card::getCardName(CityCard::CHENNAI));
	City* Chicago = new City(City::CHICAGO, Card::getCardName(CityCard::CHICAGO));
	City* Delhi = new City(City::DELHI, Card::getCardName(CityCard::DELHI));
	City* Essen = new City(City::ESSEN, Card::getCardName(CityCard::ESSEN));
	City* HoChiMinhCity = new City(City::HOCHIMINH, Card::getCardName(CityCard::HOCHIMINH));
	City* HongKong = new City(City::HONGKONG, Card::getCardName(CityCard::HONGKONG));
	City* Istanbul = new City(City::ISTANBUL, Card::getCardName(CityCard::ISTANBUL));
	City* Jakarta = new City(City::JAKARTA, Card::getCardName(CityCard::JAKARTA));
	City* Johannesburg = new City(City::JOHANNESBURG, Card::getCardName(CityCard::JOHANNESBURG));
	City* Karachi = new City(City::KARACHI, Card::getCardName(CityCard::KARACHI));
	City* Khartoum = new City(City::KHARTOUM, Card::getCardName(CityCard::KHARTOUM));
	City* Kinshasa = new City(City::KINSHASA, Card::getCardName(CityCard::KINSHASA));
	City* Kolkata = new City(City::KOLKATA, Card::getCardName(CityCard::KOLKATA));
	City* Lagos = new City(City::LAGOS, Card::getCardName(CityCard::LAGOS));
	City* Lima = new City(City::LIMA, Card::getCardName(CityCard::LIMA));
	City* London = new City(City::LONDON, Card::getCardName(CityCard::LONDON));
	City* LosAngeles = new City(City::LOSANGELES, Card::getCardName(CityCard::LOSANGELES));
	City* Madrid = new City(City::MADRID, Card::getCardName(CityCard::MADRID));
	City* Manila = new City(City::MANILA, Card::getCardName(CityCard::MANILA));
	City* MexicoCity = new City(City::MEXICO, Card::getCardName(CityCard::MEXICO));
	City* Miami = new City(City::MIAMI, Card::getCardName(CityCard::MIAMI));
	City* Milan = new City(City::MILAN, Card::getCardName(CityCard::MILAN));
	City* Montreal = new City(City::MONTREAL, Card::getCardName(CityCard::MONTREAL));
	City* Moscow = new City(City::MOSCOW, Card::getCardName(CityCard::MOSCOW));
	City* Mumbai = new City(City::MUMBAI, Card::getCardName(CityCard::MUMBAI));
	City* NewYork = new City(City::NEWYORK, Card::getCardName(CityCard::NEWYORK));
	City* Osaka = new City(City::OSAKA, Card::getCardName(CityCard::OSAKA));
	City* Paris = new City(City::PARIS, Card::getCardName(CityCard::PARIS));
	City* Riyadh = new City(City::RIYADH, Card::getCardName(CityCard::RIYADH));
	City* SanFrancisco = new City(City::SANFRAN, Card::getCardName(CityCard::SANFRAN));
	City* Santiago = new City(City::SANTIAGO, Card::getCardName(CityCard::SANTIAGO));
	City* SaoPaulo = new City(City::SAOPAULO, Card::getCardName(CityCard::SAOPAULO));
	City* Seoul = new City(City::SEOUL, Card::getCardName(CityCard::SEOUL));
	City* Shanghai = new City(City::SHANGHAI, Card::getCardName(CityCard::SHANGHAI));
	City* StPetersburg = new City(City::STPETER, Card::getCardName(CityCard::STPETER));
	City* Sydney = new City(City::SYDNEY, Card::getCardName(CityCard::SYDNEY));
	City* Taipei = new City(City::TAIPEI, Card::getCardName(CityCard::TAIPEI));
	City* Tehran = new City(City::TEHRAN, Card::getCardName(CityCard::TEHRAN));
	City* Tokyo = new City(City::TOKYO, Card::getCardName(CityCard::TOKYO));
	City* Washington = new City(City::WASHINGTON, Card::getCardName(CityCard::WASHINGTON));

	Algiers->addNearByCity(Madrid);
	Algiers->addNearByCity(Paris);
	Algiers->addNearByCity(Istanbul);
	Algiers->addNearByCity(Cairo);

	Atlanta->addNearByCity(Chicago);
	Atlanta->addNearByCity(Washington);
	Atlanta->addNearByCity(Miami);

	Baghdad->addNearByCity(Istanbul);
	Baghdad->addNearByCity(Tehran);
	Baghdad->addNearByCity(Karachi);
	Baghdad->addNearByCity(Riyadh);
	Baghdad->addNearByCity(Cairo);

	Bangkok->addNearByCity(Kolkata);
	Bangkok->addNearByCity(HongKong);
	Bangkok->addNearByCity(HoChiMinhCity);
	Bangkok->addNearByCity(Jakarta);
	Bangkok->addNearByCity(Chennai);

	Beijing->addNearByCity(Seoul);
	Beijing->addNearByCity(Shanghai);

	Bogota->addNearByCity(Miami);
	Bogota->addNearByCity(SaoPaulo);
	Bogota->addNearByCity(BuenosAires);
	Bogota->addNearByCity(Lima);
	Bogota->addNearByCity(MexicoCity);

	BuenosAires->addNearByCity(Bogota);
	BuenosAires->addNearByCity(SaoPaulo);

	Cairo->addNearByCity(Istanbul);
	Cairo->addNearByCity(Baghdad);
	Cairo->addNearByCity(Riyadh);
	Cairo->addNearByCity(Khartoum);
	Cairo->addNearByCity(Algiers);

	Chennai->addNearByCity(Delhi);
	Chennai->addNearByCity(Kolkata);
	Chennai->addNearByCity(Bangkok);
	Chennai->addNearByCity(Jakarta);
	Chennai->addNearByCity(Mumbai);

	Chicago->addNearByCity(Montreal);
	Chicago->addNearByCity(Atlanta);
	Chicago->addNearByCity(MexicoCity);
	Chicago->addNearByCity(LosAngeles);
	Chicago->addNearByCity(SanFrancisco);

	Delhi->addNearByCity(Kolkata);
	Delhi->addNearByCity(Chennai);
	Delhi->addNearByCity(Mumbai);
	Delhi->addNearByCity(Karachi);
	Delhi->addNearByCity(Tehran);

	Essen->addNearByCity(StPetersburg);
	Essen->addNearByCity(Milan);
	Essen->addNearByCity(Paris);
	Essen->addNearByCity(London);

	HoChiMinhCity->addNearByCity(HongKong);
	HoChiMinhCity->addNearByCity(Manila);
	HoChiMinhCity->addNearByCity(Jakarta);
	HoChiMinhCity->addNearByCity(Bangkok);

	HongKong->addNearByCity(Shanghai);
	HongKong->addNearByCity(Taipei);
	HongKong->addNearByCity(Manila);
	HongKong->addNearByCity(HoChiMinhCity);
	HongKong->addNearByCity(Bangkok);
	HongKong->addNearByCity(Kolkata);

	Istanbul->addNearByCity(StPetersburg);
	Istanbul->addNearByCity(Moscow);
	Istanbul->addNearByCity(Baghdad);
	Istanbul->addNearByCity(Cairo);
	Istanbul->addNearByCity(Algiers);
	Istanbul->addNearByCity(Milan);

	Jakarta->addNearByCity(Bangkok);
	Jakarta->addNearByCity(HoChiMinhCity);
	Jakarta->addNearByCity(Sydney);
	Jakarta->addNearByCity(Chennai);

	Johannesburg->addNearByCity(Khartoum);
	Johannesburg->addNearByCity(Kinshasa);

	Karachi->addNearByCity(Tehran);
	Karachi->addNearByCity(Delhi);
	Karachi->addNearByCity(Mumbai);
	Karachi->addNearByCity(Riyadh);
	Karachi->addNearByCity(Baghdad);

	Khartoum->addNearByCity(Cairo);
	Khartoum->addNearByCity(Johannesburg);
	Khartoum->addNearByCity(Kinshasa);
	Khartoum->addNearByCity(Lagos);

	Kinshasa->addNearByCity(Khartoum);
	Kinshasa->addNearByCity(Johannesburg);
	Kinshasa->addNearByCity(Lagos);

	Kolkata->addNearByCity(HongKong);
	Kolkata->addNearByCity(Bangkok);
	Kolkata->addNearByCity(Chennai);
	Kolkata->addNearByCity(Delhi);

	Lagos->addNearByCity(Khartoum);
	Lagos->addNearByCity(Kinshasa);
	Lagos->addNearByCity(SaoPaulo);

	Lima->addNearByCity(Bogota);
	Lima->addNearByCity(Santiago);
	Lima->addNearByCity(MexicoCity);

	London->addNearByCity(Essen);
	London->addNearByCity(Paris);
	London->addNearByCity(Madrid);
	London->addNearByCity(NewYork);

	LosAngeles->addNearByCity(SanFrancisco);
	LosAngeles->addNearByCity(Chicago);
	LosAngeles->addNearByCity(MexicoCity);
	LosAngeles->addNearByCity(Sydney);

	Madrid->addNearByCity(London);
	Madrid->addNearByCity(Paris);
	Madrid->addNearByCity(Algiers);
	Madrid->addNearByCity(SaoPaulo);

	Manila->addNearByCity(Taipei);
	Manila->addNearByCity(SanFrancisco);
	Manila->addNearByCity(Sydney);
	Manila->addNearByCity(HoChiMinhCity);

	MexicoCity->addNearByCity(Chicago);
	MexicoCity->addNearByCity(Miami);
	MexicoCity->addNearByCity(Bogota);
	MexicoCity->addNearByCity(Lima);
	MexicoCity->addNearByCity(LosAngeles);

	Miami->addNearByCity(Washington);
	Miami->addNearByCity(Bogota);
	Miami->addNearByCity(MexicoCity);
	Miami->addNearByCity(Atlanta);

	Milan->addNearByCity(Istanbul);
	Milan->addNearByCity(Paris);
	Milan->addNearByCity(Essen);

	Montreal->addNearByCity(NewYork);
	Montreal->addNearByCity(Washington);
	Montreal->addNearByCity(Chicago);

	Moscow->addNearByCity(Tehran);
	Moscow->addNearByCity(Istanbul);
	Moscow->addNearByCity(StPetersburg);

	Mumbai->addNearByCity(Karachi);
	Mumbai->addNearByCity(Delhi);
	Mumbai->addNearByCity(Chennai);

	NewYork->addNearByCity(London);
	NewYork->addNearByCity(Madrid);
	NewYork->addNearByCity(Washington);
	NewYork->addNearByCity(Montreal);

	Osaka->addNearByCity(Tokyo);
	Osaka->addNearByCity(Taipei);

	Paris->addNearByCity(Essen);
	Paris->addNearByCity(Milan);
	Paris->addNearByCity(Algiers);
	Paris->addNearByCity(Madrid);
	Paris->addNearByCity(London);

	Riyadh->addNearByCity(Baghdad);
	Riyadh->addNearByCity(Karachi);
	Riyadh->addNearByCity(Cairo);

	SanFrancisco->addNearByCity(Chicago);
	SanFrancisco->addNearByCity(LosAngeles);
	SanFrancisco->addNearByCity(Manila);
	SanFrancisco->addNearByCity(Tokyo);

	Santiago->addNearByCity(Lima);

	SaoPaulo->addNearByCity(Madrid);
	SaoPaulo->addNearByCity(Lagos);
	SaoPaulo->addNearByCity(BuenosAires);
	SaoPaulo->addNearByCity(Bogota);

	Seoul->addNearByCity(Tokyo);
	Seoul->addNearByCity(Shanghai);
	Seoul->addNearByCity(Beijing);

	Shanghai->addNearByCity(Beijing);
	Shanghai->addNearByCity(Seoul);
	Shanghai->addNearByCity(Tokyo);
	Shanghai->addNearByCity(Taipei);
	Shanghai->addNearByCity(HongKong);
	
	StPetersburg->addNearByCity(Moscow);
	StPetersburg->addNearByCity(Istanbul);
	StPetersburg->addNearByCity(Essen);

	Sydney->addNearByCity(Manila);
	Sydney->addNearByCity(LosAngeles);
	Sydney->addNearByCity(Jakarta);

	Taipei->addNearByCity(Osaka);
	Taipei->addNearByCity(Manila);
	Taipei->addNearByCity(HongKong);
	Taipei->addNearByCity(Shanghai);

	Tehran->addNearByCity(Delhi);
	Tehran->addNearByCity(Karachi);
	Tehran->addNearByCity(Baghdad);
	Tehran->addNearByCity(Moscow);

	Tokyo->addNearByCity(SanFrancisco);
	Tokyo->addNearByCity(Osaka);
	Tokyo->addNearByCity(Shanghai);
	Tokyo->addNearByCity(Seoul);

	Washington->addNearByCity(NewYork);
	Washington->addNearByCity(Miami);
	Washington->addNearByCity(Atlanta);
	Washington->addNearByCity(Montreal);

	m_cities[0] = Algiers;
	m_cities[1] = Atlanta;
	m_cities[2] = Baghdad;
	m_cities[3] = Bangkok;
	m_cities[4] = Beijing;
	m_cities[5] = Bogota;
	m_cities[6] = BuenosAires;
	m_cities[7] = Cairo;
	m_cities[8] = Chennai;
	m_cities[9] = Chicago;
	m_cities[10] = Delhi;
	m_cities[11] = Essen;
	m_cities[12] = HoChiMinhCity;
	m_cities[13] = HongKong;
	m_cities[14] = Istanbul;
	m_cities[15] = Jakarta;
	m_cities[16] = Johannesburg;
	m_cities[17] = Karachi;
	m_cities[18] = Khartoum;
	m_cities[19] = Kinshasa;
	m_cities[20] = Kolkata;
	m_cities[21] = Lagos;
	m_cities[22] = Lima;
	m_cities[23] = London;
	m_cities[24] = LosAngeles;
	m_cities[25] = Madrid;
	m_cities[26] = Manila;
	m_cities[27] = MexicoCity;
	m_cities[28] = Miami;
	m_cities[29] = Milan;
	m_cities[30] = Montreal;
	m_cities[31] = Moscow;
	m_cities[32] = Mumbai;
	m_cities[33] = NewYork;
	m_cities[34] = Osaka;
	m_cities[35] = Paris;
	m_cities[36] = Riyadh;
	m_cities[37] = SanFrancisco;
	m_cities[38] = Santiago;
	m_cities[39] = SaoPaulo;
	m_cities[40] = Seoul;
	m_cities[41] = Shanghai;
	m_cities[42] = StPetersburg;
	m_cities[43] = Sydney;
	m_cities[44] = Taipei;
	m_cities[45] = Tehran;
	m_cities[46] = Tokyo;
	m_cities[47] = Washington;
}

WorldMap::~WorldMap()
{
	for (int i = 0; i < 48; i += 1)
	{
		delete m_cities[i];
		m_cities[i] = nullptr;
	}

	for (size_t pos = 0; pos < m_players.size(); pos += 1)
	{
		if (m_players.at(pos) != nullptr)
		{
			delete m_players.at(pos);
			m_players.at(pos) = nullptr;
		}
	}
	m_players.clear();
}

std::string WorldMap::MakeFileName()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::string filename = "bin/Pandemic-";
	filename += std::to_string(now->tm_year + 1900);
	if (now->tm_mon + 1 < 10) filename += "0";
	filename += std::to_string(now->tm_mon + 1);
	if (now->tm_mday < 10) filename += "0";
	filename += std::to_string(now->tm_mday);
	filename += "-";
	filename += std::to_string(now->tm_hour);
	filename += std::to_string(now->tm_min);
	filename += std::to_string(now->tm_sec);
	filename += ".txt";

	return filename;
}

void WorldMap::SaveGame()
{
	// Get Timestamp ------------------------------------------------------------------------------
	std::string filename = MakeFileName();

	// Create File --------------------------------------------------------------------------------
	std::ofstream myfile;
	myfile.open(filename);
	myfile << filename << "\n";

	// Infection Cards ----------------------------------------------------------------------------
	myfile << m_infecdeck.GetSaveOutput();
	myfile << "\n";

	// Player Cards -------------------------------------------------------------------------------
	myfile << m_playerdeck.GetSaveOutput();
	myfile << "\n";

	// Role Cards ---------------------------------------------------------------------------------
	myfile << m_roledeck.GetSaveOutput();
	myfile << "\n";

	// Cities -------------------------------------------------------------------------------------
	for each  (City* city in m_cities)
	{
		myfile << city->GetSaveOutput();
		myfile << "/ ";
	}
	myfile << "\n";

	// Players ------------------------------------------------------------------------------------
	for each (Player* play in m_players)
	{
		myfile << play->GetSaveOutput();
		myfile << " / ";
	}

	// Cures --------------------------------------------------------------------------------------
	myfile << m_cures.GetSaveOutput();
	myfile << "\n";

	// Cubes ---------------------------- Is done by adding them to cities -----------------------
	//myfile << m_cubepiles.PrintCubesLeft();
	//myfile << "\n";

	// Infection Rate -----------------------------------------------------------------------------
	myfile << m_infectrate.GetSaveOutput();
	myfile << "\n";

	// Outbreak Marker ----------------------------------------------------------------------------
	myfile << m_outbreeak.GetSaveOutput();
	myfile << "\n";

	myfile.close();
}

void WorldMap::LoadGame()
{
	/* TODO: Implement */
}

void WorldMap::InfectCity(const uint8_t& cubesToAdd)
{
	InfectionCard* ic = m_infecdeck.DrawCard();
	City::CityID cid = (City::CityID)(ic->getNumID() - InfectionCard::INFECTIONCARD_MIN);
	delete ic; ic = nullptr;

	for (int i = 0; i < 48; i += 1)
	{
		if (m_cities[i]->compareCityID(cid))
		{
			for (uint8_t j = 0; j < cubesToAdd; j++)
			{
				m_cities[i]->addCube(
					m_cubepiles.takeCube(
						m_cities[i]->getCityColor()
					)
				);
			}
			break;
		}
	}
}

std::vector<City*> WorldMap::getCitiesConnectedTo(const City::CityID & id)
{
	for (int i = 0; i < 48; i += 1)
	{
		if (m_cities[i]->compareCityID(id))
		{
			return m_cities[i]->getNearByCities();
		}
	}
	std::vector<City*> result;
	return  result;
}

City* WorldMap::getCityWithID(const City::CityID & id)
{
	for (int i = 0; i < 48; i += 1)
	{
		if (m_cities[i]->compareCityID(id))
		{
			return m_cities[i];
		}
	}
	return nullptr;
}

void WorldMap::printCitiesStatus()
{
	printf("\n");
	for (int i = 0; i < 48; i += 1)
	{
		m_cities[i]->PrintInformation();
	}
}
