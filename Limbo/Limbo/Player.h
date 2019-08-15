#pragma once
#include "pch.h"
#include "object.h"
#include "Position.h"
#include "common.h"
#include "Animation.h"
#include "Animation_Idle.h"
#include "Animation_Run.h"
#include "Animation_Jump.h"
#include "PlayerControlComponent.h"
#include "BoxCollider2D.h"

class Player :public Object
{
public:
	Player();
	~Player();

	void Update(float);
	void Render(Gdiplus::Graphics*);
	//std::weak_ptr<Gdiplus::Image> GetImage();
	void Jump(bool bFlagLeft,int terrainY,float Delta);
	void AddAnimation(Animation*);
	void ChangeState(EPlayerState);
	EPlayerState GetState();
	bool GetLeftFlag();
	void SetLeftFlag(bool Flag);
	void InitVelocity();
	void PhysicsUpdate(float Delta);
	void CheckCollision(Object &objVec);
	bool GetEnable();
	void SetEnable(bool);
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	ETag GetTag();
	void Collision(Object*);
private:
	//Component
	PlayerControlComponent control;
	//BoxCollider2D collider;
	//Component* collider;

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
};

