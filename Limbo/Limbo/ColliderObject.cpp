#include "pch.h"
#include "ColliderObject.h"


ColliderObject::ColliderObject()
	:img(nullptr),
	screenPosX(0),
	screenPosY(0)
{

}

ColliderObject::ColliderObject(ETag _tag, int _x, int _y, int _width, int _height)
	:img(nullptr),
	screenPosX(0),
	screenPosY(0)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height, false);
}

ColliderObject::~ColliderObject()
{

}

void ColliderObject::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("collider.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	}
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	enable = false;
}

void ColliderObject::Release()
{
	delete collider;
}

void ColliderObject::Update(float Delta)
{

}

void ColliderObject::Render(Gdiplus::Graphics* MemG)
{
	//int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	//Gdiplus::Rect rect(drawToScreenPosX,y-height*0.5f, width, height);
	//MemG->DrawImage(img, rect);
}

void ColliderObject::Collision(Object* obj)
{

}

bool ColliderObject::HasInteraction()
{
	return false;
}
