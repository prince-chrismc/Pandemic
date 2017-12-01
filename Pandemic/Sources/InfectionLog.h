/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
