#pragma once
#include "AnimState.h"
class AnimState_Rope :
	public AnimState
{
public:
	AnimState_Rope();
	~AnimState_Rope();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

