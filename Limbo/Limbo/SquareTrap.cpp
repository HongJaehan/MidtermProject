#include "pch.h"
#include "SquareTrap.h"

#define COL_POS_Y 257
SquareTrap::SquareTrap()
{
}

SquareTrap::SquareTrap(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height-520, false);

}

SquareTrap::~SquareTrap()
{
}

void SquareTrap::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("Object.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	}
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eSquareTrap));
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	initPosX = x;
	initPosY = y;
	maxY = GameManager::GetInstance()->GetTerrainData(x);
	enable = false;
	EventManager::GetInstance()->AddEvent(std::bind(&SquareTrap::Awake, this), EEvent::eEvent_ResetGameScene);
	//Rope가 끊어지는 Event에 Trap을 발동시키는 함수 등록
	EventManager::GetInstance()->AddEvent(std::bind(&SquareTrap::OnTrap, this), EEvent::eEvent_CutRope);
}

void SquareTrap::Release()
{
	delete collider;
	delete xmlRect;
}

void SquareTrap::Update(float Delta)
{
	if (active)
	{
		Down(Delta);
	}
	collider->SetY(y+COL_POS_Y);
}

void SquareTrap::Render(Gdiplus::Graphics* MemG)
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

void SquareTrap::Collision(Object* obj)
{
	if (tag == eTag_SquareRock)
	{
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	}

}

void SquareTrap::Down(float Delta)
{
	if (y + int(height * 0.5f) < maxY)
	{
		y += int(Delta * 400);
	}
	else
	{
		tag = eTag_Collider;
	}
}

void SquareTrap::OnTrap()
{
	active = true;
}
void SquareTrap::Awake()
{
	x = initPosX;
	y = initPosY;
	active = false;
	tag = eTag_SquareRock;
}

bool SquareTrap::HasInteraction()
{
	return false;
}
