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
	Position pos; //player의 위치 X,Y
	float speed;  //player의 속도
	bool bFlagLeft; //Left Animation을 하기 위해 
	//std::vector<Gdiplus::Rect> rects; //Player의 애니메이션을 불러오기위해 저장한 Rects값들 즉,xml에 정보
	float jumpInitPosX;
	float jumpInitPosY;
	//std::vector<Gdiplus::PointF> ptList;
	std::vector<Animation*> playerAnimationList;
};

