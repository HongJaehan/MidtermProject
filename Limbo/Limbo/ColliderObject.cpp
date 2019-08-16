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
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	Gdiplus::Rect rect(drawToScreenPosX,screenPosY, width, height);
	MemG->DrawImage(img, rect);
}

void ColliderObject::Collision(Object* obj)
{
	obj = dynamic_cast<Player*>(obj);
	if (obj->GetCollider() == nullptr)
	{
		return;
	}

	if (GetCollider() == nullptr)
	{
		return;
	}

	int playerLeft = obj->GetCollider()->GetX() - obj->GetCollider()->GetWidth()*0.5f;
	int playerRight = obj->GetCollider()->GetX() + obj->GetCollider()->GetWidth() * 0.5f;
	int playerTop = obj->GetCollider()->GetY() - obj->GetCollider()->GetHeight() * 0.5f;
	int playerBottom = obj->GetCollider()->GetY() + obj->GetCollider()->GetHeight() * 0.5f;

	int objLeft = collider->GetX() - width * 0.5f;
	int objRight = collider->GetX() + width * 0.5f;
	int objTop = collider->GetY() - height * 0.5f;
	int objBottom = collider->GetY() + height * 0.5f;

	if (playerLeft <= objRight && objRight - playerLeft < obj->GetWidth())
	{
		printf("obj Right = %d \n", objRight);
		printf("player Left = %d \n", playerLeft);
		printf("player posX = %d \n", obj->GetPosX());
		printf("Game M X = %d \n", GameManager::GetInstance()->GetPlayerPosX());
		obj->SetX(obj->GetPosX() + 1);
	}
	else if (playerRight >= objLeft)
	{
		printf("objTop = %d \n", objTop);
		obj->SetX(obj->GetPosX() - 1);
	}
	if (playerTop < objBottom)
	{
		//y = playerTop + height * 0.5f;
	}
	else if (playerBottom > objTop)
	{
		//y = playerBottom - height * 0.5f;
	}
}