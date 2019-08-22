#pragma once
#include "pch.h"
#include "object.h"
#include "Position.h"
#include "common.h"
#include "Animation.h"
#include "Animation_Idle.h"
#include "Animation_Run.h"
#include "Animation_Jump.h"
#include "Animation_Die.h"
#include "Animation_InteractionMove.h"
#include "Animation_Interaction.h"
#include "PlayerControlComponent.h"
#include "BoxCollider2D.h"

class Player :public Object
{
public:
	Player();
	~Player();

	void Update(float);
	void Render(Gdiplus::Graphics*);
	void Jump(bool bFlagLeft,int terrainY,float Delta);
	void AddAnimation(Animation*);
	void ChangeState(EPlayerState);
	EPlayerState GetState();
	bool GetLeftFlag();
	void SetLeftFlag(bool Flag);
	void InitVelocity();
	void PhysicsUpdate(float Delta);
	void Collision(Object*);
	void PlayerDie();

	bool GetbFlagInteraction();
	void SetbFlagInteraction(bool _bFlag);
	void MoveReady();
	void SetVelocity(float _velocity);
	bool HasInteraction();
	void InInteractionDistance(Object* obj);

	void SetNowColState(bool bFlagState);
	bool GetNowColState();
	void InitColState();
	void SetJumpStartState(bool bFlagstate);
private:
	//Component
	PlayerControlComponent control;
	bool bFlagInteraction;

	EPlayerState state;
	int playerScreenPosX;
	int playerScreenPosY;
	float velocity; //player의 속도
//	float speed;  //player의 속도
	bool bFlagLeft; //Left Animation을 하기 위해 
	//std::vector<Gdiplus::Rect> rects; //Player의 애니메이션을 불러오기위해 저장한 Rects값들 즉,xml에 정보
	float jumpInitPosX;
	float jumpInitPosY;
	//std::vector<Gdiplus::PointF> ptList;
	std::vector<Animation*> playerAnimationList;
	Gdiplus::Rect atlasRect;

	bool bFlagNowCol;
	bool bFlagRightCol;
	bool bFlagLeftCol;
	bool bFlagBotmCol;

	bool bFlagJumpStartState;
};

