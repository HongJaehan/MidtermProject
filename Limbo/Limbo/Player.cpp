#include "pch.h"
#include "Player.h"
#include "MainFrm.h"

#define MAX_SPEED 3
#define INIT_SPEED 0
#define PI (3.1415926535897932f)
#define GRAVITY 75
#define DEGTORAD(X) (X * (PI / 180))

Player::Player()
{
	//img = AssetManager::GetInstance()->GetImage(TEXT("Player.png"));
	//tempImg = new Gdiplus::Image(TEXT("player.png"));
	tag = ePlayer;
	state = eState_Idle;
	bFlagLeft = false;
	speed = 0.1f;
	width = defines.playerWidth;
	height = defines.playerHeight;
	enable = true;

	//AnimationList에 애니메이션을 추가해준다.
	AddAnimation(new Animation_Idle());
	AddAnimation(new Animation_Run());
	AddAnimation(new Animation_Jump());

	//임시 처리
 	pos.SetX(0 + width*0.5);
	pos.SetY(800 - height);

	//사용할 생각
	//pos.SetX(GameManager::GetInstance()->GetCheckPoint().first + width * 0.5);
	//pos.SetY(GameManager::GetInstance()->GetCheckPoint().first - height);

	//MemG = 
}

Player::~Player()
{

}
//
//std::weak_ptr<Gdiplus::Image> Player::GetImage()
//{
//	//return img;
//}

void Player::Control()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8001) //왼쪽 달리기
	{
		switch (state)
		{
		case eState_Idle:
			state = eState_Run;
			bFlagLeft = true;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				state = eState_Jump;
				jumpInitPosX = pos.GetX();
				jumpInitPosY = pos.GetY();
				break;
			}
			if (!bFlagLeft) { speed = 0; }//현재 왼쪽으로 달리고있는 중이었다면 speed를 0으로 초기화한다.
			bFlagLeft = true;
			pos.SetX(pos.GetX() - speed);
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001) //오른쪽 달리기
	{
		switch (state)
		{
		case eState_Idle:
			state = eState_Run;
			bFlagLeft = false;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				state = eState_Jump;
				jumpInitPosX = pos.GetX();
				jumpInitPosY = pos.GetY();
				break;
			}
			if (bFlagLeft) { speed = 0; }//현재 왼쪽으로 달리고있는 중이었다면 speed를 0으로 초기화한다.
			bFlagLeft = false;
			pos.SetX(pos.GetX() + speed );
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001) //상호작용
	{
		switch(state)
		{
		case eState_Idle:
			state = eState_Jump;
			break;
		}
	}
	else if (GetAsyncKeyState(VK_CONTROL) & 0x8001) //상호작용
	{

	}
	else //Idle
	{
		if (state != eState_Jump)
		{
			state = eState_Idle;
			speed = INIT_SPEED;
		}
	}
}



static float AddDelta = 0;

void Player::Update(float Delta)
{
	switch (state)
	{
	case eState_Idle:
		speed = INIT_SPEED; //속도 초기화
		break;
	case eState_Run:
		if (speed < MAX_SPEED) //스피드가 최고 속도를 넘지 않으면
		{
			speed += Delta * 10;
		}
		break;
	case eState_Jump:
		Jump(bFlagLeft, Delta);
		break;
#pragma region MyRegion
		//pos.SetY(jumpInitPosY + speed * cos(DEGTORAD(-45)) - 0.5f * GRAVITY * Delta * Delta);
	//pos.SetX(jumpInitPosX + 10 * cos(DEGTORAD(-45)) * Delta);
	//AddDelta += Delta;
	//float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
	//pos.SetX(pos.GetX() +  speed * 100 * Delta);
	//pos.SetY(pos.GetY() + (-400.f * Delta) + AddVal);

	//예시
	/*if (pos.GetY() >= jumpInitPosY)
	{
		state = eState_Idle;
		pos.SetY(jumpInitPosY);
		AddDelta = 0;
	}*/
	//jumpInitPosX += 10.f * speed * Delta;
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
			//pos.SetX(X + speed * cos(DEGTORAD(45)) * Delta);
			//pos.SetY(Y + (-1000 * Delta) + AddVal);
#pragma endregion
	}
		//현재 Animation의 image를 XML정보에 맞춰 저장해줌.
		playerAnimationList[state]->Update(&atlasRect, Delta);
}

void Player::Render(Gdiplus::Graphics* _MemG)
{
	//auto atlasImg = img.lock();
	//Player의 크기
	Gdiplus::Rect rect(0,0,width,height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(),rect, atlasRect.X , atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//temp.DrawImage(tempImg,rect);

	//Gdiplus::Color color;
	//bm.GetPixel(60, 60, &color);
	//int x = color.GetAlpha();
	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(pos.GetX(), pos.GetY(), width, height);

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


void Player::Jump(bool bFlagLeft,float Delta)
{
		AddDelta += Delta;
		float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
		if (bFlagLeft)
		{
			pos.SetX(pos.GetX() - speed * 100 * Delta);
		}
		else
		{
			pos.SetX(pos.GetX() + speed * 100 * Delta);
		}
		pos.SetY(pos.GetY() + (-400.f * Delta) + AddVal);

		//예시
		if (pos.GetY() >= jumpInitPosY)
		{
			state = eState_Idle;
			pos.SetY(jumpInitPosY);
			AddDelta = 0;
			speed = 0;
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