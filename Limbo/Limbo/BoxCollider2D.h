#pragma once
#include "ColliderComponent.h"
class BoxCollider2D :
	public ColliderComponent
{
public:
	BoxCollider2D();
	BoxCollider2D(int _x,int _y, int _width, int _height, bool _trigger);
	~BoxCollider2D();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetX(int);
	void SetY(int);
	void SetWidth(int _width);
	void SetHeight(int _height);
	bool IsTrigger();

private:
	int x;
	int y;
	int width;
	int height;
	bool trigger;
};

