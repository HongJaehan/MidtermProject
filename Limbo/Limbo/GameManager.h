#pragma once
#include "Singleton.h"

class GameManager :	public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	int GetTerrainData(int playerPosX);
	int GetPlayerPosX();
	int GetCheckPointPosX();
	void Init();
	void SetPlayerPosX(int _playerPosX);
	void ConfirmCheckPoint(int _playerPosX);
private:
	//key : üũ ����Ʈ number    value: üũ����Ʈ�� x, y ��
	std::vector<int> checkPointVec;
	int nowCheckPoint;

	//��������
	int mapCount;
	//Gdiplus::Graphics* TerrainGraphics;
	Gdiplus::Bitmap* terrainBitmap;

	//player ��ġ�� X�� �����ϴ� ����
	int playerPosX;
};

GameManager* GameManager::instance = nullptr;
