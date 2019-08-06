#pragma once
#include "Singleton.h"
class GameManager :	public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	std::pair<int, int> GetCheckPoint();

private:
	//key : 체크 포인트 number    value: 체크포인트의 x, y 값
	std::unordered_map<int, std::pair<int, int>> checkPoint;
	int nowCheckPoint;
};

GameManager* GameManager::instance = nullptr;
