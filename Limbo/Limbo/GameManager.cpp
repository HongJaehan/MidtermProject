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


	//CheckPoint 데이타 가져오기
	AssetManager::GetInstance()->SetCheckPointData(checkPointVec, "XML\\CheckPoint.xml");

	//Object들의 XML데이터를 objectXMLDic에 저장
	AssetManager::GetInstance()->SetXMLData(objectXMLDic, "XML\\Object.xml");
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
		{
			if (nowCheckPoint < i)
			{
				nowCheckPoint = i;
			}
			//마지막 CheckPoint 도달 시 
			if (i == checkPointVec.size() - 1)
			{
				sndPlaySound(NULL, SND_ASYNC); //배경음 종료
				SceneManager::GetInstance()->MoveNextScene(); //씬 전환
			}
		}
		
	}
}

Gdiplus::Rect GameManager::GetObjectRect(EObjectNum _objNum)
{
	return objectXMLDic[_objNum];
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
	
	return y + defines.playerHeight;
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
