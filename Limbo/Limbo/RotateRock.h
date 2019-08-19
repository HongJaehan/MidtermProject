#pragma once
#include "object.h"
class RotateRock :
	public Object
{
public:
	RotateRock();
	RotateRock(ETag _tag, int _x, int _y, int _width, int _height);
	~RotateRock();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object*);
	void Init();
private:
	int screenPosX;
	int screenPosY;
	int initPosX;
	int initPosY;
	Gdiplus::Image* img;
	Gdiplus::Bitmap* bm;
	ERotateRockState state;
	
};

