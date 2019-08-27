#pragma once
#include "object.h"
#include "AnimState_Trap_Black.h"


class Trap_Black :
	public Object
{
public:
	Trap_Black();
	Trap_Black(ETag _tag, int _x, int _y, int _width, int _height);
	~Trap_Black();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Rect atlasRect;
	AnimState_Trap_Black animState;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool action;
};

