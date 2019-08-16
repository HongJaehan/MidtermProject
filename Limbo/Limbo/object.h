#pragma once
#include "pch.h"
#include <string>
#include "BoxCollider2D.h"

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(float) = 0;
	virtual void Render(Gdiplus::Graphics*) = 0;
	virtual void Collision(Object*) = 0;
	bool GetEnable();
	void SetEnable(bool);
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	BoxCollider2D* GetCollider();
	void SetX(int _x);
	void SetY(int _y);
	ETag GetTag();
	bool HasCollider();
//	virtual std::weak_ptr<Gdiplus::Image> GetImage();

protected:
	//std::weak_ptr<Gdiplus::Image> *img;
	BoxCollider2D *collider;
	ETag tag;
	//Gdiplus::Graphics* MemG;
	//Gdiplus::Image* img;
	int x;
	int y;
	int width;
	int height;
	bool enable;
};
