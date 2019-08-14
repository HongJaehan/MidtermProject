#pragma once
#include "Scene.h"


class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	void Init();
	void Update(float);
	void Render(Gdiplus::Graphics*);
};