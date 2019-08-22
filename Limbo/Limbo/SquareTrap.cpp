#include "pch.h"
#include "SquareTrap.h"

SquareTrap::SquareTrap()
{
}

SquareTrap::SquareTrap(ETag _tag, int _x, int _y, int _width, int _height)
{
	img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
	xmlRect = new Gdiplus::Rect(GameManager::GetInstance()->GetObjectRect(EObjectNum::eSquareTrap));
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

	collider = new BoxCollider2D(_x, _y, _width, _height-520, false);

	EventManager::GetInstance()->AddEvent(std::bind(&SquareTrap::Init, this), EEvent::eEvent_ResetGameScene);

	//Rope가 끊어지는 Event에 Trap을 발동시키는 함수 등록
	EventManager::GetInstance()->AddEvent(std::bind(&SquareTrap::OnTrap, this), EEvent::eEvent_CutRope);

}

SquareTrap::~SquareTrap()
{
}

void SquareTrap::Update(float Delta)
{
	if (active)
	{
		Down(Delta);
	}
	collider->SetY(y+257);
}

void SquareTrap::Render(Gdiplus::Graphics* MemG)
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

void SquareTrap::Collision(Object* obj)
{
	if (tag == eTag_SquareRock)
	{
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	}

}

void SquareTrap::Down(float Delta)
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

void SquareTrap::OnTrap()
{
	active = true;
}
void SquareTrap::Init()
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
