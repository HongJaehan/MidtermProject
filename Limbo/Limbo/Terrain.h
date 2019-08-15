#pragma once
#include "object.h"
class Terrain :public Object 
{
public:
	Terrain();
	~Terrain();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	bool GetEnable();
	void SetEnable(bool);
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	ETag GetTag();
private:
	Gdiplus::Image* img;
};

