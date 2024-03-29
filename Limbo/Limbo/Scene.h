#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
	ESceneTag tag;
};

