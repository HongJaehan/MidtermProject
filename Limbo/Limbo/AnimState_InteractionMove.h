#pragma once
#include "Animation.h"
class AnimState_InteractionMove :
	public Animation
{
public:
	AnimState_InteractionMove();
	~AnimState_InteractionMove();
	void Init();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

