#pragma once
#include "object.h"
#include "Animation_Trap_Black.h"


class Trap_Black :
	public Object
{
public:
	Trap_Black();
	Trap_Black(ETag _tag, int _x, int _y, int _width, int _height);
	~Trap_Black();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Rect atlasRect;
	Animation_Trap_Black animation;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool action;
};

