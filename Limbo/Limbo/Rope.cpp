#include "pch.h"
#include "Rope.h"


Rope::Rope()
{

}

Rope::Rope(ETag _tag, int _x, int _y, int _width, int _height)
{
	//img = AssetManager().GetInstance()->GetImage(TEXT("Rope.png")).lock().get();
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

	collider = new BoxCollider2D(_x, _y, _width, _height, true);
	EventManager::GetInstance()->AddEvent(std::bind(&Rope::Init, this), EEvent::eEvent_ResetGameScene);
	EventManager::GetInstance()->AddEvent(std::bind(&Rope::StartAnimation, this), EEvent::eEvent_CutRope);

}
Rope::~Rope()
{
}

void Rope::Update(float Delta)
{
	animation.Update(&atlasRect, Delta, active);
}

void Rope::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);


	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Gdiplus::Rect r(0, 0, width, height);
	temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
		atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::Rect rect2(drawToScreenPosX, y , width, height);
	MemG->DrawImage(&bm, rect2);
}

void Rope::Collision(Object* obj)
{
	//Rope가 끊어지는 소리 재생
	SoundManager::GetInstance()->Play(ESound::sound_Rope);
	//EventManager을 통해 Rope가 끊어지는 Event발생
	EventManager::GetInstance()->OnEvent(EEvent::eEvent_CutRope);
	
	active = true;
}

void Rope::Init()
{
	SoundManager::GetInstance()->Stop(ESound::sound_Rope);
	active = false;
}

void Rope::StartAnimation()
{
	active = true;
}

bool Rope::HasInteraction()
{
	return false;
}
