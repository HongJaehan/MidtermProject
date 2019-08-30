#include "pch.h"
#include "Trap_Black.h"
#define ADD_RENDER_HEIGHT 20

Trap_Black::Trap_Black()
	:InitPosX(0),
	InitPosY(0),
	action(false),
	screenPosX(0),
	screenPosY(0)
{
}

Trap_Black::Trap_Black(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width - 50, _height - 20, false);
}

Trap_Black::~Trap_Black()
{

}

void Trap_Black::Init()
{
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	InitPosX = x;
	InitPosY = y;
	enable = false;
	animation.Init();
	EventManager::GetInstance()->AddEvent(std::bind(&Trap_Black::Awake, this), EEvent::eEvent_ResetGameScene);
}

void Trap_Black::Release()
{
	delete collider;
}

void Trap_Black::Update(float Delta)
{
	animation.Update(&atlasRect, Delta, action);

	y = GameManager::GetInstance()->GetTerrainData(x) - int(height * 0.5f);
	collider->SetX(x);
	collider->SetY(y + int(height * 0.3f));

}

void Trap_Black::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = x - int(width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Gdiplus::Rect r(0, 0, width, height);
	if (animation.GetAtlasImg().expired())
	{
		return;
	}
	temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
		atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::Rect rect2(drawToScreenPosX, y - int(height * 0.5f) + ADD_RENDER_HEIGHT, width, height);
	MemG->DrawImage(&bm, rect2);
}

void Trap_Black::Collision(Object* obj)
{
	Player* _obj = dynamic_cast<Player*>(obj);
	if (obj->GetCollider() == nullptr)
	{
		return;
	}

	if (GetCollider() == nullptr)
	{
		return;
	}

	int playerLeft = obj->GetCollider()->GetX() - int(obj->GetCollider()->GetWidth() * 0.5f);
	int playerRight = obj->GetCollider()->GetX() + int(obj->GetCollider()->GetWidth() * 0.5f);
	int playerTop = obj->GetCollider()->GetY() - int(obj->GetCollider()->GetHeight() * 0.5f);
	int playerBottom = obj->GetCollider()->GetY() + int(obj->GetCollider()->GetHeight() * 0.5f);

	int objLeft = collider->GetX() - int(collider->GetWidth() * 0.5f);
	int objRight = collider->GetX() + int(collider->GetWidth() * 0.5f);
	int objTop = collider->GetY() - int(collider->GetHeight() * 0.5f);
	int objBottom = collider->GetY() + int(collider->GetHeight() * 0.5f);

	if (playerBottom > objTop && abs(playerBottom - objTop) < 10)
	{
		action = true;
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
		return;
	}
}

void Trap_Black::Awake()
{
	x = InitPosX;
	y = InitPosY;
	action = false;
}

bool Trap_Black::HasInteraction()
{
	return true;
}