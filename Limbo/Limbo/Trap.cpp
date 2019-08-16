#include "pch.h"
#include "Trap.h"

Trap::Trap()
{

}

Trap::Trap(ETag _tag, int _x, int _y, int _width, int _height)
{
	//img = AssetManager().GetInstance()->GetImage(TEXT("collider.png")).lock().get();
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	enable = false;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);
}

Trap::~Trap()
{

}

void Trap::Update(float Delta)
{
	
}

void Trap::Render(Gdiplus::Graphics* MemG)
{
	//PlayerÀÇ Å©±â
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	
	temp.DrawImage(animation.GetAtlasImg().lock().get(), rect,
		atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	Gdiplus::Rect rect2(drawToScreenPosX, screenPosY, width, height);
	MemG->DrawImage(&bm, rect2);
}

void Trap::Collision(Object* obj)
{

}
