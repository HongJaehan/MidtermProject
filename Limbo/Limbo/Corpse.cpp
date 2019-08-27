#include "pch.h"
#include "Corpse.h"

Corpse::Corpse()
{
}

Corpse::Corpse(ETag _tag, int _x, int _y, int _width, int _height)
{

	img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eCorpse));
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
	bFlagOnEvent = false;
	cutRopeEventPos = 500;
	collider = new BoxCollider2D(_x, _y, _width-50, _height-10, false);

	EventManager::GetInstance()->AddEvent(std::bind(&Corpse::Init, this), EEvent::eEvent_ResetGameScene);
}

Corpse::~Corpse()
{
}

void Corpse::Update(float Delta)
{
	y = GameManager::GetInstance()->GetTerrainData(x) - (height * 0.5f);
	collider->SetX(x);
	collider->SetY(y);

	if (bFlagOnEvent == false)
	{
		if (y > cutRopeEventPos)
		{
			bFlagOnEvent = true;
			CutRope();
		}
	}
	//printf("dx = %d\n" ,x);
}

void Corpse::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(img, rect,
		xmlRect->X, xmlRect->Y, xmlRect->Width, xmlRect->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	int drawToScreenPosX = (x - width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);

	//Gdiplus::Rect rect2(drawToScreenPosX, y - (height * 0.5f), width, height);
	Gdiplus::Rect rect2(drawToScreenPosX, y, width, height);

	MemG->DrawImage(&bm, rect2);

}
void Corpse::Collision(Object* obj)
{

}

void Corpse::Init()
{
	x = InitPosX;
	y = InitPosY;
}

bool Corpse::HasInteraction()
{
	return true;
}

void Corpse::CutRope()
{
	EventManager::GetInstance()->OnEvent(eEvent_CutRope);
}
