#include "pch.h"
#include "Animation_Idle.h"

Animation_Idle::Animation_Idle()
{
	frame = 0;
	state = eState_Idle;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Idle.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect,"XML\\Idle.xml");
}

Animation_Idle::~Animation_Idle()
{
	atlasImg.reset();
}

void Animation_Idle::Update(Gdiplus::Rect* rect, float Delta)
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

void Animation_Idle::Begin()
{

}

void Animation_Idle::End()
{

}

std::weak_ptr<Gdiplus::Image> Animation_Idle::GetAtlasImg()
{
	return atlasImg;
}