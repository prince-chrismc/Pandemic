#include <sstream>
#include "Observers.h"
#include "Pandemic.h"

void WorldObserver::Update()
{
	std::string alg = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::ALGIERS)->GetMapOutput();
	std::string Atl = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::ATLANTA)->GetMapOutput();
	std::string Bag = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::BAGHDAD)->GetMapOutput();
	std::string Ban = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::BANGKOK)->GetMapOutput();
	std::string Bei = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::BEIJING)->GetMapOutput();
	std::string Bog = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::BOGOTA)->GetMapOutput();
	std::string Bue = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::BUENOSAIRES)->GetMapOutput();
	std::string Cai = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::CAIRO)->GetMapOutput();
	std::string Che = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::CHENNAI)->GetMapOutput();
	std::string Chi = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::CHICAGO)->GetMapOutput();
	std::string Del = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::DELHI)->GetMapOutput();
	std::string Ess = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::ESSEN)->GetMapOutput();
	std::string HoC = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::HOCHIMINH)->GetMapOutput();
	std::string Hon = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::HONGKONG)->GetMapOutput();
	std::string Ist = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::ISTANBUL)->GetMapOutput();
	std::string Jak = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::JAKARTA)->GetMapOutput();
	std::string Joh = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::JOHANNESBURG)->GetMapOutput();
	std::string Kar = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::KARACHI)->GetMapOutput();
	std::string Kha = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::KHARTOUM)->GetMapOutput();
	std::string Kin = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::KINSHASA)->GetMapOutput();
	std::string Kol = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::KOLKATA)->GetMapOutput();
	std::string Lag = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::LAGOS)->GetMapOutput();
	std::string Lim = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::LIMA)->GetMapOutput();
	std::string Lon = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::LONDON)->GetMapOutput();
	std::string Los = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::LOSANGELES)->GetMapOutput();
	std::string Mad = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MADRID)->GetMapOutput();
	std::string Man = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MANILA)->GetMapOutput();
	std::string Mex = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MEXICO)->GetMapOutput();
	std::string Mia = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MIAMI)->GetMapOutput();
	std::string Mil = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MILAN)->GetMapOutput();
	std::string Mon = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MONTREAL)->GetMapOutput();
	std::string Mos = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MOSCOW)->GetMapOutput();
	std::string Mum = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::MUMBAI)->GetMapOutput();
	std::string New = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::NEWYORK)->GetMapOutput();
	std::string Osa = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::OSAKA)->GetMapOutput();
	std::string Par = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::PARIS)->GetMapOutput();
	std::string Riy = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::RIYADH)->GetMapOutput();
	std::string fra = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SANFRAN)->GetMapOutput();
	std::string tia = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SANTIAGO)->GetMapOutput();
	std::string Sao = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SAOPAULO)->GetMapOutput();
	std::string Seo = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SEOUL)->GetMapOutput();
	std::string Sha = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SHANGHAI)->GetMapOutput();
	std::string StP = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::STPETER)->GetMapOutput();
	std::string Syd = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::SYDNEY)->GetMapOutput();
	std::string Tai = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::TAIPEI)->GetMapOutput();
	std::string Teh = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::TEHRAN)->GetMapOutput();
	std::string Tok = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::TOKYO)->GetMapOutput();
	std::string Was = dynamic_cast<MapSubject*>(m_MapSub)->GetCityWithID(CityList::WASHINGTON)->GetMapOutput();

	std::string aa = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::ALGIERS) ? "*" : " ";
	std::string ab = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::ATLANTA) ? "*" : " ";
	std::string ac = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::BAGHDAD) ? "*" : "-";
	std::string ad = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::BANGKOK) ? "*" : " ";
	std::string ae = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::BEIJING) ? "*" : "-";
	std::string af = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::BOGOTA) ? "*" : " ";
	std::string ag = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::BUENOSAIRES) ? "*" : " ";
	std::string ah = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::CAIRO) ? "*" : "-";
	std::string ai = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::CHENNAI) ? "*" : " ";
	std::string aj = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::CHICAGO) ? "*" : " ";
	std::string ak = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::DELHI) ? "*" : "-";
	std::string al = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::ESSEN) ? "*" : " ";
	std::string am = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::HOCHIMINH) ? "*" : " ";
	std::string an = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::HONGKONG) ? "*" : " ";
	std::string ao = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::ISTANBUL) ? "*" : " ";
	std::string ap = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::JAKARTA) ? "*" : " ";
	std::string aq = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::JOHANNESBURG) ? "*" : " ";
	std::string ar = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::KARACHI) ? "*" : "-";
	std::string as = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::KHARTOUM) ? "*" : " ";
	std::string at = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::KINSHASA) ? "*" : " ";
	std::string au = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::KOLKATA) ? "*" : " ";
	std::string av = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::LAGOS) ? "*" : "_";
	std::string aw = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::LIMA) ? "*" : " ";
	std::string ax = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::LONDON) ? "*" : "-";
	std::string ay = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::LOSANGELES) ? "*" : " ";
	std::string az = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MADRID) ? "*" : " ";
	std::string ba = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MANILA) ? "*" : " ";
	std::string bb = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MEXICO) ? "*" : " ";
	std::string bc = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MIAMI) ? "*" : " ";
	std::string bd = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MILAN) ? "*" : " ";
	std::string be = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MONTREAL) ? "*" : "-";
	std::string bf = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MOSCOW) ? "*" : " ";
	std::string bg = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::MUMBAI) ? "*" : " ";
	std::string bh = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::NEWYORK) ? "*" : "_";
	std::string bi = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::OSAKA) ? "*" : " ";
	std::string bj = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::PARIS) ? "*" : " ";
	std::string bk = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::RIYADH) ? "*" : " ";
	std::string bl = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SANFRAN) ? "*" : " ";
	std::string bm = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SANTIAGO) ? "*" : " ";
	std::string bn = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SAOPAULO) ? "*" : " ";
	std::string bo = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SEOUL) ? "*" : " ";
	std::string bp = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SHANGHAI) ? "*" : " ";
	std::string bq = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::STPETER) ? "*" : " ";
	std::string br = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::SYDNEY) ? "*" : " ";
	std::string bs = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::TAIPEI) ? "*" : " ";
	std::string bt = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::TEHRAN) ? "*" : " ";
	std::string bu = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::TOKYO) ? "*" : "-";
	std::string bv = dynamic_cast<StationsSubject*>(m_StationsSub)->IsaCenterIn(CityList::WASHINGTON) ? "*" : " ";

	std::stringstream ss;
	ss << "  ----------------------------------------------------------------------------------------------------------------------------\n" <<
		"  |                                                                                                                          |\n" <<
		"  |                                                                                                                          |\n" <<
		"  |                                                         St. Petersburg" << bq << "                                                  |\n" <<
		"  |                                                          / " << StP << " \\                                                   |\n" <<
		"  |                                                         /      |     Moscow" << bf << "                                             |\n" <<
		"  |                                         ___London" << ax << "----Essen" << al << "   |   " << Mos << "                                             |\n" <<
		"  |                   _Montreal" << be << "-New York" << bh << "_/  " << Lon << " " << Ess << "  |    /    |                                               |\n" <<
		"  |         " << aj << "Chicago_/" << Mon << "  " << New << "       |   \\   /    |    |   /    Theran" << bt << "                    Biejing" << ae << "---Seoul" << bo << "     |\n" <<
		"  |          " << Chi << "      \\     /    \\         |  " << bj << "Paris--Milan" << bd << " |  /    " << Teh << "                  " << Bei << " " << Seo << "    |\n" <<
		"  |         /   | | \\      Washington" << bv << "  \\        |   /   |     \\   | /      /   |  \\                       |     /    \\      |\n" <<
		"  |-San" << bl << "Fransico| |  \\      " << Was << "    \\______Madrid" << az << "  |    Istanboul" << ao << "   /    |  Dehli" << ak << "-----Kolkata" << au << "   " << bp << "Shanghai---" << bu << "Tokyo--|\n" <<
		"  |/" << fra << "   | |   \\    /     |             " << Mad << " |    " << Ist << "   /     | " << Del << "  " << Kol << "   " << Sha << "  " << Tok << "|\n" <<
		"  |        \\    | |    Atlanta" << ab << "  |              /     \\  |   /    |   \\  /      |  /  | \\   /   |    \\      |    |      |   /|\n" <<
		"  |         \\   | |   " << Atl << "  |             /       Algeris" << aa << "   |  Baghdad" << ac << "-" << ar << "Karachi|  \\  |   |    Hong Kong" << an << "  |  Okasa" << bi << " / |\n" <<
		"  |   Los Angeles" << ay << "|          \\   |            /       " << alg << "   |" << Bag << " " << Kar << "|   \\ |   |    " << Hon << "\\  | " << Osa << " |\n" <<
		"  |  / " << Los << "  |          Miami" << bc << "          /                \\   | /      \\ /     |  |   | |   |   /    |  \\  \\ |  /    /   |\n" <<
		"  | /          \\  |        " << Mia << "        /                  Cario" << ah << "----Ryadh" << bk << "   Mumbia" << bg << " | |  Bangkok" << ad << "  |   \\  Tapie" << bs << "  /    |\n" <<
		"  |/         " << bb << "Mexico city_/  /             /                " << Cai << " " << Riy << " " << Mum << " | | " << Ban << "  |    \\" << Tai << "     |\n" <<
		"  |            " << Mex << "\\   /             /                          \\                 \\  | | /   |  \\   |     \\  |   /     /|\n" <<
		"  |              \\       \\ /             /                     ___Khartom" << as << "             Chennia" << ai << "   | HoChiMinh" << am << "  Manila" << ba << "    / |\n" <<
		"  |               \\     Bogota" << af << "         /       ______Lagos" << av << "__/  " << Kha << "            " << Che << "   | " << HoC << "  " << Man << "  /  |\n" <<
		"  |                \\   " << Bog << "       /       /    " << Lag << "     /    |                       \\  |  /          |        /   |\n" <<
		"  |                 \\ /    |   \\      /       /           \\      /     |                        Jakarta" << ap << "        |       /    |\n" <<
		"  |                Lima" << aw << "   |   " << bn << "Sao Paulo____/            Kinsenea" << at << "    |                       " << Jak << "        |      /     |\n" <<
		"  |              " << Lim << " |    " << Sao << "                 " << Kin << "    |                               \\        |     /      |\n" <<
		"  |                   |    |     /                              \\      |                                \\       |    /       |\n" <<
		"  |                   |  Beuno Aires" << ag << "                         Johannesburg" << aq << "                              \\      |   /        |\n" <<
		"  |                   |   " << Bue << "                            " << Joh << "                                  \\     |  /         |\n" <<
		"  |                Santiago" << bm << "                                                                               \\    | /          |\n" <<
		"  |                " << tia << "                                                                                Sydney" << br << "          |\n" <<
		"  |                                                                                                        " << Syd << "         |\n" <<
		"  |                                                                                                                          |\n" <<
		"  ----------------------------------------------------------------------------------------------------------------------------\n" <<
		"  * = Research Center\t\t[ red, blue, yellow, black ]\n" << "  Paris  - " << Par << "\tMilan   - " << Mil << "\n";
	std::cout << ss.str();
}