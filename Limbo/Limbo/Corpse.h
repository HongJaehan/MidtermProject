#pragma once
#include "object.h"
class Corpse :
	public Object
{
public:
	Corpse();
	Corpse(ETag _tag, int _x, int _y, int _width, int _height);
	~Corpse();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	bool HasInteraction();
	void CutRope();
private:
	int screenPosX;
	int screenPosY;
	int initPosX;
	int initPosY;
	Gdiplus::Image* img;
	Gdiplus::Rect* xmlRect;
	bool bFlagOnEvent;
	int cutRopeEventPos;
};

