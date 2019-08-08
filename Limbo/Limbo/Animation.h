#pragma once
#include "pch.h"

class Animation
{
public:
	Animation();
	~Animation();
	virtual void Update(Gdiplus::Image *img,float Delta) = 0;
	virtual void Begin() = 0;
	virtual void End() = 0;
protected:
	std::weak_ptr<Gdiplus::Image> atlasImg;
	std::vector<Gdiplus::Rect> XMLRect;
	EPlayerState state;
	int frame;
};

