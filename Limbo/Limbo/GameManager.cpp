#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	mapCount = 9;
	nowCheckPoint = 0;


	terrainBitmap = new Gdiplus::Bitmap(defines.screenSizeX * 2 * mapCount, defines.screenSizeY, PixelFormat32bppARGB);
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

	//юс╫ц
	checkPointVec.emplace_back(500);
	checkPointVec.emplace_back(2375);
	checkPointVec.emplace_back(4291);
	checkPointVec.emplace_back(7993);

	
}

GameManager::~GameManager()
{
	delete terrainBitmap;
}

void GameManager::SetPlayerPosX(int _playerPosX)
{
	playerPosX = _playerPosX;
	ConfirmCheckPoint(playerPosX);
}

void GameManager::ConfirmCheckPoint(int _playerPosX)
{
	for (int i = 0; i < checkPointVec.size(); ++i)
	{
		if (_playerPosX > checkPointVec[i])
			nowCheckPoint = i;
		if (nowCheckPoint == 3)
		{
			int xxx;
		}
	}
}

int GameManager::GetTerrainData(int _playerPosX)
{
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

//void GameManager::Func(int)
//{
//	playerPosX;
//}


int GameManager::GetPlayerPosX()
{
	return playerPosX;
}

int GameManager::GetCheckPointPosX()
{
	return checkPointVec[nowCheckPoint];
}

void GameManager::Init()
{
}
