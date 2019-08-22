#include "pch.h"
#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D()
{

}

BoxCollider2D::BoxCollider2D(int _x, int _y, int _width, int _height, bool _trigger)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	trigger = _trigger;
}

BoxCollider2D::~BoxCollider2D()
{
}

int BoxCollider2D::GetX()
{
	return x;
}

int BoxCollider2D::GetY()
{
	return y;
}

int BoxCollider2D::GetWidth()
{
	return width;
}

int BoxCollider2D::GetHeight()
{
	return height;
}

void BoxCollider2D::SetX(int _x)
{
	x = _x;
}

void BoxCollider2D::SetY(int _y)
{
	y = _y;
}

void BoxCollider2D::SetWidth(int _width)
{
	width = _width;
}

void BoxCollider2D::SetHeight(int _height)
{
	height = _height;
}

bool BoxCollider2D::IsTrigger()
{
	return trigger;
}
