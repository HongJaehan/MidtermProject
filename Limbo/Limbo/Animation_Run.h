#pragma once
#include "Animation.h"
class Animation_Run :
	public Animation
{
public:
	Animation_Run();
	~Animation_Run();
	void Update( Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

