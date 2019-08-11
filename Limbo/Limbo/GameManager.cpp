#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	//mapCount = 10;
	//nowCheckPoint = 0;
	//terrainBitmap = new Gdiplus::Bitmap(mapCount * 2 * 1920,1080, PixelFormat32bppARGB);
	//Gdiplus::Graphics graphics(terrainBitmap);
	//Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3_ground.png")).lock().get();
	//Gdiplus::Rect mapRect(0,0,3920, 1080);
	//graphics.DrawImage(img,0,0, 3920, 1080);
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	/*for (int i = 0; i < mapCount; ++i)
	{
		
	}*/
    ex = new Gdiplus::Bitmap (1920*2, 1080, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(ex);
	Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3_ground.png")).lock().get();
	Gdiplus::Rect rect(0, 0, 1920*2, 1080);

	graphics.DrawImage(img, rect);

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
	for (y = 0; y < 1080; ++y)
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