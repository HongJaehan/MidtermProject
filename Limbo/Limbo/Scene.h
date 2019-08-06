#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Control() = 0;
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;

};

