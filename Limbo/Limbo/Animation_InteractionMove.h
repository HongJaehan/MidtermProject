#pragma once
#include "Animation.h"
class Animation_InteractionMove :
	public Animation
{
public:
	Animation_InteractionMove();
	~Animation_InteractionMove();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

