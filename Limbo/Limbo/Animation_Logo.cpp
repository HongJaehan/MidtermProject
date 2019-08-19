#include "pch.h"
#include "Animation_Logo.h"

Animation_Logo::Animation_Logo()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("PRESS.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Intro.xml");
}

Animation_Logo::~Animation_Logo()
{
	atlasImg.reset();
}

void Animation_Logo::Update(Gdiplus::Rect* rect, float Delta)
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

void Animation_Logo::Begin()
{

}

void Animation_Logo::End()
{
	//frame = 0;
	//addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> Animation_Logo::GetAtlasImg()
{
	return atlasImg;
}