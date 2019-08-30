#pragma once
#include "Scene.h"
#include "Animation_End.h"

class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	virtual void Init()override;
	virtual void Release()override;
	virtual void Update(float)override;
	virtual void Render(Gdiplus::Graphics*)override;

	void SendKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	std::weak_ptr<Gdiplus::Image> backgroundImg;
	std::weak_ptr<Gdiplus::Image> fadeOutImg;
	std::weak_ptr<Gdiplus::Image> LOGOImg;

	Gdiplus::Bitmap* bm2;
	Gdiplus::ImageAttributes* imgAttr;
	float AddDelta;
	float rTransparency;

	Animation* IntroAnimation;
	Gdiplus::Rect atlasRect;
};