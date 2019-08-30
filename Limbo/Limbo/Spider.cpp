#include "pch.h"
#include "Spider.h"

Spider::Spider()
{
}

Spider::Spider(ETag _tag, int _x, int _y, int _width, int _height)
{
	tag = _tag;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	collider = new BoxCollider2D(_x, _y, _width-50, _height, false);

}

Spider::~Spider()
{

}

void Spider::Init()
{
	screenPosX = x - int(width * 0.5f);
	screenPosY = y - int(height * 0.5f);
	enable = false;
	action = false;
	bFlagSoundOn = false;
	state = eSpiderState_Idle;
	initPosY = y;
	initPosX = x;
	animation.Init();
	maxY = GameManager::GetInstance()->GetTerrainData(x) - int(height * 0.5f);
	EventManager::GetInstance()->AddEvent(std::bind(&Spider::Awake, this), EEvent::eEvent_ResetGameScene);

}

void Spider::Release()
{
	delete collider;
}

void Spider::Update(float Delta)
{
	//animation.Update(&atlasRect, Delta, action);
	if ((x - width * 0.5f) - GameManager::GetInstance()->GetPlayerPosX() < 100
		&& state == eSpiderState_Idle)
	{
		state = eSpiderState_Down;
	}

	animation.Update(&atlasRect, Delta, state);
	switch (state)
	{
	case eSpiderState_Idle:
		break;
	case eSpiderState_Down:
		Down(Delta);
		break;
	case eSpiderState_Up:
		Up(Delta);
		break;
	}

	collider->SetX(x);
	collider->SetY(y);
}

void Spider::Render(Gdiplus::Graphics* MemG)
{
	int drawToScreenPosX = screenPosX - (GameManager::GetInstance()->GetPlayerPosX() - int(defines.screenSizeX * 0.5f));
	////PlayerÀÇ Å©±â
	//Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Gdiplus::Rect r(0, 0, width, height);

		temp.DrawImage(animation.GetAtlasImg().lock().get(), r,
			atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::Rect rect2(drawToScreenPosX, y - int(height * 0.5f) + 10, width, height);
	MemG->DrawImage(&bm, rect2);
}

void Spider::Collision(Object* obj)
{
	EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	//int Bottom = collider->GetY() + collider->GetHeight()*0.5f;
}

void Spider::Up(float Delta)
{
	if (bFlagSoundOn)
	{
		SoundManager::GetInstance()->Stop(ESound::sound_Spider);
		bFlagSoundOn = false;
	}
	if (state != eSpiderState_Idle)
	{
		if (y > initPosY)
		{
			y -= int(Delta * 70);
		}
		else
		{
			state = eSpiderState_Down;
		}
	}

}

void Spider::Down(float Delta)
{
	if (!bFlagSoundOn)
	{
		SoundManager::GetInstance()->Play(ESound::sound_Spider);
	}

	if (state != eSpiderState_Idle)
	{
		if (y < maxY)
		{
			y += (Delta * 400);
		}
		else
		{
			state = eSpiderState_Up;
		}
	}
}

void Spider::Awake()
{
	state = eSpiderState_Idle;
	x = initPosX;
	y = initPosY;
	SoundManager::GetInstance()->Stop(ESound::sound_Spider);

}

bool Spider::HasInteraction()
{
	return false;
}
