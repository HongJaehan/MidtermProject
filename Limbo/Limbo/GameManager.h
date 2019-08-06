#pragma once
#include "Singleton.h"
class GameManager :	public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	std::pair<int, int> GetCheckPoint();

private:
	//key : üũ ����Ʈ number    value: üũ����Ʈ�� x, y ��
	std::unordered_map<int, std::pair<int, int>> checkPoint;
	int nowCheckPoint;
};

GameManager* GameManager::instance = nullptr;
