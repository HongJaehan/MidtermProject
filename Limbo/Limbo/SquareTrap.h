#pragma once
#include "object.h"
class SquareTrap :
	public Object
{
public:
	SquareTrap();
	SquareTrap(ETag _tag, int _x, int _y, int _width, int _height);
	~SquareTrap();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Down(float Delta);
	void OnTrap();
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Image* img;
	Gdiplus::Rect* xmlRect;
	int screenPosX;
	int screenPosY;
	bool active;
	int initPosX;
	int initPosY;
	int maxY;
};

