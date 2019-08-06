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
	Position pos; //player�� ��ġ X,Y
	float speed;  //player�� �ӵ�
	int frame;    //frame��
	std::vector<Gdiplus::Rect> rects; //Player�� �ִϸ��̼��� �ҷ��������� ������ Rects���� ��,xml�� ����
};

