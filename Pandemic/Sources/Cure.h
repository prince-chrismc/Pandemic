///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Cures Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include "Pandemic.h"

class Cure abstract
{
private:
	enum State { UNDISCOVERED, KNOWN, ERADICATED };

	Color m_Color;
	State m_State;

public:
	Cure(const Color& color) : m_Color(color), m_State(UNDISCOVERED) {}

	// Mutator/Accessor
	std::string GetState() { return std::to_string(m_State); }
	void SetState(const uint16_t& state) { m_State = (State)state; }

	void CureDiscover() { m_State = KNOWN; }
	void EradicateDisease() { m_State = ERADICATED; }
	bool IsCured() { return (m_State == KNOWN); }
	bool IsNotEradicated() { return (m_State != ERADICATED); }
};

class RedCure final : public Cure { public: RedCure() : Cure(Color::RED) {} };
class YellowCure final : public Cure { public: YellowCure() : Cure(Color::YELLOW) {} };
class BlueCure final : public Cure { public: BlueCure() : Cure(Color::BLUE) {} };
class BlackCure final : public Cure { public: BlackCure() : Cure(Color::BLACK) {} };

class CureMakers final
{
private:
	RedCure m_Red;
	YellowCure m_Yellow;
	BlueCure m_Blue;
	BlackCure m_Black;

public:
	CureMakers() : m_Red(), m_Yellow(), m_Blue(), m_Black() {}

	//Prevent Copy/Assignment
	CureMakers(const CureMakers&) = delete;
	void operator=(const CureMakers&) = delete;

	void CureDiscover(const Color& color);
	void EradicateDisease(const Color& color);
	bool IsCured(const Color& color);
	bool IsNotEradicated(const Color& color);
	bool IsEradicated(const Color& color) { return !IsNotEradicated(color); }
	bool IsAllCuresDiscovered() { return m_Red.IsCured() && m_Yellow.IsCured() && m_Blue.IsCured() && m_Black.IsCured(); }
	std::string GetSaveOutput() { return (m_Red.GetState() + m_Blue.GetState() + m_Yellow.GetState() + m_Black.GetState()); } //FilePrint
	void InputLoadedGame(const uint16_t& red, const uint16_t& blue, const uint16_t& yellow, const uint16_t& black) { m_Red.SetState(red); m_Blue.SetState(blue); m_Yellow.SetState(yellow); m_Black.SetState(black); }

	class Builder
	{
	private:
		uint16_t m_Red;
		uint16_t m_Yellow;
		uint16_t m_Blue;
		uint16_t m_Black;

	public:
		Builder() : m_Red(0), m_Yellow(0), m_Blue(0), m_Black(0) {}

		Builder& ParseRedCure(std::string loaded);
		Builder& ParseBlueCure(std::string loaded);
		Builder& ParseYellowCure(std::string loaded);
		Builder& ParseBlackCure(std::string loaded);

		const uint16_t& GetRedCure() { return m_Red; }
		const uint16_t& GetBlueCure() { return m_Blue; }
		const uint16_t& GetYellowCure() { return m_Yellow; }
		const uint16_t& GetBlackCure() { return m_Black; }
	};
};