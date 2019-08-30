#pragma once
#include "object.h"

class ColliderObject :
	public Object
{
public:
	ColliderObject();
	ColliderObject(ETag _tag, int _x, int _y, int _width, int _height);
	~ColliderObject();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics*);
	void Collision(Object*);
	bool HasInteraction();
private:
	int screenPosX;
	int screenPosY;
	Gdiplus::Image* img;
};

