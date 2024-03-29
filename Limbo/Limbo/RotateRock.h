#pragma once
#include "object.h"
class RotateRock :
	public Object
{
public:
	RotateRock();
	RotateRock(ETag _tag, int _x, int _y, int _width, int _height);
	~RotateRock();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object*);
	void Awake();
	bool HasInteraction();
private:
	int screenPosX;
	int screenPosY;
	int initPosX;
	int initPosY;
	Gdiplus::Image* img;
	ERotateRockState state;
	Gdiplus::Bitmap* bm;
	Gdiplus::Rect* xmlRect;
	int minX;
	int rotateNum;
};

