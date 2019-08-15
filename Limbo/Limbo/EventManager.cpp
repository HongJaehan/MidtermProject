#include "pch.h"
#include "EventManager.h"


EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::AddEvent(std::function<void(int)> func,EEvent _event)
{
	dicEvent[_event].emplace_back(func);
}

void EventManager::OnEvent(EEvent _event)
{
	for (auto& it : dicEvent[_event])
	{
		it(5);
	}
}