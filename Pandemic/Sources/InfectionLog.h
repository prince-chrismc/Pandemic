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


public:
	InfectionLog(ISubject* sub) : IObserver(sub), m_Log() {}

	///Prevent Copy/Assignment
	InfectionLog(const InfectionLog&) = delete;
	void operator=(const InfectionLog&) = delete;

	void Update();

	///Save/Load
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

class InfectionLogNotifier final : public ISubject
{
private:
	std::pair<std::string, uint16_t> m_Latest;

public:
	InfectionLogNotifier() : ISubject() {}

	///Prevent Copy/Assignment
	InfectionLogNotifier(const InfectionLogNotifier&) = delete;
	void operator=(const InfectionLogNotifier&) = delete;

	void AddLatestInfection(std::string name, uint16_t cubes);
	std::pair<std::string, uint16_t> GetLatestInfection() { return m_Latest; }
};
