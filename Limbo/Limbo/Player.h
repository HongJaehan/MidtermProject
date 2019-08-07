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
	void Update(float);
	void Render(Gdiplus::Graphics*);
	std::weak_ptr<Gdiplus::Image> GetImage();

private:
	EPlayerState state;
	Position pos; //player�� ��ġ X,Y
	float speed;  //player�� �ӵ�
	int frame;    //frame��
	bool bFlagLeft; //Left Animation�� �ϱ� ���� 
	std::vector<Gdiplus::Rect> rects; //Player�� �ִϸ��̼��� �ҷ��������� ������ Rects���� ��,xml�� ����
	float jumpInitPosX;
	float jumpInitPosY;
	std::vector<Gdiplus::PointF> ptList;
};

