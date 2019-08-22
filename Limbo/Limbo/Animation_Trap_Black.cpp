#include "pch.h"
#include "Animation_Trap_Black.h"

Animation_Trap_Black::Animation_Trap_Black()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("trap.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\trap_Black.xml");
}

Animation_Trap_Black::~Animation_Trap_Black()
{
	atlasImg.reset();
}

void Animation_Trap_Black::Update(Gdiplus::Rect* rect, float Delta)
{

}

void Animation_Trap_Black::Update(Gdiplus::Rect* rect, float Delta, bool action)
{
	if (!action)
	{
		rect->X = XMLRect[0].X;
		rect->Y = XMLRect[0].Y;
		rect->Width = XMLRect[0].Width;
		rect->Height = XMLRect[0].Height;
		return;
	}

	//addDelta += Delta;

	//if (addDelta > 0.01f)
	//{
	//	addDelta = 0;
	//}
	++frame;
	if (frame > XMLRect.size() - 1)
	{
		frame = XMLRect.size() - 1;
	}

	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void Animation_Trap_Black::Begin()
{
}

void Animation_Trap_Black::End()
{
}

std::weak_ptr<Gdiplus::Image> Animation_Trap_Black::GetAtlasImg()
{
	return atlasImg;
}

