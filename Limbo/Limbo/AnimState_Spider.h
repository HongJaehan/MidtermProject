#pragma once
#include "AnimState.h"
class AnimState_Spider :
	public AnimState
{
public:
	AnimState_Spider();
	~AnimState_Spider();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, ESpiderState);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

