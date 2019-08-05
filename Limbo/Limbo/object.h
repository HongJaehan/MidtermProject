#pragma once
#include "pch.h"

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Control() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	Gdiplus::Image* GetImage();

protected:
	Gdiplus::Image* img;
};
