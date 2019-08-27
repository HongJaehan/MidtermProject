#pragma once
#include "AnimState.h"
class AnimState_InteractionMove :
	public AnimState
{
public:
	AnimState_InteractionMove();
	~AnimState_InteractionMove();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

