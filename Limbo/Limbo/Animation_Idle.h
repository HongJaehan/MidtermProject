#pragma once
#include "Animation.h"

class Animation_Idle :
	public Animation
{
public:
	Animation_Idle();
	~Animation_Idle();
	void Update(Gdiplus::Image* img, float Delta);
	void Begin();
	void End();
private:
};

