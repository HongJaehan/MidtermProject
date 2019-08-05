#include "pch.h"
#include "Player.h"

Player::Player()
{
	img = new Gdiplus::Image(TEXT("player.png"));
}

Player::~Player()
{

}

Gdiplus::Image* Player::GetImage()
{
	return img;
}

void Player::Control()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{

	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{

	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{

	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{

	}
	else if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{

	}


}

void Player::Update()
{

}

void Player::Render()
{

}