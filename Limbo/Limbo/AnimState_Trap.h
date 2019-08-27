#pragma once
#include "AnimState.h"

class AnimState_Trap :
	public AnimState
{
public:
	AnimState_Trap();
	~AnimState_Trap();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

