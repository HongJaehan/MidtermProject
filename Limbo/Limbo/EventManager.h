#pragma once
#include "Singleton.h"

class EventManager :
	public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();
	void AddEvent(std::function<void(int)> func, EEvent);
	void OnEvent(EEvent);

private:
	std::unordered_map<EEvent,std::vector<std::function<void(int)>>> dicEvent;
};

EventManager* EventManager::instance = nullptr;

