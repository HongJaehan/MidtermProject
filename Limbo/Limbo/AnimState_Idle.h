#pragma once
#include "AnimState.h"

class AnimState_Idle :
	public AnimState
{
public:
	AnimState_Idle();
	~AnimState_Idle();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

