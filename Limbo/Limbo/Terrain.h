#pragma once
#include "object.h"
class Terrain :public Object 
{
public:
	Terrain();
	~Terrain();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	void Collision(Object*);
	bool HasInteraction();
private:
	Gdiplus::Image* img;
};

