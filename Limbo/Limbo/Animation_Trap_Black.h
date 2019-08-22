#pragma once
#include "Animation.h"

class Animation_Trap_Black :
	public Animation
{
public:
	Animation_Trap_Black();
	~Animation_Trap_Black();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};


