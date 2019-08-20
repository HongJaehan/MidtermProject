#pragma once
#include "object.h"
class Corpse :
	public Object
{
public:
	Corpse();
	Corpse(ETag _tag, int _x, int _y, int _width, int _height);
	~Corpse();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Init();
private:

	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	Gdiplus::Image* img;
	Gdiplus::Rect* xmlRect;
};

