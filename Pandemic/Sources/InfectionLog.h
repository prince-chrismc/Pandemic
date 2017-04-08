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

	class Builder
	{
	private:
		std::vector<std::pair<std::string, uint16_t>> m_Log;

	public:
		Builder() : m_Log() {}

		Builder& ParseLog(std::string loaded);

		std::vector<std::pair<std::string, uint16_t>> GetLog() { return m_Log; }
	};
};