#pragma once
#include "pch.h"
#include <string>
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Control() = 0;
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
	//virtual std::weak_ptr<Gdiplus::Image> GetImage();

protected:
	std::weak_ptr<Gdiplus::Image> img;
	ETag tag;
	Gdiplus::Graphics* MemG;
	Gdiplus::Image* tempImg;
	int width;
	int height;
	//Gdiplus::Image* img;
};
