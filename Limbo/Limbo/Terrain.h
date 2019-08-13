#pragma once
#include "object.h"
class Terrain :public Object 
{
public:
	Terrain();
	~Terrain();
	void Control();
	void Update(float);
	void Render(Gdiplus::Graphics*);
private:
	Gdiplus::Image* img;
};

