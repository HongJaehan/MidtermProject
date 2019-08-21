#include "pch.h"
#include "Rope.h"


Rope::Rope()
{

}

Rope::Rope(ETag _tag, int _x, int _y, int _width, int _height)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	InitPosX = x;
	InitPosY = y;
	enable = false;

	collider = new BoxCollider2D(_x, _y, _width, _height, true);
	EventManager::GetInstance()->AddEvent(std::bind(&Rope::Init, this), EEvent::eEvent_ResetGameScene);
}
Rope::~Rope()
{
}

void Rope::Update(float Delta)
{
}

void Rope::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	Gdiplus::Rect rect(drawToScreenPosX, y-height*0.5f, width, height);
	MemG->DrawImage(img, rect);
}

void Rope::Collision(Object* obj)
{
	EventManager::GetInstance()->OnEvent(EEvent::eEvent_CutRope);
}

void Rope::Init()
{
	active = false;
}

bool Rope::HasInteraction()
{
	return false;
}
