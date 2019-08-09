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

	//��������
	int mapCount;
	//Gdiplus::Graphics* TerrainGraphics;
	Gdiplus::Bitmap* terrainBitmap;
};

GameManager* GameManager::instance = nullptr;
