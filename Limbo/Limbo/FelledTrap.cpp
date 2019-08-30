#include "pch.h"
#include "FelledTrap.h"

#define DOWN_FORCE 400
FelledTrap::FelledTrap()
{
}

FelledTrap::FelledTrap(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height - 60, false);
}

FelledTrap::~FelledTrap()
{

}

void FelledTrap::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("Object.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	}
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eFallTrap));
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	initPosX = x;
	initPosY = y;
	maxY = GameManager::GetInstance()->GetTerrainData(x) + 20;
	enable = false;

	EventManager::GetInstance()->AddEvent(std::bind(&FelledTrap::Awake, this), EEvent::eEvent_ResetGameScene);
}

void FelledTrap::Release()
{
	delete xmlRect;
}

void FelledTrap::Update(float Delta)
{
	int dist = abs(x - GameManager::GetInstance()->GetPlayerPosX());
	if (dist< 80)
	{
		active = true;
	}

	if (active)
	{
		Down(Delta);

		SoundManager::GetInstance()->Play(ESound::sound_FelledTrap);
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

	int drawToScreenPosX = (x - int(width * 0.5f)) - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));

	Gdiplus::Rect rect2(drawToScreenPosX, y - int(height * 0.5f), width, height);
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
		y += int(Delta * DOWN_FORCE);
	}
	else
	{
		tag = eTag_Collider;
	}
}

void FelledTrap::OnTrap()
{
	SoundManager::GetInstance()->Play(ESound::sound_FelledTrap);
	active = true;
}

void FelledTrap::Awake()
{
	x = initPosX;
	y = initPosY;
	active = false;
	tag = eTag_FallenTrap;
	SoundManager::GetInstance()->Stop(ESound::sound_FelledTrap);

}

bool FelledTrap::HasInteraction()
{
	return false;
}
