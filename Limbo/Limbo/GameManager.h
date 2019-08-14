#pragma once
#include "Singleton.h"

class GameManager :	public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	std::pair<int, int> GetCheckPoint();
	int GetTerrainData(int playerPosX);
	int GetPlayerPosX();
	void Func(int);

private:
	//key : üũ ����Ʈ number    value: üũ����Ʈ�� x, y ��
	std::unordered_map<int, std::pair<int, int>> checkPoint;
	int nowCheckPoint;

	//��������
	int mapCount;
	//Gdiplus::Graphics* TerrainGraphics;
	Gdiplus::Bitmap* terrainBitmap;

	//player ��ġ�� X�� �����ϴ� ����
	int playerPosX;
};

GameManager* GameManager::instance = nullptr;
