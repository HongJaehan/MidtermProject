#pragma once
#include "AnimState.h"
class AnimState_Die :
	public AnimState
{
public:
	AnimState_Die();
	~AnimState_Die();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
	void CountSceneChange(float Delta);
private:

};

