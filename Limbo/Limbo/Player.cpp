#include "pch.h"
#include "Player.h"
#include "MainFrm.h"

Player::Player()
{
	img = AssetManager::GetInstance()->GetImage(TEXT("Player.png"));
	tempImg = new Gdiplus::Image(TEXT("player.png"));
	tag = ePlayer;
	state = eState_Idle;
	
	pos.SetX(0);
	pos.SetY(0);

	//MemG = 
}

Player::~Player()
{

}

std::weak_ptr<Gdiplus::Image> Player::GetImage()
{
	return img;
}

void Player::Control()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		state = eState_Run;
		pos.SetX(pos.GetX()-10);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		state = eState_Run;
		pos.SetX(pos.GetX()+10);

	}
	else if (GetAsyncKeyState(VK_UP) & 0x1001)
	{
		state = eState_Jump;
	}
	else if (GetAsyncKeyState(VK_CONTROL) & 0x8001)
	{

	}
	else
	{
		state = eState_Idle;
	}
}

void Player::Update(int Delta)
{
	switch (state)
	{
	case eState_Idle:
		break;
	case eState_Run:
		break;
	case eState_Jump:
		break;
	}
}

void Player::Render(Gdiplus::Graphics* MemG)
{
	//Player의 크기
	Gdiplus::Rect rect(0,0,116,163);
	Gdiplus::Bitmap bm(116, 163, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(tempImg,rect);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(pos.GetX(), pos.GetY(), 116, 163);
	MemG->DrawImage(&bm, screenPosRect);
	//temp.DrawImage(img.lock,rect, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height,
	//	Gdiplus::Unit::UnitPixel,nullptr, 0, nullptr);

	//MemG->DrawImage(&bm, rect);
	//MemG->DrawImage()
}