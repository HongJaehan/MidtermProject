#pragma once
#include "Animation.h"
class Animation_Jump :
	public Animation
{
public:
	Animation_Jump();
	~Animation_Jump();
	void Update(Gdiplus::Image *img ,float Delta);
	void Begin();
	void End();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

