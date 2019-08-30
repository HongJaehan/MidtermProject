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

		if (!AssetManager().GetInstance()->GetImage(filePath).expired())
		{
			Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(filePath).lock().get();
			graphics.DrawImage(img, rect);
		}
		x += defines.screenSizeX * 2;
	}

	//CheckPoint 데이타 가져오기
	AssetManager::GetInstance()->SetCheckPointData(checkPointVec, "XML\\CheckPoint.xml");

	//Object들의 XML데이터를 objectXMLDic에 저장
	AssetManager::GetInstance()->SetXMLData(objectXMLDic, "XML\\Object.xml");
	//게임 종료 이벤트 등록
	EventManager::GetInstance()->AddEvent(std::bind(&GameManager::ExitGame, this), EEvent::eEvent_ExitGame);


}

GameManager::~GameManager()
{
	delete terrainBitmap;
}

//Singleton으로 만든 Manager들은 생성 순서 떄문에 Init()을 사용해 주지 않았음.
void GameManager::Init()
{
}

void GameManager::SetPlayerPosX(int _playerPosX)
{
	playerPosX = _playerPosX;
	ConfirmCheckPoint(playerPosX);
}

void GameManager::ConfirmCheckPoint(int _playerPosX)
{
	for (size_t i = 0; i < checkPointVec.size(); ++i)
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


int GameManager::GetPlayerPosX()
{
	return playerPosX;
}

int GameManager::GetCheckPointPosX()
{
	return checkPointVec[nowCheckPoint];
}

void GameManager::ExitGame()
{

	SceneManager::GetInstance()->Release();
	AssetManager::GetInstance()->Release();
	SoundManager::GetInstance()->Release();
	EventManager::GetInstance()->Release();
	ExitProcess(0);	
}
