#include "pch.h"
#include "Niddle.h"

Niddle::Niddle()
{

}

Niddle::Niddle(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height, false);
}

Niddle::~Niddle()
{

}

void Niddle::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("collider.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	}
	enable = false;
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
}

void Niddle::Release()
{
	delete collider;
}

void Niddle::Update(float Delta)
{
}

void Niddle::Render(Gdiplus::Graphics* MemG)
{
	//int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	//Gdiplus::Rect rect(drawToScreenPosX, y, width, height);
	//MemG->DrawImage(img, rect);
}

void Niddle::Collision(Object* obj)
{
	EventManager::GetInstance()->OnEvent(eEvent_PlayerDie); 
}

bool Niddle::HasInteraction()
{
	return false;
}
