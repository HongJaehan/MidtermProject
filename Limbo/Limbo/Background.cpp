#include "pch.h"
#include "common.h"
#include "Background.h"

Background::Background()
	:startPosX(0),
	endPosX(0),
	imgName(TEXT(""))
{

}

Background::Background(int _startPosX, std::wstring _imgName)
	:startPosX(_startPosX),
	endPosX(_startPosX + defines.screenSizeX * 2),
	imgName(_imgName)
{
	img = AssetManager::GetInstance()->GetImage(_imgName);
}
Background::~Background()
{
	
}

void Background::Init()
{
}

void Background::Release()
{
	img.reset();
}

int Background::GetStartPosX()
{
	return startPosX;
}

int Background::GetEndPosX()
{
	return endPosX;
}

void Background::Render(Gdiplus::Graphics* MemG,int interval)
{
	int width = defines.screenSizeX;
	int height = defines.screenSizeY;

	int imgSizeX = defines.mapImgSizeX;
	int imgSizeY = defines.mapImgSizeY;

	////실제로 스크린에 뿌려줄 크기
	Gdiplus::Rect rect2(0, 0, width*2, height);
	
	//interval = interval * imgSizeX / width;
	interval = interval * imgSizeX / (width * 2);
	//MemG->DrawImage(AssetManager::GetInstance()->GetImage(imgName).lock().get(), rect2, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	if (!img.expired())
	{
		MemG->DrawImage(img.lock().get(), rect2, interval, 0, imgSizeX, imgSizeY, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}
}

void Background::RenderLeft(Gdiplus::Graphics* MemG, int sizeToDraw)
{
	int width = defines.screenSizeX;
	int height = defines.screenSizeY;

	int imgSizeX = defines.mapImgSizeX;
	int imgSizeY = defines.mapImgSizeY;

	//실제로 스크린에 뿌려줄 크기
	Gdiplus::Rect rect2(0, 0, sizeToDraw+10, height);

	sizeToDraw = (sizeToDraw*imgSizeX) / (width * 2);
	if (!img.expired())
	{
		MemG->DrawImage(img.lock().get(), rect2, imgSizeX - sizeToDraw, 0, sizeToDraw, imgSizeY, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}
}

void Background::RenderRight(Gdiplus::Graphics* MemG, int sizeToDraw)
{
	int width = defines.screenSizeX;
	int height = defines.screenSizeY;

	int imgSizeX = defines.mapImgSizeX;
	int imgSizeY = defines.mapImgSizeY;

	//실제로 스크린에 뿌려줄 크기
	Gdiplus::Rect rect2(width-sizeToDraw, 0, sizeToDraw, height);

	sizeToDraw = (sizeToDraw * imgSizeX) / (width * 2);
	if (!img.expired())
	{
		MemG->DrawImage(img.lock().get(), rect2, 0, 0, sizeToDraw, imgSizeY, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}
}
