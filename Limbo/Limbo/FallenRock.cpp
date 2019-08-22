#include "pch.h"
#include "FallenRock.h"

FallenRock::FallenRock()
{
}

FallenRock::FallenRock(ETag _tag, int _x, int _y, int _width, int _height,EObjectNum objNum)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(objNum));
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	initPosX = x;
	initPosY = y;
	maxY = GameManager::GetInstance()->GetTerrainData(x) + 200;
	enable = false;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);

	EventManager::GetInstance()->AddEvent(std::bind(&FallenRock::Init, this), EEvent::eEvent_ResetGameScene);
}

FallenRock::~FallenRock()
{
	delete xmlRect;
}

void FallenRock::Update(float Delta)
{
	if (active)
	{
		Down(Delta);
	}
	collider->SetY(y);
}

void FallenRock::Render(Gdiplus::Graphics* MemG)
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

void FallenRock::Collision(Object* obj)
{
	SoundManager::GetInstance()->Play(ESound::sound_FallenRock);
	active = true;
}

void FallenRock::Down(float Delta)
{
	if (y + (height * 0.5f) < maxY)
	{
		y += Delta * 70;
	}
	else
	{
		SoundManager::GetInstance()->Stop(ESound::sound_FallenRock);
	}
}

void FallenRock::Init()
{
	SoundManager::GetInstance()->Stop(ESound::sound_FallenRock);
	active = false;
	x = initPosX;
	y = initPosY;
}

inline bool FallenRock::HasInteraction()
{
	return false;
}

