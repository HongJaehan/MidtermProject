#include "pch.h"
#include "Rope.h"


Rope::Rope()
{
}

Rope::Rope(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	collider = new BoxCollider2D(_x, _y, _width, _height, true);

}
Rope::~Rope()
{
}

void Rope::Init()
{
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	InitPosX = x;
	InitPosY = y;
	active = false;
	enable = false;
	animation.Init();
	EventManager::GetInstance()->AddEvent(std::bind(&Rope::Awake, this), EEvent::eEvent_ResetGameScene);
	EventManager::GetInstance()->AddEvent(std::bind(&Rope::StartAnimation, this), EEvent::eEvent_CutRope);
}

void Rope::Release()
{
	delete collider;
}

void Rope::Update(float Delta)
{
	animation.Update(&atlasRect, Delta, active);
}

void Rope::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() -int(defines.screenSizeX * 0.5f));


	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Gdiplus::Rect r(0, 0, width, height);

	if (!animation.GetAtlasImg().expired())
	{
		temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
			atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}

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

void Rope::Awake()
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
