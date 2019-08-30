#include "pch.h"
#include "FallenRock.h"

FallenRock::FallenRock()
{
}

FallenRock::FallenRock(ETag _tag, int _x, int _y, int _width, int _height,EObjectNum objNum)
{

	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height, false);
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(objNum));
}

FallenRock::~FallenRock()
{

}

void FallenRock::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("Object.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	}
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	initPosX = x;
	initPosY = y;
	maxY = GameManager::GetInstance()->GetTerrainData(x) + 200;
	enable = false;
	EventManager::GetInstance()->AddEvent(std::bind(&FallenRock::Awake, this), EEvent::eEvent_ResetGameScene);
}

void FallenRock::Release()
{
	delete collider;
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

		int drawToScreenPosX = (x - int(width * 0.5f)) - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));

		Gdiplus::Rect rect2(drawToScreenPosX, y - int(height * 0.5f), width, height);
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
		y += int(Delta * 70);
	}
	else
	{
		SoundManager::GetInstance()->Stop(ESound::sound_FallenRock);
	}
}

void FallenRock::Awake()
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

