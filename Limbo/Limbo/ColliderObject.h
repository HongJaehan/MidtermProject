#pragma once
#include "object.h"

class ColliderObject :
	public Object
{
public:
	ColliderObject();
	ColliderObject(ETag _tag, int _x, int _y, int _width, int _height);
	~ColliderObject();
	void Update(float Delta);
	void Render(Gdiplus::Graphics*);
	bool GetEnable();
	void SetEnable(bool);
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	ETag GetTag();
private:
	int screenPosX;
	int screenPosY;
	Gdiplus::Image* img;
};

