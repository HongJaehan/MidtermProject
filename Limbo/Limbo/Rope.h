#pragma once
#include "object.h"
#include "Animation_Rope.h"

class Rope :
	public Object
{
public:
	Rope();
	Rope(ETag _tag, int _x, int _y, int _width, int _height);
	~Rope();
	virtual void Init()override;
	virtual void Release()override;
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void Collision(Object* obj);
	void Awake();
	void StartAnimation();
	bool HasInteraction();
private:
	Gdiplus::Rect atlasRect;
	Animation_Rope animation;
	int screenPosX;
	int screenPosY;
	int InitPosX;
	int InitPosY;
	bool active;
};

