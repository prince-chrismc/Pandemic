///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Infection Log Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "Observers.h"

class InfectionLog final : public IObserver
{
private:
	std::vector<std::pair<std::string, uint16_t>> m_Log;

	void Update();

public:
	InfectionLog() : IObserver(nullptr), m_Log() {}

	void Update(std::string name, uint16_t cubes);
	std::string GetSaveOutput();
	void InputLoadedGame(std::vector<std::pair<std::string, uint16_t>> log);
};