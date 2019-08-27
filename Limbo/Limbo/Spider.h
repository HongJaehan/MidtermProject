#pragma once
#include "object.h"
#include "AnimState_Spider.h"
class Spider :
	public Object
{
public:
	Spider();
	Spider(ETag _tag, int _x, int _y, int _width, int _height);
	~Spider();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Up(float Delta);
	void Down(float Delta);
	void Awake();
	bool HasInteraction();
private:
	Gdiplus::Image* colImg;
	Gdiplus::Rect atlasRect;
	AnimState_Spider animState;
	int screenPosX;
	int screenPosY;
	bool action;
	ESpiderState state;
	int initPosX;
	int initPosY;
	int maxY;
	bool bFlagSoundOn;
};

