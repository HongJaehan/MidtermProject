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
	void SetX(int _x);
	void SetY(int _y);
	ETag GetTag();
	BoxCollider2D* GetCollider();
	bool HasCollider();
	
	virtual bool HasInteraction() = 0;
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
