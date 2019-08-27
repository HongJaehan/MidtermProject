#include "pch.h"
#include "AnimState_Rope.h"

AnimState_Rope::AnimState_Rope()
{
}

AnimState_Rope::~AnimState_Rope()
{
	atlasImg.reset();
}

void AnimState_Rope::Init()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Rope.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Rope.xml");
}

void AnimState_Rope::Update(Gdiplus::Rect* rect, float Delta)
{
}

void AnimState_Rope::Update(Gdiplus::Rect* rect, float Delta, bool action)
{
	if (!action)
	{
		rect->X = XMLRect[0].X;
		rect->Y = XMLRect[0].Y;
		rect->Width = XMLRect[0].Width;
		rect->Height = XMLRect[0].Height;
		return;
	}

	addDelta += Delta;
	if (addDelta > 0.05f)
	{
		frame++;
		addDelta = 0;
	}
	if (frame > XMLRect.size() - 1)
	{
		frame = XMLRect.size() - 1;
	}

	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void AnimState_Rope::Begin()
{
}

void AnimState_Rope::End()
{
}


std::weak_ptr<Gdiplus::Image> AnimState_Rope::GetAtlasImg()
{
	return atlasImg;
}
