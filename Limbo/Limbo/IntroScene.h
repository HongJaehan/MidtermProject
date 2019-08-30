#pragma once
#include "Scene.h"
#include "Animation_Logo.h"
#include "MCISound.h"

class IntroScene :public Scene
{
public:
	IntroScene();
	~IntroScene();

	virtual void Init()override;
	virtual void Release()override;
	virtual void Update(float)override;
	virtual void Render(Gdiplus::Graphics*)override;
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

	/*MCISound* sound;
	HWND hWnd;
	DWORD Sound1, Sound2;*/
};

