#include "pch.h"
#include "Player.h"
#include "MainFrm.h"
#include "PlayerControlComponent.h"
#include <cmath>

#define MAX_velocity 150
#define INIT_velocity 0
#define ACCELERATION 150
#define PI (3.1415926535897932f)
#define GRAVITY 7
#define JUMPFORCE 350
#define DEGTORAD(X) (X * (PI / 180))

float Lerp(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}

Player::Player()
{
	tag = ePlayer;
	state = eState_Idle;
	bFlagLeft = false;
	velocity = 0.1f;
	width = defines.playerWidth;
	height = defines.playerHeight;
	enable = true;

//	float speed = Lerp(0, 10, 2);

	//AnimationList에 애니메이션을 추가해준다.
	AddAnimation(new Animation_Idle());
	AddAnimation(new Animation_Run());
	AddAnimation(new Animation_Jump());

	int screenSizeWidth = defines.screenSizeX;
 	pos.SetX(screenSizeWidth*0.5f);
	pos.SetY(800);

	playerScreenPosX = pos.GetX() - width * 0.5;
	playerScreenPosY = pos.GetY() - height;

	//사용할 생각
	//pos.SetX(GameManager::GetInstance()->GetCheckPoint().first + width * 0.5);
	//pos.SetY(GameManager::GetInstance()->GetCheckPoint().first - height);

}

Player::~Player()
{
	for (auto& it : playerAnimationList)
	{
		delete it;

	}
}
//
//std::weak_ptr<Gdiplus::Image> Player::GetImage()
//{
//	//return img;
//}

void Player::Update(float Delta)
{
	//Component Update
	control.Update(*this);
	//physics 업데이트
	PhysicsUpdate(Delta);

	//현재 Animation의 image를 XML정보에 맞춰 저장해줌.
	playerAnimationList[state]->Update(&atlasRect,Delta);
}

void Player::Render(Gdiplus::Graphics* _MemG)
{
	//Player의 크기
	Gdiplus::Rect rect(0,0,width,height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(),rect, atlasRect.X , atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::Rect screenPosRect(defines.screenSizeX/2 - width*0.5f,pos.GetY()-height+10, width, height);

	//만약 좌측방향이라면 bit를 좌우 반전시켜준다.
	if (bFlagLeft)
	{
		bm.RotateFlip(Gdiplus::Rotate180FlipY);
	}

	_MemG->DrawImage(&bm, screenPosRect);

#if defined VEL_DEBUG
	if(ptList.size() < 2) return;
	for (auto it = ptList.begin(); it != ptList.end() - 1; ++it)
	{
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0), 1);
		Gdiplus::PointF& pt1 = *it;
		Gdiplus::PointF& pt2 = *(it + 1);
		MemG->DrawLine(&pen, pt1, pt2);
	}
#endif
	//temp.DrawImage(img.lock,rect, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height,
	//	Gdiplus::Unit::UnitPixel,nullptr, 0, nullptr);

	//MemG->DrawImage(&bm, rect);
	//MemG->DrawImage()
}

static float AddDelta = 0;
void Player::Jump(bool bFlagLeft,int terrainY,float Delta)
{
		AddDelta += Delta;
		float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);

		if (bFlagLeft)
		{
			pos.SetX(pos.GetX()-0.1f - velocity * Delta);
		}
		else
		{
			pos.SetX(pos.GetX()+0.1f + velocity * Delta);
		}
		pos.SetY(pos.GetY() + (-JUMPFORCE * Delta) + AddVal);

		if (pos.GetY() > terrainY)
		{
			pos.SetY(terrainY);
			ChangeState(eState_Idle);
			AddDelta = 0.0f;
			velocity = 0;
		}
}


void Player::AddAnimation(Animation* ani)
{
	playerAnimationList.emplace_back(ani);
}

void Player::ChangeState(EPlayerState _state)
{
	playerAnimationList[state]->End();
	state = _state;
	playerAnimationList[state]->Begin();
}

EPlayerState Player::GetState()
{
	return state;
}
bool Player::GetLeftFlag()
{
	return bFlagLeft;
}
void Player::SetLeftFlag(bool Flag)
{
	bFlagLeft = Flag;
}

void Player::InitVelocity()
{
	velocity = 0;
}

static float AddUpdateDelta = 0;
void Player::PhysicsUpdate(float Delta)
{
	AddUpdateDelta += Delta;

	if (AddUpdateDelta > 1.0f)
	{
		AddUpdateDelta = 1.0f;
	}
	//GameManager에 현재 Player의 X좌표를 보내 Terrain의 Y 정보를 받아온다.
	int terrainY = GameManager::GetInstance()->GetTerrainData(pos.GetX() + width * 0.5f);

	switch (state)
	{
	case eState_Idle:
		pos.SetY(pos.GetY() + GRAVITY * AddUpdateDelta);
		velocity = INIT_velocity; //속도 초기화
		AddUpdateDelta = 0.0f;
		//현재 Player의 Y좌표가 Terrain보다 크다면
		if (pos.GetY() >= terrainY)
		{
			pos.SetY(terrainY);
		}
		break;
	case eState_Run:
		velocity = ACCELERATION * AddUpdateDelta;
		if (bFlagLeft)
		{
			pos.SetX(pos.GetX() - velocity * Delta);
		}
		else
		{
			pos.SetX(pos.GetX() + velocity * Delta);
		}
		pos.SetY(pos.GetY() + GRAVITY * AddUpdateDelta);
		//현재 Player의 Y좌표가 Terrain보다 크다면
		if (pos.GetY() >= terrainY)
		{
			pos.SetY(terrainY);
		}
		break;
	case eState_Jump:
		Jump(bFlagLeft, terrainY, Delta);
		break;
#pragma region MyRegion
		//pos.SetY(jumpInitPosY + velocity * cos(DEGTORAD(-45)) - 0.5f * GRAVITY * Delta * Delta);
	//pos.SetX(jumpInitPosX + 10 * cos(DEGTORAD(-45)) * Delta);
	//AddDelta += Delta;
	//float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
	//pos.SetX(pos.GetX() +  velocity * 100 * Delta);
	//pos.SetY(pos.GetY() + (-400.f * Delta) + AddVal);

	//예시
	/*if (pos.GetY() >= jumpInitPosY)
	{
		state = eState_Idle;
		pos.SetY(jumpInitPosY);
		AddDelta = 0;
	}*/
	//jumpInitPosX += 10.f * velocity * Delta;
	//jumpInitPosY += (-200.f * Delta) + AddVal;
#if defined VEL_DEBUG
		for (int i = 0; i < 1000; ++i)
		{
#endif

#if defined VEL_DEBUG
			ptList.emplace_back(Gdiplus::PointF(jumpInitPosX, jumpInitPosY));
		}
#else
			//pos.SetX(jumpInitPosX);
			//pos.SetY(jumpInitPosY);
#endif

			//AddDelta += Delta;
			//float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
			//
			//pos.SetX(X + velocity * cos(DEGTORAD(45)) * Delta);
			//pos.SetY(Y + (-1000 * Delta) + AddVal);
#pragma endregion
	}
}