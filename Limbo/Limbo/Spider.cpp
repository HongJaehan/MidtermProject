#include "pch.h"
#include "Spider.h"

Spider::Spider()
{
}

Spider::Spider(ETag _tag, int _x, int _y, int _width, int _height)
{
	colImg = AssetManager().GetInstance()->GetImage(TEXT("spider1.png")).lock().get();
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	enable = false;
	action = false;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);
}

Spider::~Spider()
{
	delete collider;
}

void Spider::Update(float Delta)
{
	//animation.Update(&atlasRect, Delta, action);
	if ((x - width * 0.5f) - GameManager::GetInstance()->GetPlayerPosX() < 100)
	{
		if (action == false)
		{
			action = true;
		}
	}
	collider->SetX(x);
	collider->SetY(y);
}

void Spider::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);
	////PlayerÀÇ Å©±â
	//Gdiplus::Rect rect(0, 0, width, height);

	//Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);


	//Gdiplus::Rect r(0, 0, width, height);
	//temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
	//	atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//Gdiplus::Rect rect2(drawToScreenPosX,screenPosY, width, height);
	//MemG->DrawImage(&bm, rect2);

	Gdiplus::Rect rect(drawToScreenPosX, y - height*0.5f, width, height);
	MemG->DrawImage(colImg, rect);
}

void Spider::Collision(Object* obj)
{
	EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	//int Bottom = collider->GetY() + collider->GetHeight()*0.5f;
}
