#pragma once
#include "pch.h"

class Background
{
public:
	Background();
	Background(int startPosX, std::wstring);
	~Background();
	void Render(Gdiplus::Graphics*,int interval);
	void RenderLeft(Gdiplus::Graphics*, int sizeToDraw);
	void RenderRight(Gdiplus::Graphics*, int sizeToDraw);

	int GetStartPosX();
	int GetEndPosX();
private:
	std::weak_ptr<Gdiplus::Image> img;
	std::wstring imgName;
	int startPosX;
	int endPosX;
};

