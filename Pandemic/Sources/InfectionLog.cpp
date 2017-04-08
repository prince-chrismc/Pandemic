#include <iostream>
#include <string>
#include <sstream>
#include "InfectionLog.h"

void InfectionLog::Update()
{
	if (m_Log.size() >= 10) //Such that Initial setup is skipped
	{
		std::cout << std::endl << "Infection log updated..." << std::endl;
		uint16_t i = 0;
		for (auto itor = m_Log.rbegin(); itor < (m_Log.rbegin() + 10); itor++)
		{
			std::cout << ++i << ": " << itor->first << " gained " << itor->second << " cubes." << std::endl;
		}
		std::cout << std::endl;
	}
}

std::string InfectionLog::GetSaveOutput()
{
	std::string result;
	for (auto itor = m_Log.begin(); itor != m_Log.end(); itor++)
	{
		result += itor->first + " " + std::to_string(itor->second) + "/ ";
	}
	return result;
}

void InfectionLog::InputLoadedGame(std::vector<std::pair<std::string, uint16_t>> log)
{
	m_Log = log;
}

void InfectionLog::Update(std::string name, uint16_t cubes)
{
	m_Log.emplace_back(std::make_pair(name, cubes));
	Update();
}

InfectionLog::Builder &InfectionLog::Builder::ParseLog(std::string loaded)
{
	for (uint16_t e = 0; e < 99; e += 1)
	{
		size_t slash = loaded.find("/");
		if (slash == std::string::npos) break;
		std::string entry(loaded.substr(0, slash));
		loaded = loaded.substr(slash + 2);

		size_t space = entry.find(" ");
		std::stringstream ss(entry.substr(space + 1));
		uint16_t num = 0;
		ss >> std::hex >> num;
		m_Log.emplace_back(std::make_pair(entry.substr(0, space), num));
	}

	return *this;
}
