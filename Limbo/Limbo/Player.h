#pragma once
#include "object.h"
#include "Position.h"
#include "common.h"

class Player :public Object
{
public:
	Player();
	~Player();

	void Control();
	void Update(int);
	void Render(Gdiplus::Graphics*);
	std::weak_ptr<Gdiplus::Image> GetImage();

private:
	ePlayerState state;
	Position pos; //player의 위치 X,Y
	float speed;  //player의 속도
	int frame;    //frame값
	std::vector<Gdiplus::Rect> rects; //Player의 애니메이션을 불러오기위해 저장한 Rects값들 즉,xml에 정보
};

