#include "pch.h"
#include "Trap.h"

Trap::Trap()
{

}

Trap::Trap(ETag _tag, int _x, int _y, int _width, int _height)
{

	colImg = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	enable = false;

	collider = new BoxCollider2D(_x, _y, _width - 50, _height, false);
}

Trap::~Trap()
{

}

void Trap::Update(float Delta)
{
	animation.Update(&atlasRect, Delta, action);
	////printf("Top = %f\n", collider->GetY() - collider->GetHeight() * 0.5);
	////printf("Left = %f\n", collider->GetX() - collider->GetWidth() * 0.5);
	//
	y = GameManager::GetInstance()->GetTerrainData(x)-height*0.5f;
	//collider->SetX(x);
	//collider->SetY(y-height*0.5f);
	////printf("Top = %f\n", collider->GetY() - collider->GetHeight() * 0.5);
	////system("cls");
}

void Trap::Render(Gdiplus::Graphics* MemG)
{


	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	////Player의 크기
	//Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	
	
	Gdiplus::Rect r(0, 0, width, height);
	temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
		atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	Gdiplus::Rect rect2(drawToScreenPosX, y-height*0.5f + 10, width, height);
	MemG->DrawImage(&bm, rect2);
	Gdiplus::Rect rect(drawToScreenPosX, y, width, height);
	MemG->DrawImage(colImg, rect);
	//int drawToScreenPosX = x - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	//int drawToScreenPosY = y - height;

	////Trap은 전체사이즈가 안맞기 때문에 
	//Gdiplus::Rect rect2(drawToScreenPosX, drawToScreenPosY, width, height);
}

void Trap::Collision(Object* obj)
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

	int objLeft = collider->GetX() - collider->GetWidth() * 0.5f;
	int objRight = collider->GetX() + collider->GetWidth()* 0.5f;
	int objTop = collider->GetY() - collider->GetHeight() * 0.5f;
	int objBottom = collider->GetY() + collider->GetHeight() * 0.5f;

	if (playerBottom > objTop && (playerBottom - objTop) < 80)
	{
		action = true;
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
		return;
	}
	//if (playerBottom < objTop && playerRight > objLeft && abs(playerRight - objLeft) < obj->GetWidth())
	//{
	//
	//}
	//else if (playerBottom < objTop && playerLeft < objRight && (objRight - playerLeft) < obj->GetWidth())
	//{
	//	action = true;
	//	EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	//}
}
