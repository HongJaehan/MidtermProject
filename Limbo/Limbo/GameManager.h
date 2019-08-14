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
	//key : 체크 포인트 number    value: 체크포인트의 x, y 값
	std::unordered_map<int, std::pair<int, int>> checkPoint;
	int nowCheckPoint;

	//지형정보
	int mapCount;
	//Gdiplus::Graphics* TerrainGraphics;
	Gdiplus::Bitmap* terrainBitmap;

	//player 위치값 X를 저장하는 변수
	int playerPosX;
};

GameManager* GameManager::instance = nullptr;
