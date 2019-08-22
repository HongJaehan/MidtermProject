#pragma once
#include "Animation.h"

class Animation_Trap :
	public Animation
{
public:
	Animation_Trap();
	~Animation_Trap();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

