#pragma once
#include "Animation.h"
class AnimState_Interaction :
	public Animation
{
public:
	AnimState_Interaction();
	~AnimState_Interaction();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

