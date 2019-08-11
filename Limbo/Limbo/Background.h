#pragma once
#include "pch.h"

class Background
{
public:
	Background();
	Background(int x, std::wstring);
	~Background();
	void Render(Gdiplus::Graphics*);
private:
	std::wstring imgName;
	int startPosX;
	int endPosX;
};

