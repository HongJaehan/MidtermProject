#include "pch.h"
#include "object.h"

Object::Object()
{

}

Object::~Object()
{

}

bool Object::HasCollider()
{
	if (collider != nullptr)
	{
		return true;
	}
	else
		return false;
}

bool Object::GetEnable()
{
	return enable;
}

void Object::SetEnable(bool bFlag)
{
	enable = bFlag;
}

int Object::GetPosX()
{
	return x;
}

int Object::GetPosY()
{
	return y;
}

int Object::GetWidth()
{
	return width;
}

int Object::GetHeight()
{
	return height;
}

BoxCollider2D* Object::GetCollider()
{
	return collider;
}

void Object::SetX(int _x)
{
	x = _x;
}

void Object::SetY(int _y)
{
	y = _y;
}

ETag Object::GetTag()
{
	return tag;
}
