#pragma once
#include "Animation.h"
class Animation_Rope :
	public Animation
{
public:
	Animation_Rope();
	~Animation_Rope();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Update(Gdiplus::Rect* rect, float Delta, bool action);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

