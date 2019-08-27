#pragma once
#include "object.h"
#include "AnimState_Trap.h"

class Trap :
	public Object
{
public:
	Trap();
	Trap(ETag _tag, int _x, int _y, int _width, int _height);
	~Trap();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Rect atlasRect;
	AnimState_Trap animState;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool action;
};

