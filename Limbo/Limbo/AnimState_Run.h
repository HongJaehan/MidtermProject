#pragma once
#include "Animation.h"
class AnimState_Run :
	public Animation
{
public:
	AnimState_Run();
	~AnimState_Run();
	virtual void Init()override;
	virtual void Release()override;
	void Update( Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

