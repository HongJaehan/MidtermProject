#pragma once
#include "AnimState.h"
class AnimState_Logo :
	public AnimState
{
public:
	AnimState_Logo();
	~AnimState_Logo();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

