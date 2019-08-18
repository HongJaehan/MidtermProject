#include "pch.h"
#include "PlayerControlComponent.h"


PlayerControlComponent::PlayerControlComponent()
{

}

PlayerControlComponent::~PlayerControlComponent()
{

}

void PlayerControlComponent::Update(Player& player)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001) //���� �޸���
	{
		switch (player.GetState())
		{
		case eState_Idle:
			player.ChangeState(eState_Run);
			player.SetLeftFlag(true);
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				player.ChangeState(eState_Jump);
				break;
			}
			if (!player.GetLeftFlag()) { player.InitVelocity(); }//���� �������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			player.SetLeftFlag(true);
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001) //������ �޸���
	{
		switch (player.GetState())
		{
		case eState_Idle:
			player.ChangeState(eState_Run);
			player.SetLeftFlag(false);
			break;
		case eState_Jump:
			break;
		case eState_Run:
			if (GetAsyncKeyState(VK_UP) & 0x1001)
			{
				player.ChangeState(eState_Jump);
				break;
			}
			if (player.GetLeftFlag()) { player.InitVelocity(); }//���� �������� �޸����ִ� ���̾��ٸ� speed�� 0���� �ʱ�ȭ�Ѵ�.
			player.SetLeftFlag(false);
			break;
		case eState_Interaction:
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001) //��ȣ�ۿ�
	{
		switch (player.GetState())
		{
		case eState_Idle:
			player.ChangeState(eState_Jump);
			break;
		}
	}
	else if (GetAsyncKeyState(VK_CONTROL) & 0x8001) //��ȣ�ۿ�
	{

	}
	else //Idle
	{
		if (player.GetState()!= eState_Jump && player.GetState()!= eState_Die)
		{
			player.ChangeState(eState_Idle);
			player.InitVelocity();
		}
	}
}