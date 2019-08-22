#pragma once
class ObjectXMLData
{
public:
	ObjectXMLData();
	ObjectXMLData(int _num, int _x, int _y, int _w, int _h);
	~ObjectXMLData();
	int GetNum();
	int GetX();
	int GetY();
	int GetW();
	int GetH();

private:
	int num;
	int x;
	int y;
	int w;
	int h;
};

