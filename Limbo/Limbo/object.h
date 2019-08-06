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
	virtual void Update(int) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
	//virtual std::weak_ptr<Gdiplus::Image> GetImage();

protected:
	std::weak_ptr<Gdiplus::Image> img;
	eTag tag;
	Gdiplus::Graphics* MemG;
	Gdiplus::Image* tempImg;
	//Gdiplus::Image* img;
};
