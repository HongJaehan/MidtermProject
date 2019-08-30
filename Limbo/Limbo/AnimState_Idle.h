#pragma once
#include "Animation.h"

class AnimState_Idle :
	public Animation
{
public:
	AnimState_Idle();
	~AnimState_Idle();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
};

