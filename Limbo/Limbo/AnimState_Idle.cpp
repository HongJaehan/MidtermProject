#include "pch.h"
#include "AnimState_Idle.h"

AnimState_Idle::AnimState_Idle()
{

}

AnimState_Idle::~AnimState_Idle()
{
	atlasImg.reset();
}


void AnimState_Idle::Init()
{
	frame = 0;
	state = eState_Idle;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Idle.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Idle.xml");
}


void AnimState_Idle::Update(Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.025f)
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

void AnimState_Idle::Begin()
{

}

void AnimState_Idle::End()
{

}

std::weak_ptr<Gdiplus::Image> AnimState_Idle::GetAtlasImg()
{
	return atlasImg;
}