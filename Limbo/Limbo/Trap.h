#pragma once
#include "object.h"
#include "Animation_Trap.h"

class Trap :
	public Object
{
public:

	Trap();
	Trap(ETag _tag, int _x, int _y, int _width, int _height);
	~Trap();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
private:
	Gdiplus::Image* colImg;
	Gdiplus::Rect atlasRect;
	Animation_Trap animation;
	int screenPosX;
	int screenPosY;
	bool action;
};

