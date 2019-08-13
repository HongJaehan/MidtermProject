#include "pch.h"
#include "Player.h"
#include "MainFrm.h"

#define MAX_SPEED 2.5f
#define INIT_SPEED 0
#define PI (3.1415926535897932f)
#define GRAVITY 7
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

	//AnimationList�� �ִϸ��̼��� �߰����ش�.
	AddAnimation(new Animation_Idle());
	AddAnimation(new Animation_Run());
	AddAnimation(new Animation_Jump());

	int screenSizeWidth = defines.screenSizeX;
 	pos.SetX(screenSizeWidth*0.5f);
	pos.SetY(800);

	playerScreenPosX = pos.GetX() - width * 0.5;
	playerScreenPosY = pos.GetY() - height;


	//����� ����
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

void Player::Control()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001) //���� �޸���
	{
		switch (state)
		{
		case eState_Idle:
			ChangeState(eState_Run);
			bFlagLeft = true;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				ChangeState(eState_Jump);
				jumpInitPosX = pos.GetX();
				jumpInitPosY = pos.GetY();
				break;
			}
			if (!bFlagLeft) { speed = 0; }//���� �������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			bFlagLeft = true;
			//pos.SetX(pos.GetX() - speed);
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001) //������ �޸���
	{
		switch (state)
		{
		case eState_Idle:
			ChangeState(eState_Run);
			bFlagLeft = false;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				ChangeState(eState_Jump);
				jumpInitPosX = pos.GetX();
				jumpInitPosY = pos.GetY();
				break;
			}
			if (bFlagLeft) { speed = 0; }//���� �������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			bFlagLeft = false;
			//pos.SetX(pos.GetX() + speed );
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001) //��ȣ�ۿ�
	{
		switch(state)
		{
		case eState_Idle:
			ChangeState(eState_Jump);
			break;
		}
	}
	else if (GetAsyncKeyState(VK_CONTROL) & 0x8001) //��ȣ�ۿ�
	{

	}
	else //Idle
	{
		if (state != eState_Jump)
		{
			ChangeState(eState_Idle);
			speed = INIT_SPEED;
		}
	}
}



static float AddDelta = 0;

static float AddUpdateDelta = 0;
void Player::Update(float Delta)
{
	AddUpdateDelta += Delta;

	if (AddUpdateDelta > 0.3f)
	{
		AddUpdateDelta = 0;
	}
	//GameManager�� ���� Player�� X��ǥ�� ���� Terrain�� Y ������ �޾ƿ´�.
	int terrainY = GameManager::GetInstance()->GetTerrainData(pos.GetX()+width*0.5f);

	switch (state)
	{
	case eState_Idle:
		pos.SetY(pos.GetY() + AddUpdateDelta * GRAVITY);
		speed = INIT_SPEED; //�ӵ� �ʱ�ȭ
		//���� Player�� Y��ǥ�� Terrain���� ũ�ٸ�
		if (pos.GetY() >= terrainY)
		{
			pos.SetY(terrainY);
		}
		break;
	case eState_Run:
		if (speed < MAX_SPEED) //���ǵ尡 �ְ� �ӵ��� ���� ������
		{
			speed += AddUpdateDelta;
		}
		if (bFlagLeft)
		{
			pos.SetX(pos.GetX() - speed * AddUpdateDelta);
		}
		else
		{
			pos.SetX(pos.GetX() + speed * AddUpdateDelta);
		}
		pos.SetY(pos.GetY() + AddUpdateDelta * GRAVITY);
		//���� Player�� Y��ǥ�� Terrain���� ũ�ٸ�
		if (pos.GetY() >= terrainY)
		{
			pos.SetY(terrainY);
		}
		break;
	case eState_Jump:
		Jump(bFlagLeft,terrainY, Delta);
		break;
#pragma region MyRegion
		//pos.SetY(jumpInitPosY + speed * cos(DEGTORAD(-45)) - 0.5f * GRAVITY * Delta * Delta);
	//pos.SetX(jumpInitPosX + 10 * cos(DEGTORAD(-45)) * Delta);
	//AddDelta += Delta;
	//float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
	//pos.SetX(pos.GetX() +  speed * 100 * Delta);
	//pos.SetY(pos.GetY() + (-400.f * Delta) + AddVal);

	//����
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
		//���� Animation�� image�� XML������ ���� ��������.
		playerAnimationList[state]->Update(&atlasRect,Delta);
}

void Player::Render(Gdiplus::Graphics* _MemG)
{
	//Player�� ũ��
	Gdiplus::Rect rect(0,0,width,height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(),rect, atlasRect.X , atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	Gdiplus::Rect screenPosRect(defines.screenSizeX/2 - width*0.5f,pos.GetY()-height+10, width, height);

	//���� ���������̶�� bit�� �¿� ���������ش�.
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


void Player::Jump(bool bFlagLeft,int terrainY,float Delta)
{
		AddDelta += Delta;
		float AddVal = (0.5f * GRAVITY * AddDelta * AddDelta);
		if (bFlagLeft)
		{
			pos.SetX(pos.GetX() - speed * 130 * Delta);
		}
		else
		{
			pos.SetX(pos.GetX() + speed * 130 * Delta);
		}
		pos.SetY(pos.GetY() + (-400.f * Delta) + AddVal);

		if (pos.GetY() > terrainY)
		{
			pos.SetY(terrainY);
			ChangeState(eState_Idle);
			AddDelta = 0.0f;
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