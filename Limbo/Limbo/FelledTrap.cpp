#include "pch.h"
#include "FelledTrap.h"

FelledTrap::FelledTrap()
{
}

FelledTrap::FelledTrap(ETag _tag, int _x, int _y, int _width, int _height)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eFallTrap));
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	initPosX = x;
	initPosY = y;
	maxY = GameManager::GetInstance()->GetTerrainData(x);
	enable = false;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);

	EventManager::GetInstance()->AddEvent(std::bind(&FelledTrap::Init, this), EEvent::eEvent_ResetGameScene);
}

FelledTrap::~FelledTrap()
{
}

void FelledTrap::Update(float Delta)
{
	if (active)
	{
		Down(Delta);
	}
	collider->SetY(y);
}

void FelledTrap::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(img, rect,
		xmlRect->X, xmlRect->Y, xmlRect->Width, xmlRect->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	int drawToScreenPosX = (x - width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);

	Gdiplus::Rect rect2(drawToScreenPosX, y - (height * 0.5f), width, height);
	MemG->DrawImage(&bm, rect2);
}

void FelledTrap::Collision(Object* obj)
{
	if (tag != eTag_Collider)
	{
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	}
}

void FelledTrap::Down(float Delta)
{
	if (y + (height * 0.5f) < maxY)
	{
		y += Delta * 400;
	}
	else
	{
		tag = eTag_Collider;
	}
}

void FelledTrap::OnTrap()
{
	active = true;
}

void FelledTrap::Init()
{
	x = initPosX;
	y = initPosY;
	active = false;
	tag = eTag_FallenTrap;
}

bool FelledTrap::HasInteraction()
{
	return false;
}