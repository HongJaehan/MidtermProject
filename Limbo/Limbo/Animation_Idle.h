#pragma once
#include "Animation.h"

class Animation_Idle :
	public Animation
{
public:
	Animation_Idle();
	~Animation_Idle();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

