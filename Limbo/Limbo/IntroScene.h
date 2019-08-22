#pragma once
#include "Scene.h"
#include "Animation_Logo.h"
#include "MCISound.h"

class IntroScene :public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Init();
	void Update(float);
	void Render(Gdiplus::Graphics*);
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

