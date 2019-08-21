#pragma once
#include "object.h"
class Niddle :
	public Object
{
public:
	Niddle();
	Niddle(ETag _tag, int _x, int _y, int _width, int _height);
	~Niddle();

	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object*);
	bool HasInteraction();
private:
	int screenPosX;
	int screenPosY;
	Gdiplus::Image* img;
};

