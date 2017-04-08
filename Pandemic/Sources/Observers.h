///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Observer Interface Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

class ISubject;

class IObserver
{
private:
	ISubject* m_subject;

public:
	IObserver(ISubject* sub) : m_subject(sub) {}

	virtual void Update() = 0;
};