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
private:
	//Component
	PlayerControlComponent control;
	//Component* collider;

	EPlayerState state;
	Position pos; //player�� ��ġ X,Y
	int playerScreenPosX;
	int playerScreenPosY;
	float velocity; //player�� �ӵ�
//	float speed;  //player�� �ӵ�
	bool bFlagLeft; //Left Animation�� �ϱ� ���� 
	//std::vector<Gdiplus::Rect> rects; //Player�� �ִϸ��̼��� �ҷ��������� ������ Rects���� ��,xml�� ����
	float jumpInitPosX;
	float jumpInitPosY;
	//std::vector<Gdiplus::PointF> ptList;
	std::vector<Animation*> playerAnimationList;
	Gdiplus::Rect atlasRect;
};

