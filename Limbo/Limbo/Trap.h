#pragma once
#include "object.h"
#include "Animation_Trap.h"

class Trap :
	public Object
{
public:
	Trap();
	Trap(ETag _tag, int _x, int _y, int _width, int _height);
	~Trap();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Rect atlasRect;
	Animation_Trap animation;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool action;
};

