#pragma once
#include "object.h"
#include "Position.h"

class Player :public Object
{
public:
	Player();
	~Player();

	void Control();
	void Update();
	void Render();
	Gdiplus::Image* GetImage();

private:
	Position pos;
};

