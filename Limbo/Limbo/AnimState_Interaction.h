#pragma once
#include "AnimState.h"
class AnimState_Interaction :
	public AnimState
{
public:
	AnimState_Interaction();
	~AnimState_Interaction();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

