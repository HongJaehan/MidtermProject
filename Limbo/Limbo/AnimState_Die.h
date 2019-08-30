#pragma once
#include "Animation.h"
class AnimState_Die :
	public Animation
{
public:
	AnimState_Die();
	~AnimState_Die();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
	void CountSceneChange(float Delta);
private:

};

