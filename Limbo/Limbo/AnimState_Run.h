#pragma once
#include "AnimState.h"
class AnimState_Run :
	public AnimState
{
public:
	AnimState_Run();
	~AnimState_Run();
	void Update( Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:
	//std::vector<Gdiplus::Rect> sprites;
};

