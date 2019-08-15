#pragma once
#include "pch.h"
#include <string>

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
    virtual bool GetEnable() = 0;
	virtual void SetEnable(bool) = 0;
	virtual int GetPosX() = 0;
	virtual int GetPosY() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual ETag GetTag() = 0;
//	virtual std::weak_ptr<Gdiplus::Image> GetImage();

protected:
	//std::weak_ptr<Gdiplus::Image> *img;
	ETag tag;
	//Gdiplus::Graphics* MemG;
	//Gdiplus::Image* img;
	int x;
	int y;
	int width;
	int height;
	bool enable;
};
