#pragma once
#include "Animation.h"
class Animation_Die :
	public Animation
{
public:
	Animation_Die();
	~Animation_Die();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
	void CountSceneChange(float Delta);
private:

};

