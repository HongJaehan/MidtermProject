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
	if (GetAsyncKeyState(VK_LEFT) & 0x8001) //왼쪽 달리기
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
			if (GetAsyncKeyState(VK_UP) & 0x8001)
			{
				player.ChangeState(eState_Jump);
				player.SetJumpStartState(true);
				break;
			}
			if (!player.GetLeftFlag()) { player.InitVelocity(); }//현재 왼쪽으로 달리고있는 중이었다면 speed를 0으로 초기화한다.
			player.SetLeftFlag(true);
			break;
		case eState_Interaction:
			break;
		case eState_InteractionMove:
			player.SetVelocity(-70);
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001) //오른쪽 달리기
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
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				player.ChangeState(eState_Jump);
				player.SetJumpStartState(true);
				break;
			}
			if (player.GetLeftFlag()) { player.InitVelocity(); }//현재 왼쪽으로 달리고있는 중이었다면 speed를 0으로 초기화한다.
			player.SetLeftFlag(false);
			break;
		case eState_Interaction:
			break;
		case eState_InteractionMove:
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
			{
				player.SetVelocity(70);
			}
			else
			{

			}
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001) //상호작용
	{
		switch (player.GetState())
		{
		case eState_Idle:
			player.ChangeState(eState_Jump);
			player.SetJumpStartState(true);
			break;
		}
	}
	else //Idle
	{
		if (player.GetState()!= eState_Jump && player.GetState()!= eState_Die && player.GetState() != eState_Interaction && player.GetState() != eState_InteractionMove)
		{
			player.ChangeState(eState_Idle);
			player.InitVelocity();
		}
	}
}