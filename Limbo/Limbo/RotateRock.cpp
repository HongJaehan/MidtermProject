#include "pch.h"
#include "RotateRock.h"

RotateRock::RotateRock()
{
}

RotateRock::RotateRock(ETag _tag, int _x, int _y, int _width, int _height)
{
	//img = AssetManager().GetInstance()->GetImage(TEXT("Object.png")).lock().get();
 	img = AssetManager().GetInstance()->GetImage(TEXT("Rock.png")).lock().get();

	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	enable = false;
	screenPosX = x - width * 0.5;
	screenPosY = y - height * 0.5;
	state = eRotateRock_Idle;
	initPosX = x;
	initPosY = y;
	rotateNum = 0;
	minX = 7810 + width * 0.5f;

	collider = new BoxCollider2D(_x, _y, _width, _height, false);
//	bm = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
	EventManager::GetInstance()->AddEvent(std::bind(&RotateRock::Init, this), EEvent::eEvent_ResetGameScene);
}

RotateRock::~RotateRock()
{
	delete collider;
	delete xmlRect;
}

void RotateRock::Update(float Delta)
{
	switch (state)
	{
	case eRotateRock_Idle:
		if ((x - width * 0.5f) - GameManager::GetInstance()->GetPlayerPosX() < 500)
		{
			state = eRotateRock_Move;
			SoundManager::GetInstance()->Play(ESound::sound_Rock);
		}
		break;
	case eRotateRock_Move:
		if (x > minX)
		{
			x -= Delta * 200;
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
	y = GameManager::GetInstance()->GetTerrainData(x) - height * 0.5f;
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
	int drawToScreenPosX = (x - width * 0.5f) - (GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f);

	Gdiplus::Rect rect2(drawToScreenPosX, y - (height * 0.5f)+10, width, height);
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

void RotateRock::Init()
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

