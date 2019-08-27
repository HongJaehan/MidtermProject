#pragma once
#include "AnimState.h"

class AnimState_Trap_Black :
	public AnimState
{
public:
	AnimState_Trap_Black();
	~AnimState_Trap_Black();
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	void Init();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};


