#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	mapCount = 9;
	nowCheckPoint = 0;


    terrainBitmap = new Gdiplus::Bitmap (defines.screenSizeX*2*mapCount, defines.screenSizeY, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(terrainBitmap);
	

	int x = 0;
	for (int i = 1; i <= mapCount; ++i)
	{
		Gdiplus::Rect rect(x, 0, defines.screenSizeX * 2, defines.screenSizeY);
		std::wstring filePath = TEXT("\\Map\\map");
		filePath.append(std::to_wstring(i));
		filePath.append(TEXT("_Terrain.png"));
		Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(filePath).lock().get();
		graphics.DrawImage(img, rect);
		x += defines.screenSizeX * 2;
	}
	EventManager::GetInstance()->AddEvent(std::bind(&GameManager::Func, this,std::placeholders::_1),EEvent::eEvent_PlayerDie);
	
}

GameManager::~GameManager()
{
	delete terrainBitmap;
}

int GameManager::GetTerrainData(int _playerPosX)
{
	//받아온 X값을 저장
	playerPosX = _playerPosX;;
	Gdiplus::Color color;
	int y;
	for (y = 0; y < defines.screenSizeY; ++y)
	{
		terrainBitmap->GetPixel(_playerPosX, y, &color);
		if (color.GetAlpha() > 0)
		{
			return y;
			break;
		}
	}
	
	return y;
}

std::pair<int, int> GameManager::GetCheckPoint()
{
	auto& it = checkPoint.find(nowCheckPoint);
	//checkPoint에서 key를 찾았을 경우
	if (it != checkPoint.end())
	{
		//두번째 x,y 값을 가지고 있는 pair을 반환해준다.
		return it->second;
	}
}

void GameManager::Func(int)
{
	playerPosX;
}
int GameManager::GetPlayerPosX()
{
	return playerPosX;
}