#include "pch.h"
#include "Player.h"
#include "MainFrm.h"

#define MAX_SPEED 8
#define INIT_SPEED 0
#define PI 3.14

Player::Player()
{
	img = AssetManager::GetInstance()->GetImage(TEXT("Player.png"));
	tempImg = new Gdiplus::Image(TEXT("player.png"));
	tag = ePlayer;
	state = eState_Idle;
	bFlagLeft = false;
	speed = 0.1f;
	width = define.playerWidth;
	height = define.playerHeight;
	
	//�ӽ� ó��
 	pos.SetX(0 + width*0.5);
	pos.SetY(800 - height);

	//����� ����
	//pos.SetX(GameManager::GetInstance()->GetCheckPoint().first + width * 0.5);
	//pos.SetY(GameManager::GetInstance()->GetCheckPoint().first - height);

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

	if (GetAsyncKeyState(VK_LEFT) & 0x8001) //���� �޸���
	{
		switch (state)
		{
		case eState_Idle:
			state = eState_Run;
			frame = 0;
			bFlagLeft = true;
			break;
		case eState_Jump:
			//���� ���ֱ�
			break;
		case eState_Run:
			if (!bFlagLeft) { speed = 0; }//���� ���������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			bFlagLeft = true;
			pos.SetX(pos.GetX() - speed );
			break;
		case eState_Interaction:
			break;
		default :
			break;
		}
		
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001) //������ �޸���
	{
		switch (state)
		{
		case eState_Idle:
			state = eState_Run;
			frame = 0;
			bFlagLeft = false;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (bFlagLeft) { speed = 0; }//���� �������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			bFlagLeft = false;
			pos.SetX(pos.GetX() + speed );
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x1001) //����
	{
		switch (state)
		{
		case eState_Idle:
			state = eState_Jump;
			break;
		case eState_Jump:
			break;
		case eState_Run:
			state = eState_Jump;
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_CONTROL) & 0x8001) //��ȣ�ۿ�
	{

	}
	else //Idle
	{
		state = eState_Idle;
		speed = INIT_SPEED;
	}
}

void Player::Update(float Delta)
{
	switch (state)
	{
	case eState_Idle:
		speed = INIT_SPEED; //�ӵ� �ʱ�ȭ
		break;
	case eState_Run:
		if (speed < MAX_SPEED) //���ǵ尡 �ְ� �ӵ��� ���� ������
		{
			speed += 1.0f;
		}
		break;
	case eState_Jump:
		pos.SetXY(speed * cos(45 * (PI / 180)) * Delta * 0.01f ,
			speed *sin(45*(PI/180)) * Delta * 0.01f);
		break;
	}
}

void Player::Render(Gdiplus::Graphics* MemG)
{
	//Player�� ũ��
	Gdiplus::Rect rect(0,0,width,height);
	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	temp.DrawImage(tempImg,rect);

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(pos.GetX(), pos.GetY(), width, height);

	//���� ���������̶�� bit�� �¿� ���������ش�.
	if (bFlagLeft)
	{
		bm.RotateFlip(Gdiplus::Rotate180FlipY);
	}
	MemG->DrawImage(&bm, screenPosRect);
	
	//temp.DrawImage(img.lock,rect, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height,
	//	Gdiplus::Unit::UnitPixel,nullptr, 0, nullptr);

	//MemG->DrawImage(&bm, rect);
	//MemG->DrawImage()
}