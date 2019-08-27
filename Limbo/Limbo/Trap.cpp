#include "pch.h"
#include "Trap.h"

Trap::Trap()
{

}

Trap::Trap(ETag _tag, int _x, int _y, int _width, int _height)
{
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
	animState.Init();

	collider = new BoxCollider2D(_x, _y, _width-50, _height-20, false);

	EventManager::GetInstance()->AddEvent(std::bind(&Trap::Awake, this), EEvent::eEvent_ResetGameScene);
}

Trap::~Trap()
{
	delete collider;
}

void Trap::Update(float Delta)
{
	animState.Update(&atlasRect, Delta, action);

	y = GameManager::GetInstance()->GetTerrainData(x)-height*0.5f;
	collider->SetX(x);
	collider->SetY(y+height*0.3f);

}

void Trap::Render(Gdiplus::Graphics* MemG)
{


	int drawToScreenPosX = x - (width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);


	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);


	Gdiplus::Rect r(0, 0, width, height);

	if (animState.GetAtlasImg().expired())
	{
		return;
	}
	temp.DrawImage(animState.GetAtlasImg().lock().get(), r,
		atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	Gdiplus::Rect rect2(drawToScreenPosX, y-height*0.5f + 5, width, height);
	MemG->DrawImage(&bm, rect2);
}

void Trap::Collision(Object* obj)
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
	
	int playerLeft = obj->GetCollider()->GetX() - obj->GetCollider()->GetWidth()*0.5f;
	int playerRight = obj->GetCollider()->GetX() + obj->GetCollider()->GetWidth() * 0.5f;
	int playerTop = obj->GetCollider()->GetY() - obj->GetCollider()->GetHeight() * 0.5f;
	int playerBottom = obj->GetCollider()->GetY() + obj->GetCollider()->GetHeight() * 0.5f;

	int objLeft = collider->GetX() - collider->GetWidth() * 0.5f;
	int objRight = collider->GetX() + collider->GetWidth()* 0.5f;
	int objTop = collider->GetY() - collider->GetHeight() * 0.5f;
	int objBottom = collider->GetY() + collider->GetHeight() * 0.5f;

	if (playerBottom > objTop && abs(playerBottom - objTop) < 10)
	{
		action = true;
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
		return;
	}
}

void Trap::Awake()
{
	x = InitPosX;
	y = InitPosY;
	action = false;
}

bool Trap::HasInteraction()
{
	return true;
}
