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

	collider = new BoxCollider2D(_x, _y, _width,_height, false);
}

ColliderObject::~ColliderObject()
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
