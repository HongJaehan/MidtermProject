#pragma once
#include "Animation.h"
class Animation_Jump :
	public Animation
{
public:
	Animation_Jump();
	~Animation_Jump();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

