#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	mapCount = 10;
	nowCheckPoint = 0;
	terrainBitmap = new Gdiplus::Bitmap(mapCount * 2 * 1920,1080, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(terrainBitmap);
	Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3_ground.png")).lock().get();
	//Gdiplus::Rect mapRect(0,0,3920, 1080);
	graphics.DrawImage(img,0,0, 3920, 1080);
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	/*for (int i = 0; i < mapCount; ++i)
	{
		
	}*/
}

GameManager::~GameManager()
{

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