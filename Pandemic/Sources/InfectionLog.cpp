#include <iostream>
#include <string>
#include "InfectionLog.h"

void InfectionLog::Update()
{
	std::cout << std::endl << "Infection log updated..." << std::endl;
	int i = 0;
	if (m_Log.size() >= 10)
	{
		for (auto itor = m_Log.rbegin(); itor < (m_Log.rbegin() + 10); itor++)
		{
			std::cout << ++i << ": City " << itor->first << " gained " << itor->second << " cubes." << std::endl;
		}
	}
	else
	{
		for (auto itor = m_Log.rbegin(); itor != m_Log.rend(); itor++)
		{
			std::cout << ++i << ": City " << itor->first << " gained " << itor->second << " cubes." << std::endl;
		}
	}
	std::cout << std::endl;
}

void InfectionLog::Notify(std::string name, uint16_t cubes)
{
	m_Log.emplace_back(std::make_pair(name, cubes));
	Update();
}
