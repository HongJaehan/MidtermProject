#include "pch.h"
#include "Player.h"
#include "MainFrm.h"
#include "PlayerControlComponent.h"
#include <cmath>

#define MAX_velocity 1
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
	tag = eTag_Player;
	state = eState_Idle;
	bFlagLeft = false;
	velocity = 0.1f;
	width = defines.playerWidth;
	height = defines.playerHeight;
	enable = true;
//	float speed = Lerp(0, 10, 2);
	
	//AnimationList에 애니메이션을 추가해준다.  enum순서대로 넣어줘야 한다ㄷ
	AddAnimation(new Animation_Idle());
	AddAnimation(new Animation_Run());
	AddAnimation(new Animation_Jump());
	AddAnimation(new Animation_Die());
	int screenSizeWidth = defines.screenSizeX;
	//x = screenSizeWidth * 0.5f;
	x = 2500;
	y = 450;

	collider = new BoxCollider2D(x, y, width, height, false);

	playerScreenPosX = x - width * 0.5;
	playerScreenPosY = y - height * 0.5;

 	EventManager::GetInstance()->AddEvent(std::bind(&Player::PlayerDie, this),EEvent::eEvent_PlayerDie);
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
	delete collider;
}

void Player::Update(float Delta)
{
	//Component Update
	control.Update(*this);
	//physics 업데이트
	PhysicsUpdate(Delta);
	GameManager::GetInstance()->SetPlayerPosX(x);
	collider->SetX(x);
	collider->SetY(y);

	//현재 Animation의 image를 XML정보에 맞춰 저장해줌.
	playerAnimationList[state]->Update(&atlasRect,Delta);

}

void Player::Render(Gdiplus::Graphics* _MemG)
{
	//Player의 크기
	Gdiplus::Rect rect(0,0,width,height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(),rect,
		atlasRect.X , atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	int playerScreenWidth;
	int playerScreenHeight;
	if (state == eState_Die)
	{
		playerScreenWidth = defines.playerWidth_Die;
		playerScreenHeight = defines.playerHeight_Die;
	}
	else
	{
		playerScreenWidth = width;
		playerScreenHeight = height;
	}
	Gdiplus::Rect screenPosRect(defines.screenSizeX / 2 - width * 0.5f, y - height *0.5f + 10, playerScreenWidth, height);
	


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
			x -= velocity * Delta; 
		}
		else
		{
			x += velocity * Delta;
		}

		y = y + (-150 * Delta) + AddVal;

		if (y > terrainY)
		{
			y = terrainY;
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

static float AddUpdateDelta = 0;
void Player::PhysicsUpdate(float Delta)
{
	AddUpdateDelta += Delta;

	if (AddUpdateDelta > 1.0f)
	{
		AddUpdateDelta = 0.5f;
	}
	//GameManager에 현재 Player의 X좌표를 보내 Terrain의 Y 정보를 받아온다.
	int terrainY = GameManager::GetInstance()->GetTerrainData(x) - height * 0.5f;
	switch (state)
	{
	case eState_Idle:
		y = y + GRAVITY * AddUpdateDelta;
		velocity = INIT_velocity; //속도 초기화
		AddUpdateDelta = 0.0f;
		//현재 Player의 Y좌표가 Terrain보다 크다면
		if (y >= terrainY)
		{
			y = terrainY;
		}
		break;
	case eState_Run:
		velocity = ACCELERATION * AddUpdateDelta * 1.3f;
		if (bFlagLeft)
		{
			x -= velocity * Delta;
		}
		else
		{
			x += velocity * Delta;
		}
		y = y + GRAVITY * AddUpdateDelta;
		//현재 Player의 Y좌표가 Terrain보다 크다면
		if (y >= terrainY)
		{
			y = terrainY;
		}
		break;
	case eState_Jump:
		Jump(bFlagLeft, terrainY, Delta);
		break;
	case eState_Die:
		y = y + GRAVITY * AddUpdateDelta;
		if (y >= terrainY)
		{
			y = terrainY;
		}
		break;
	
#pragma region MyRegion
		//pos.SetY(jumpInitPosY + velocity * cos(DEGTORAD(-45)) - 0.5f * GRAVITY * Delta * Delta);
	//pos.SetX(jumpInitPosX + 10 * cos(DEGTORAD(-45)) * Delta);
	//AddDelta += Delta;
	//float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
	//pos.SetX(x +  velocity * 100 * Delta);
	//pos.SetY(y + (-400.f * Delta) + AddVal);

	//예시
	/*if (y >= jumpInitPosY)
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
		/*collider->SetY(y);
		collider->SetX(x);*/
}


EPlayerState Player::GetState()
{
	return state;
}

void Player::Collision(Object* obj)
{

	if (obj->GetTag() != eTag_Collider)
	{
		return;
	}

	int objLeft = obj->GetCollider()->GetX() - obj->GetCollider()->GetWidth() * 0.5f;
	int objRight = obj->GetCollider()->GetX() + obj->GetCollider()->GetWidth() * 0.5f;
	int objTop = obj->GetCollider()->GetY() - obj->GetCollider()->GetHeight() * 0.5f;
	int objBottom = obj->GetCollider()->GetY() + obj->GetCollider()->GetHeight() * 0.5f;

	int pLeft = GetCollider()->GetX() - GetCollider()->GetWidth() * 0.5f;
	int pRight = GetCollider()->GetX() + GetCollider()->GetWidth() * 0.5f;
	int pTop = GetCollider()->GetY() - GetCollider()->GetHeight() * 0.5f;
	int pBottom = GetCollider()->GetY() + GetCollider()->GetHeight() * 0.5f;
	
	if (pLeft < objRight && abs(objRight - pLeft) < width)
	{
		x = objRight + width * 0.5f;
	}
	else if (pRight > objLeft && abs(pRight-objLeft) < width)
	{
		x = objLeft - width * 0.5f;
	}
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

void Player::PlayerDie()
{
	ChangeState(eState_Die);
}
