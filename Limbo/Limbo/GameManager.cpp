#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	//mapCount = 10;
	//nowCheckPoint = 0;
	//terrainBitmap = new Gdiplus::Bitmap(mapCount * 2 * defines.screenSizeX,defines.screenSizeY, PixelFormat32bppARGB);
	//Gdiplus::Graphics graphics(terrainBitmap);
	//Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3_ground.png")).lock().get();
	//Gdiplus::Rect mapRect(0,0,3920, defines.screenSizeY);
	//graphics.DrawImage(img,0,0, 3920, defines.screenSizeY);
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	/*for (int i = 0; i < mapCount; ++i)
	{
		
	}*/
    ex = new Gdiplus::Bitmap (defines.screenSizeX*2, defines.screenSizeY, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(ex);
	Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map1_ground.png")).lock().get();
	Gdiplus::Rect rect(0, 0, defines.screenSizeX*2, defines.screenSizeY);
	Gdiplus::Image* img2 = AssetManager().GetInstance()->GetImage(TEXT("map2_ground.png")).lock().get();
	Gdiplus::Rect rect2(defines.screenSizeX*2, 0, defines.screenSizeX * 2, defines.screenSizeY);


	graphics.DrawImage(img, rect);
	graphics.DrawImage(img2, rect2);

	//MemG->DrawImage(&terrainBitmap, rect);
}

GameManager::~GameManager()
{

}

int GameManager::GetTerrainData(int _playerPosX)
{
	//�޾ƿ� X���� ����
	playerPosX = _playerPosX;

	Gdiplus::Color color;
	int y;
	for (y = 0; y < defines.screenSizeY; ++y)
	{
		ex->GetPixel(_playerPosX, y, &color);
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
	//checkPoint���� key�� ã���� ���
	if (it != checkPoint.end())
	{
		//�ι�° x,y ���� ������ �ִ� pair�� ��ȯ���ش�.
		return it->second;
	}
}

int GameManager::GetPlayerPosX()
{
	return playerPosX;
}