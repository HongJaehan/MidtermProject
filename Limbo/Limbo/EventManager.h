#pragma once
#include "Singleton.h"

class EventManager :
	public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();
	//이벤트를 추가한다
	void AddEvent(std::function<void()> func, EEvent);
	//이벤트가 발생 시 등록된 모든 함수 수행
	void OnEvent(EEvent);

private:
	//이벤트(Key)에 따라 실행할 함수를 저장할 Map 
	std::unordered_map<EEvent,std::vector<std::function<void()>>> dicEvent;
};

EventManager* EventManager::instance = nullptr;

