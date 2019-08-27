#include "pch.h"
#include "AnimState_Logo.h"

AnimState_Logo::AnimState_Logo()
{

}

AnimState_Logo::~AnimState_Logo()
{
	atlasImg.reset();
}

void AnimState_Logo::Init()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("PRESS.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Intro.xml");
}

void AnimState_Logo::Update(Gdiplus::Rect* rect, float Delta)
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

void AnimState_Logo::Begin()
{

}

void AnimState_Logo::End()
{
	//frame = 0;
	//addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> AnimState_Logo::GetAtlasImg()
{
	return atlasImg;
}