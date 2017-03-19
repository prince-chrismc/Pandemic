///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Infection Log Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>

class InfectionLog final
{
private:
	std::vector<std::pair<std::string, uint16_t>> m_Log;

	void Update();

public:
	InfectionLog() : m_Log() {}

	void Notify(std::string name, uint16_t cubes = 1);
	std::string GetSaveOutput();
	void InputLoadedGame(std::vector<std::pair<std::string, uint16_t>> log);
};