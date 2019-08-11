#include "pch.h"
#include "common.h"
#include "Background.h"

Background::Background()
{

}

Background::Background(int x, std::wstring _imgName)
	:startPosX(x),
	endPosX(x + 1920),
	imgName(_imgName)
{

}
Background::~Background()
{

}

void Background::Render(Gdiplus::Graphics* MemG)
{

}