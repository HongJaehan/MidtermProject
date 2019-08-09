#pragma once
#include "pch.h"

class Animation
{
public:
	Animation();
	~Animation();
	virtual void Update(Gdiplus::Rect *rect,float Delta) = 0;
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual std::weak_ptr<Gdiplus::Image> GetAtlasImg() = 0;
protected:
	std::weak_ptr<Gdiplus::Image> atlasImg;
	std::vector<Gdiplus::Rect> XMLRect;
	EPlayerState state;
	int frame;
	float addDelta;
};

