#pragma once
#include "Animation.h"
class Animation_Spider :
	public Animation
{
public:
	Animation_Spider();
	~Animation_Spider();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, ESpiderState);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

