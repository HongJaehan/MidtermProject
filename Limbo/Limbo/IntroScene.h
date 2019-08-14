#pragma once
#include "Scene.h"

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
};

