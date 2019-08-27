#pragma once
#include "AnimState.h"
class AnimState_End :
	public AnimState
{
public:
	AnimState_End();
	~AnimState_End();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};