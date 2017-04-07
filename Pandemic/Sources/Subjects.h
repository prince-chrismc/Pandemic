///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Subject Interface Definitions for the Pandemic Game
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Observers.h"


class ISubject
{
protected:
	std::vector<IObserver*> m_observers;

public:
	ISubject() : m_observers() {}

	void RegistarObserver(IObserver* obv) { m_observers.emplace_back(obv); }
	virtual void Notify() { for each(IObserver* obv in m_observers) { if (obv == nullptr) continue; obv->Update(); } }
};
