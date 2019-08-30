#pragma once
#include "Animation.h"
class Animation_Logo :
	public Animation
{
public:
	Animation_Logo();
	~Animation_Logo();
	virtual void Init()override;
	virtual void Release()override;
	void Update(Gdiplus::Rect* rect, float Delta);
	void Begin();
	void End();
	std::weak_ptr<Gdiplus::Image> GetAtlasImg();
private:

};

