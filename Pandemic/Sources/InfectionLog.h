///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Infection Log Definition for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Observers.h"

class InfectionLog final : public IObserver
{
private:
	std::vector<std::pair<std::string, uint16_t>> m_Log;

	void Update(); // custom because a member of a class can not have a pointer to the object it is within

public:
	InfectionLog() : IObserver(nullptr), m_Log() {}

	void Update(std::string name, uint16_t cubes); // custom because a member of a class can not have a pointer to the object it is within
	std::string GetSaveOutput();
	void InputLoadedGame(std::vector<std::pair<std::string, uint16_t>> log);

	class Builder final
	{
	private:
		std::vector<std::pair<std::string, uint16_t>> m_Log;

		Builder() : m_Log() {}

	public:
		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		static Builder& GetInstance() { static Builder builder; return builder; }
		Builder& ParseLog(std::string loaded);
		std::vector<std::pair<std::string, uint16_t>> GetLog() { return m_Log; }
	};
};