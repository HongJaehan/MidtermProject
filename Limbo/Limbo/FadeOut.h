#pragma once
#include "object.h"
class FadeOut :public Object
{
public:
	FadeOut();
	~FadeOut();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	void Collision(Object*);
	void OnFadeOutEvent();
	bool HasInteraction();
private:
	std::weak_ptr<Gdiplus::Image> fadeOutImg;

	Gdiplus::Bitmap* bm2;
	Gdiplus::ImageAttributes* imgAttr;
	float AddDelta;
	float rTransparency;
};

