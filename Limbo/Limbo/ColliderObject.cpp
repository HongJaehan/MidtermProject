#include "pch.h"
#include "ColliderObject.h"


ColliderObject::ColliderObject()
{

}

ColliderObject::ColliderObject(ETag _tag, int _x, int _y, int _width, int _height)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
 	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	enable = false;
}

ColliderObject::~ColliderObject()
{

}

void ColliderObject::Update(float Delta)
{

}

void ColliderObject::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	Gdiplus::Rect rect(drawToScreenPosX, y-height*0.5f, width, height);
	MemG->DrawImage(img, rect);
}

bool ColliderObject::GetEnable()
{
	return enable;
}

void ColliderObject::SetEnable(bool bFlag)
{
	enable = bFlag;
}

int ColliderObject::GetPosX()
{
	return x;
}

int ColliderObject::GetPosY()
{
	return y;
}

int ColliderObject::GetWidth()
{
	return width;
}

int ColliderObject::GetHeight()
{
	return height;
}

ETag ColliderObject::GetTag()
{
	return tag;
}