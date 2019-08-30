#include "pch.h"
#include "Player.h"
#include "MainFrm.h"
#include "PlayerControlComponent.h"
#include <cmath>

#define MAX_velocity 300
#define INIT_velocity 0.5f
#define ACCELERATION 150
#define PI (3.1415926535897932f)
#define GRAVITY 10
#define JUMPFORCE 350
#define DEGTORAD(X) (X * (PI / 180))

float Lerp(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}

Player::Player()
	:bFlagBotmCol(false),
	bFlagInteraction(false),
	bFlagJumpStartState(false),
	bFlagLeft(false),
	bFlagLeftCol(false),
	bFlagRightCol(false),
	bFlagNowCol(false),
	jumpInitPosX(0),
	jumpInitPosY(0),
	playerScreenPosX(0),
	playerScreenPosY(0),
	state(EPlayerState::eState_Idle),
	velocity(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	tag = eTag_Player;
	state = eState_Idle;
	velocity = 0.1f;
	width = defines.playerWidth;
	height = defines.playerHeight;
	enable = true;
	//	float speed = Lerp(0, 10, 2);

		//AnimationList에 애니메이션을 추가해준다.  enum순서대로 넣어줘야 한다
	AnimState_Idle* animState_Idle = new AnimState_Idle();
	animState_Idle->Init();
	AnimState_Die* animState_Die = new AnimState_Die();
	animState_Die->Init();
	AnimState_Run* animState_Run = new AnimState_Run();
	animState_Run->Init();
	AnimState_Jump* animState_Jump = new AnimState_Jump();
	animState_Jump->Init();
	AnimState_Interaction* animState_Interaction = new AnimState_Interaction();
	animState_Interaction->Init();
	AnimState_InteractionMove* animState_InteractionMove = new AnimState_InteractionMove();
	animState_InteractionMove->Init();

	AddAnimation(animState_Idle);
	AddAnimation(animState_Run);
	AddAnimation(animState_Jump);
	AddAnimation(animState_Die);
	AddAnimation(animState_Interaction);
	AddAnimation(animState_InteractionMove);

	int screenSizeWidth = defines.screenSizeX;
	//x = screenSizeWidth * 0.5f;
	x = PLAYER_INIT_POS_X;
	y = PLAYER_INIT_POS_Y;

	collider = new BoxCollider2D(x, y, width, height, false);

	playerScreenPosX = x - int(width * 0.5f);
	playerScreenPosY = y - int(height * 0.5f);

	EventManager::GetInstance()->AddEvent(std::bind(&Player::PlayerDie, this), EEvent::eEvent_PlayerDie);
	EventManager::GetInstance()->AddEvent(std::bind(&Player::MoveReady, this), EEvent::eEvent_MoveReady);

}

void Player::Release()
{
	for (auto& it : playerAnimationList)
	{
		SafeRelease(&it);
	}
	playerAnimationList.clear();

	delete collider;
}

void Player::Update(float Delta)
{
	//printf("Delta : %f\n", Delta);
	//Component Update
	//physics 업데이트
	control.Update(*this);

	PhysicsUpdate(Delta);
	GameManager::GetInstance()->SetPlayerPosX(x);
	collider->SetX(x);
	collider->SetY(y);

	//현재 Animation의 image를 XML정보에 맞춰 저장해줌.
	playerAnimationList[state]->Update(&atlasRect, Delta);
}

void Player::Render(Gdiplus::Graphics* _MemG)
{
	//Player의 크기
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	if (!playerAnimationList[state]->GetAtlasImg().expired())
	{
		temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect,
			atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}

	int playerScreenWidth;
	int playerScreenHeight;

	int screenPosY = y - int(height * 0.5f) + 10;

	switch (state)
	{
	case eState_Die:
		playerScreenWidth = defines.playerWidth_Die;
		playerScreenHeight = height;
		screenPosY += 10;
		break;
	case eState_InteractionMove:
		playerScreenWidth = width;
		playerScreenHeight = defines.playerHeight_InterMove;
		screenPosY += 20;
		break;
	default:
		playerScreenWidth = width;
		playerScreenHeight = height;
		break;
	}

	Gdiplus::Rect screenPosRect((defines.screenSizeX / 2) - int(width * 0.5f), screenPosY, playerScreenWidth, playerScreenHeight);



	//만약 좌측방향이라면 bit를 좌우 반전시켜준다.
	if (bFlagLeft)
	{
		bm.RotateFlip(Gdiplus::Rotate180FlipY);
	}

	_MemG->DrawImage(&bm, screenPosRect);

#if defined VEL_DEBUG
	if (ptList.size() < 2) return;
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
void Player::Jump(bool bFlagLeft, int terrainY, float Delta)
{
	AddDelta += Delta;
	float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);

	if (AddDelta > 0.3f)
	{
		bFlagJumpStartState = false;
	}
	int velocity_Int = (abs(velocity * Delta))+1;
	//printf("velocity : %d\n", velocity_Int);
	if (bFlagLeft && !bFlagLeftCol)
	{
		x -= velocity_Int;
	}
	else if (!bFlagLeft && !bFlagRightCol)
	{
		x += velocity_Int;
		//printf("vel = %f\n", velocity);
	}

	if (!bFlagBotmCol)
	{
		y = y + (-140 * Delta) + (AddVal);
	}

	if (y > terrainY)
	{
		y = terrainY;
		ChangeState(eState_Idle);
		AddDelta = 0.0f;
		InitVelocity();
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
static float RunSoundDelta = 0;
void Player::PhysicsUpdate(float Delta)
{
	AddUpdateDelta += Delta;
	if (AddUpdateDelta > 1.0f)
	{
		AddUpdateDelta = 0.5f;
	}
	//GameManager에 현재 Player의 X좌표를 보내 Terrain의 Y 정보를 받아온다.
	int terrainY = GameManager::GetInstance()->GetTerrainData(x) - int(height * 0.5f);
	switch (state)
	{
	case eState_Idle:
		if (!bFlagBotmCol)
		{
			y = y + int(GRAVITY * AddUpdateDelta) + 10;
		}
		velocity = INIT_velocity; //속도 초기화
		AddUpdateDelta = 0.0f;
		//현재 Player의 Y좌표가 Terrain보다 크다면
		if (y >= terrainY)
		{
			y = terrainY;
		}
		break;
	case eState_Run:
	{
		RunSoundDelta += Delta;
		if (RunSoundDelta > 8.0f)
		{
			SoundManager::GetInstance()->Stop(ESound::sound_walk);
			SoundManager::GetInstance()->Play(ESound::sound_walk);
			RunSoundDelta = 0.0f;
		}
		if (!bFlagBotmCol)
		{
			y = y + GRAVITY * int(AddUpdateDelta + 10);
		}
		//y = y + GRAVITY * AddUpdateDelta;
		velocity = ACCELERATION * AddUpdateDelta * 1.5f;
		if (velocity > MAX_velocity)
		{
			velocity = MAX_velocity;
		}
		int velocity_Int = int(abs(velocity * Delta));
		if (bFlagLeft && !bFlagLeftCol)
		{
			x -= velocity_Int + 1;
		}
		else if (!bFlagLeft && !bFlagRightCol)
		{
			x += velocity_Int + 1;
		}

		if (y >= terrainY)
		{
			y = terrainY;
		}
	}

	break;
	case eState_Jump:
		Jump(bFlagLeft, terrainY, Delta);
		break;
	case eState_InteractionMove:
		//x += velocity * Delta;
		//y = y + GRAVITY * AddUpdateDelta;
		//현재 Player의 Y좌표가 Terrain보다 크다면
	case eState_Die:
		y = y + int(GRAVITY * AddUpdateDelta);
		if (y >= terrainY)
		{
			y = terrainY;
		}
		break;
	}
}


EPlayerState Player::GetState()
{
	return state;
}

void Player::Collision(Object* obj)
{
	//Trigger가 아닐경우 수행
	if (!obj->GetCollider()->IsTrigger())
	{
		int objLeft = obj->GetCollider()->GetX() - int(obj->GetCollider()->GetWidth() * 0.5f);
		int objRight = obj->GetCollider()->GetX() + int(obj->GetCollider()->GetWidth() * 0.5f);
		int objTop = obj->GetCollider()->GetY() - int(obj->GetCollider()->GetHeight() * 0.5f);
		int objBottom = obj->GetCollider()->GetY() + int(obj->GetCollider()->GetHeight() * 0.5f);

		int pLeft = GetCollider()->GetX() - int(GetCollider()->GetWidth() * 0.5f);
		int pRight = GetCollider()->GetX() + int(GetCollider()->GetWidth() * 0.5f);
		int pTop = GetCollider()->GetY() - int(GetCollider()->GetHeight() * 0.5f);
		int pBottom = GetCollider()->GetY() + int(GetCollider()->GetHeight() * 0.5f);

		switch (state)
		{
		case eState_Die:
			break;
		case eState_Run:
		{
			if (pLeft < objRight && abs(objRight - pLeft) < width)
			{
				bFlagLeftCol = true;
			}
			else if (pRight > objLeft && abs(pRight - objLeft) < width)
			{
				bFlagRightCol = true;
			}

			int dist = abs(pBottom - objTop);
			if (pBottom > objTop && dist < 50)
			{
				//y = objTop - height * 0.5f;
				bFlagBotmCol = true;
			}
		}
		break;
		case eState_Idle:
		{
			int dist = abs(pBottom - objTop);
			if (pBottom > objTop && dist < 50)
			{
				bFlagBotmCol = true;
				ChangeState(eState_Idle);
			}


			if (GetAsyncKeyState(VK_UP) & 0x8001)
			{
				bFlagJumpStartState = true;
			}
		}
		break;
		case eState_Jump:
		{

			if (pLeft < objRight && abs(objRight - pLeft) < width)
			{
				bFlagLeftCol = true;
				break;
			}
			else if (pRight > objLeft && abs(pRight - objLeft) < width)
			{
				bFlagRightCol = true;
				break;
			}

			int dist = abs(pBottom - objTop);

			if (pBottom > objTop && dist < 10)
			{
				if (!bFlagJumpStartState)
				{
					bFlagBotmCol = true;
					AddDelta = 0.0f;
					ChangeState(eState_Idle);
				}

			}
		}
		break;
		case eState_Interaction:
			break;
		case eState_InteractionMove:
			break;
		default:
			break;
		}
	}
	else
	{
		return;
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
	velocity = 50;
}

void Player::PlayerDie()
{
	ChangeState(eState_Die);
	SoundManager::GetInstance()->Play(ESound::sound_Dead);
}

bool Player::GetbFlagInteraction()
{
	return bFlagInteraction;
}

void Player::SetbFlagInteraction(bool _bFlag)
{
	bFlagInteraction = _bFlag;
}

void Player::MoveReady()
{
	ChangeState(eState_InteractionMove);
}

void Player::SetVelocity(float _velocity)
{
	velocity = _velocity;
}

bool Player::HasInteraction()
{
	return false;
}

void Player::InInteractionDistance(Object* obj)
{
	switch (state)
	{
	case eState_Die:
		break;
	case eState_Run:
		break;
	case eState_Idle:
		if (GetAsyncKeyState(VK_CONTROL) & 0x8001) //상호작용
		{
			ChangeState(eState_Interaction);
		}
		break;
	case eState_Interaction:
		if (GetAsyncKeyState(VK_CONTROL) & 0x8001)
		{

		}
		else
		{
			ChangeState(eState_Idle);
		}
		break;
	case eState_InteractionMove:
		if (GetAsyncKeyState(VK_CONTROL) & 0x8001)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
			{
				x += 1;
				obj->SetX(obj->GetPosX() + 1);
			}
			else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
			{
				x -= 1;
				obj->SetX(obj->GetPosX() - 1);
			}
		}
		else
		{
			ChangeState(eState_Idle);
		}
		break;
	default:
		break;
	}
}

void Player::SetNowColState(bool bFlagState)
{
	bFlagNowCol = bFlagState;
}

bool Player::GetNowColState()
{
	return bFlagNowCol;
}

void Player::InitColState()
{
	bFlagNowCol = false;
	bFlagLeftCol = false;
	bFlagRightCol = false;
	bFlagBotmCol = false;
}

void Player::SetJumpStartState(bool bFlagstate)
{
	bFlagJumpStartState = bFlagstate;
}

