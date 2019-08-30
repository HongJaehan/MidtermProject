#include "pch.h"
#include "Corpse.h"

Corpse::Corpse()
	:initPosX(0),
	initPosY(0),
	bFlagOnEvent(false),
	cutRopeEventPos(0),
	img(nullptr),
	screenPosX(0),
	screenPosY(0),
	xmlRect(nullptr)
{

}

Corpse::Corpse(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width - 50, _height - 10, false);
}

Corpse::~Corpse()
{
}

void Corpse::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("Object.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	}
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eCorpse));
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	initPosX = x;
	initPosY = y;
	enable = false;
	bFlagOnEvent = false;
	cutRopeEventPos = CORPSE_EVENT_POS;

	EventManager::GetInstance()->AddEvent(std::bind(&Corpse::Awake, this), EEvent::eEvent_ResetGameScene);

}

void Corpse::Release()
{
	delete collider;
}

void Corpse::Update(float Delta)
{
	y = GameManager::GetInstance()->GetTerrainData(x) - int(height * 0.5f);
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

	int drawToScreenPosX = (x - int(width * 0.5f)) - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));

	//Gdiplus::Rect rect2(drawToScreenPosX, y - (height * 0.5f), width, height);
	Gdiplus::Rect rect2(drawToScreenPosX, y, width, height);

	MemG->DrawImage(&bm, rect2);

}
void Corpse::Collision(Object* obj)
{

}

void Corpse::Awake()
{
	x = initPosX;
	y = initPosY;
}

bool Corpse::HasInteraction()
{
	return true;
}

void Corpse::CutRope()
{
	EventManager::GetInstance()->OnEvent(eEvent_CutRope);
}
