#pragma once
#include "Animation.h"
class Animation_End :
	public Animation
{
public:
	Animation_End();
	~Animation_End();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};