#pragma once
class ObjectXMLData
{
public:
	ObjectXMLData();
	ObjectXMLData(int _num, int _x, int _y, int _w, int _h);
	~ObjectXMLData();
	
private:
	int num;
	int x;
	int y;
	int w;
	int h;
};

