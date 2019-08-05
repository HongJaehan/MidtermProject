#include "pch.h"
#include "CVector.h"

CVector::CVector()
{

}

CVector::~CVector()
{

}

CVector::CVector(float _x, float _y)
{
	x = _x;
	y = _y;
}

CVector CVector::operator+(const CVector& vec)
{
	return CVector(x + vec.x, y + vec.y);
}

CVector CVector::operator-(const CVector& vec)
{
	return CVector(x - vec.x, y - vec.y);
}

void CVector::operator=(const CVector& vec)
{
	x = vec.x;
	y = vec.y;
}
void CVector::SetX(float _x)
{
	x = +x;
}

float CVector::GetX()
{
	return x;
}

void CVector::SetY(float _y)
{
	y = +y;
}

float CVector::GetY()
{
	return y;
}

void CVector::SetXY(float _x, float _y)
{
	x = _x;
	y = _y;
}

CVector& CVector::GetXY()
{
	return *this;
}

