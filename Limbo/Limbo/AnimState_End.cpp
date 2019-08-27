#include "pch.h"
#include "AnimState_End.h"

AnimState_End::AnimState_End()
{

}

void AnimState_End::Init()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("THANK.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\End.xml");
}
AnimState_End::~AnimState_End()
{
	atlasImg.reset();
}

void AnimState_End::Update(Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.5f)
	{
		addDelta = 0;
		++frame;
	}

	if (frame > XMLRect.size() - 1)
	{
		frame = 0;
	}
	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void AnimState_End::Begin()
{

}

void AnimState_End::End()
{
	//frame = 0;
	//addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> AnimState_End::GetAtlasImg()
{
	return atlasImg;
}