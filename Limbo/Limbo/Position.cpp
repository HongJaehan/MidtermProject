#include "pch.h"
#include "Position.h"

Position::Position()
{

}

Position::~Position()
{

}

Position::Position(float _x, float _y)
{
	x = _x;
	y = _y;
}

Position Position::operator+(const Position& vec)
{
	return Position(x + vec.x, y + vec.y);
}

Position Position::operator-(const Position& vec)
{
	return Position(x - vec.x, y - vec.y);
}

void Position::operator=(const Position& vec)
{
	x = vec.x;
	y = vec.y;
}
void Position::SetX(float _x)
{
	x = _x;
}

float Position::GetX()
{
	return x;
}

void Position::SetY(float _y)
{
	y = _y;
}

float Position::GetY()
{
	return y;
}

void Position::SetXY(float _x, float _y)
{
	x = _x;
	y = _y;
}

Position& Position::GetXY()
{
	return *this;
}

