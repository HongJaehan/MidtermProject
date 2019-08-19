#pragma once
#include "Animation.h"
class Animation_Interaction :
	public Animation
{
public:
	Animation_Interaction();
	~Animation_Interaction();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

