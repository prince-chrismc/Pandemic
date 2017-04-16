///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Disease Cube Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Pandemic.h"

class DiseaseCube abstract
{
private:
	Color m_Color;

public:
	DiseaseCube(const Color& color) : m_Color(color) {}
	Color GetColor() { return m_Color; }
};

class RedDiseaseCube final : public DiseaseCube { public: RedDiseaseCube() : DiseaseCube(Color::RED) {} };
class YellowDiseaseCube final : public DiseaseCube { public: YellowDiseaseCube() : DiseaseCube(Color::YELLOW) {} };
class BlueDiseaseCube final : public DiseaseCube { public: BlueDiseaseCube() : DiseaseCube(Color::BLUE) {} };
class BlackDiseaseCube final : public DiseaseCube { public: BlackDiseaseCube() : DiseaseCube(Color::BLACK) {} };

class CubePile abstract
{
protected:
	uint16_t m_CubesLeft;

public:
	CubePile() : m_CubesLeft(24) {}

	uint16_t CubesLeft() { return m_CubesLeft; }
	bool IsEmpty() { return (m_CubesLeft == 0); }
	virtual DiseaseCube* TakeCube() = 0;
	void PlaceCube(DiseaseCube* dc) { delete dc; dc = nullptr;  m_CubesLeft += 1; }
};

class RedDiseaseCubePile final : public CubePile
{
public:
	RedDiseaseCubePile() : CubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new RedDiseaseCube(); }
};

class YellowDiseaseCubePile final : public CubePile
{
public:
	YellowDiseaseCubePile() : CubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new YellowDiseaseCube(); }
};

class BlueDiseaseCubePile final : public CubePile
{
public:
	BlueDiseaseCubePile() : CubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new BlueDiseaseCube(); }
};

class BlackDiseaseCubePile final : public CubePile
{
public:
	BlackDiseaseCubePile() : CubePile() {}
	DiseaseCube* TakeCube() { if (m_CubesLeft == 0) { return nullptr; } m_CubesLeft -= 1; return new BlackDiseaseCube(); }
};

class DiseaseCubePile final
{
private:
	RedDiseaseCubePile m_Red;
	YellowDiseaseCubePile m_Yellow;
	BlueDiseaseCubePile m_Blue;
	BlackDiseaseCubePile m_Black;

public:
	DiseaseCubePile() : m_Red(), m_Yellow(), m_Blue(), m_Black() {}

	///Prevent Copy/Assignment
	DiseaseCubePile(const DiseaseCubePile&) = delete;
	void operator=(const DiseaseCubePile&) = delete;

	bool IsAnyEmpty() { return m_Red.IsEmpty() || m_Yellow.IsEmpty() || m_Blue.IsEmpty() || m_Black.IsEmpty(); }
	bool IsFull(const Color& color);
	DiseaseCube* TakeCube(const Color& color);
	const Color PlaceCube(DiseaseCube* dc);
};