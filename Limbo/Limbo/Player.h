#pragma once
#include "object.h"
#include "Position.h"
#include "common.h"
#include "Animation.h"
#include "Animation_Idle.h"
#include "Animation_Run.h"
#include "Animation_Jump.h"

class Player :public Object
{
public:
	Player();
	~Player();

	void Control();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	//std::weak_ptr<Gdiplus::Image> GetImage();
	void Jump(bool bFlagLeft,float Delta);
	void AddAnimation(Animation*);

private:
	EPlayerState state;
	Position pos; //player�� ��ġ X,Y
	float speed;  //player�� �ӵ�
	bool bFlagLeft; //Left Animation�� �ϱ� ���� 
	//std::vector<Gdiplus::Rect> rects; //Player�� �ִϸ��̼��� �ҷ��������� ������ Rects���� ��,xml�� ����
	float jumpInitPosX;
	float jumpInitPosY;
	//std::vector<Gdiplus::PointF> ptList;
	std::vector<Animation*> playerAnimationList;
};

