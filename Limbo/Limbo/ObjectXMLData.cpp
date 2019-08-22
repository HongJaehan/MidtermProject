#include "pch.h"
#include "ObjectXMLData.h"

ObjectXMLData::ObjectXMLData()
{
}

ObjectXMLData::ObjectXMLData(int _num, int _x, int _y, int _w, int _h)
{
	num = _num;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

ObjectXMLData::~ObjectXMLData()
{
}

int ObjectXMLData::GetNum()
{
	return num;
}

int ObjectXMLData::GetX()
{
	return x;
}

int ObjectXMLData::GetY()
{
	return y;
}

int ObjectXMLData::GetW()
{
	return w;
}

int ObjectXMLData::GetH()
{
	return h;
}
