#pragma once
#include "pch.h"
#include <string>

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Control() = 0;
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
//	virtual std::weak_ptr<Gdiplus::Image> GetImage();

protected:
	//std::weak_ptr<Gdiplus::Image> img;
	ETag tag;
	Gdiplus::Graphics* MemG;
	std::weak_ptr<Gdiplus::Image> img;
	//Gdiplus::Image* img;
	int width;
	int height;
	bool enable;
	//Gdiplus::Image* img;
};