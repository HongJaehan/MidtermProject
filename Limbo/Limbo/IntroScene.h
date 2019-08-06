#pragma once
#include "Scene.h"

class IntroScene :public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Init();
	void Control();
	void Update(int);
	void Render(Gdiplus::Graphics*);
};

