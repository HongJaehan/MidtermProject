#pragma once
#include "object.h"
#include "AnimState_Rope.h"

class Rope :
	public Object
{
public:
	Rope();
	Rope(ETag _tag, int _x, int _y, int _width, int _height);
	~Rope();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	void StartAnimState();
	bool HasInteraction();
private:
	Gdiplus::Image* img;
	Gdiplus::Rect atlasRect;
	AnimState_Rope animState;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool active;
};

