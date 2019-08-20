#include "pch.h"
#include "RotateRock.h"

RotateRock::RotateRock()
{
}

RotateRock::RotateRock(ETag _tag, int _x, int _y, int _width, int _height)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eRotateRock));
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	enable = false;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	state = eRotateRock_Idle;
	initPosX = x;
	initPosY = y;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);

	EventManager::GetInstance()->AddEvent(std::bind(&RotateRock::Init, this), EEvent::eEvent_ResetGameScene);
}

RotateRock::~RotateRock()
{
	delete collider;
	delete xmlRect;
}

void RotateRock::Update(float Delta)
{
	switch (state)
	{
	case eRotateRock_Idle:
		if ((x - width * 0.5f) - GameManager::GetInstance()->GetPlayerPosX() < 500)
		{
			state = eRotateRock_Move;
		}
		break;
	case eRotateRock_Move:
		x -= Delta * 190;
		break;
	}
	y = GameManager::GetInstance()->GetTerrainData(x) - height * 0.5f;
	collider->SetX(x);
	collider->SetY(y);
}

void RotateRock::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(img, rect,
		xmlRect->X, xmlRect->Y, xmlRect->Width, xmlRect->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	if (state == eRotateRock_Move)
	{
		bm.RotateFlip(Gdiplus::Rotate90FlipY);
	}

	int drawToScreenPosX = (x - width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);

	Gdiplus::Rect rect2(drawToScreenPosX, y - (height * 0.5f), width, height);
	MemG->DrawImage(&bm, rect2);
}

void RotateRock::Collision(Object* obj)
{
	if (obj->GetTag() == eTag_Player)
	{
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
		return;
	}
}

void RotateRock::Init()
{
	x = initPosX;
	y = initPosY;
	state = eRotateRock_Idle;
}

