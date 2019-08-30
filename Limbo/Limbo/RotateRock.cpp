#include "pch.h"
#include "RotateRock.h"

RotateRock::RotateRock()
{
}

RotateRock::RotateRock(ETag _tag, int _x, int _y, int _width, int _height)
{

	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width, _height, false);
}

RotateRock::~RotateRock()
{
}

void RotateRock::Init()
{
	if (!AssetManager().GetInstance()->GetImage(TEXT("Rock.png")).expired())
	{
		img = AssetManager().GetInstance()->GetImage(TEXT("Rock.png")).lock().get();
	}
	enable = false;
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	state = eRotateRock_Idle;
	initPosX = x;
	initPosY = y;
	rotateNum = 0;
	minX = ROCK_MIX_X + int(width * 0.5f);
	EventManager::GetInstance()->AddEvent(std::bind(&RotateRock::Awake, this), EEvent::eEvent_ResetGameScene);
}

void RotateRock::Release()
{
	delete collider;
	delete xmlRect;
}

void RotateRock::Update(float Delta)
{
	switch (state)
	{
	case eRotateRock_Idle:
		if ((x - width * 0.5f) - GameManager::GetInstance()->GetPlayerPosX() < ROCK_EVENT_DIST)
		{
			state = eRotateRock_Move;
			SoundManager::GetInstance()->Play(ESound::sound_Rock);
		}
		break;
	case eRotateRock_Move:
		if (x > minX)
		{
			x -= int(Delta * 200);
		}
		else
		{
			state = eRotateRock_Stop;
			tag = eTag_Collider;
			SoundManager::GetInstance()->Stop(ESound::sound_Rock);
			collider->SetWidth(width - 70);
			collider->SetHeight(height - 70);

		}
		break;
	}
	y = GameManager::GetInstance()->GetTerrainData(x) - int(height * 0.5f);
	collider->SetX(x);
	collider->SetY(y);

	

}

void RotateRock::Render(Gdiplus::Graphics* MemG)
{
	rotateNum++;
	if (rotateNum > 2)
	{
		rotateNum = 0;
	}

	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(img, rect,
		0,0,142,142, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);


	if (state == eRotateRock_Move)
	{
		switch(rotateNum)
		{
		case 0:
			bm.RotateFlip(Gdiplus::Rotate90FlipX);
			break;
		case 1:
			bm.RotateFlip(Gdiplus::Rotate180FlipX);
			break;
		case 2:
			bm.RotateFlip(Gdiplus::Rotate270FlipX);
			break;
		}
		
	}
	//bm.RotateFlip(Gdiplus::Rotate90FlipX);
	int drawToScreenPosX = (x - int(width * 0.5f)) - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));

	Gdiplus::Rect rect2(drawToScreenPosX, y - int(height * 0.5f) + 10, width, height);
	MemG->DrawImage(&bm, rect2);
}

void RotateRock::Collision(Object* obj)
{
	if (obj->GetTag() == eTag_Player && tag != eTag_Collider)
	{
		EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
		SoundManager::GetInstance()->Stop(ESound::sound_Rock);
		return;
	}
}

void RotateRock::Awake()
{
	x = initPosX;
	y = initPosY;
	state = eRotateRock_Idle;
	collider->SetWidth(width + 70);
	collider->SetHeight(height + 70);
	SoundManager::GetInstance()->Stop(ESound::sound_Rock);

}

bool RotateRock::HasInteraction()
{
	return false;
}

