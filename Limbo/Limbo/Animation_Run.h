#pragma once
#include "Animation.h"
class Animation_Run :
	public Animation
{
public:
	Animation_Run();
	~Animation_Run();
	void Update(Gdiplus::Image *img ,float Delta);
	void Begin();
	void End();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

