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

	//Prevent Copy/Assignment
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
		//Prevent Copy/Assignment
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

	//Prevent Copy/Assignment
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
		//Prevent Copy/Assignment
		Builder(const Builder&) = delete;
		void operator=(const Builder&) = delete;

		static Builder& GetInstance() { static Builder builder; return builder; }
		Builder& ParseOutbreakMarker(std::string loaded);
		const uint16_t& GetPosition() { return m_Position; }
	};
};
