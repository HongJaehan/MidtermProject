#pragma once
#include "object.h"
class Spider :
	public Object
{
public:
	Spider();
	Spider(ETag _tag, int _x, int _y, int _width, int _height);
	~Spider();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Up(float Delta);
	void Down(float Delta);
private:
	Gdiplus::Image* colImg;
	Gdiplus::Rect atlasRect;
	Animation_Trap animation;
	int screenPosX;
	int screenPosY;
	bool action;
};

