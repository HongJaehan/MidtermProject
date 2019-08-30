#pragma once
#include "Animation.h"

class Animation_Trap_Black :
	public Animation
{
public:
	Animation_Trap_Black();
	~Animation_Trap_Black();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};


