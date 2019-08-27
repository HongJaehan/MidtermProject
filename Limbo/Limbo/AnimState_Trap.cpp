#include "pch.h"
#include "AnimState_Trap.h"

AnimState_Trap::AnimState_Trap()
{
}

AnimState_Trap::~AnimState_Trap()
{
	atlasImg.reset();
}

void AnimState_Trap::Init()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("trapEx.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\trap.xml");
}

void AnimState_Trap::Update(Gdiplus::Rect* rect, float Delta)
{

}

void AnimState_Trap::Update(Gdiplus::Rect* rect, float Delta, bool action)
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

void AnimState_Trap::Begin()
{
}

void AnimState_Trap::End()
{
}

std::weak_ptr<Gdiplus::Image> AnimState_Trap::GetAtlasImg()
{
	return atlasImg;
}
