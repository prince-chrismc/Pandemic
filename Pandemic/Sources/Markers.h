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
//  Marker Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include "Pandemic.h"

class InfectionRate final
{
private:
	uint16_t m_Position;
	const uint16_t m_Track[7] = { 2, 2, 2, 3, 3, 4, 4 };

public:
	InfectionRate() : m_Position(0) {}

	///Prevent Copy/Assignment
	InfectionRate(const InfectionRate&) = delete;
	void operator=(const InfectionRate&) = delete;

	uint16_t GetRate() { return m_Track[m_Position]; }
	void IncreaseRate() { m_Position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_Position); }
	void InputLoadedGame(const uint16_t& position) { m_Position = position; }

	class Builder final
	{
	private:
		uint16_t m_Position;

		Builder() : m_Position(0) {}

	public:
		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		static Builder& GetInstance() { static Builder builder; return builder; }
		Builder& ParseInfectionRate(std::string loaded);
		const uint16_t& GetPosition() { return m_Position; }
	};
};

class OutbreakMarker final
{
private:
	uint16_t m_Position;
	const uint16_t m_Track[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

public:
	OutbreakMarker() : m_Position(0) {}

	///Prevent Copy/Assignment
	OutbreakMarker(const OutbreakMarker&) = delete;
	void operator=(const OutbreakMarker&) = delete;

	uint16_t GetMarker() { return m_Track[m_Position]; }
	void IncreaseRate() { m_Position += 1; }
	std::string GetSaveOutput() { return std::to_string(m_Position); }
	void InputLoadedGame(const uint16_t& position) { m_Position = position; }

	class Builder final
	{
	private:
		uint16_t m_Position;

		Builder() : m_Position(0) {}

	public:
		///Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		static Builder& GetInstance() { static Builder builder; return builder; }
		Builder& ParseOutbreakMarker(std::string loaded);
		const uint16_t& GetPosition() { return m_Position; }
	};
};
