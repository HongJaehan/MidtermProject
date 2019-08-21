#include "pch.h"
#include "Animation_End.h"

Animation_End::Animation_End()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("THANK.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\End.xml");
}

Animation_End::~Animation_End()
{
	atlasImg.reset();
}

void Animation_End::Update(Gdiplus::Rect* rect, float Delta)
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

void Animation_End::Begin()
{

}

void Animation_End::End()
{
	//frame = 0;
	//addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> Animation_End::GetAtlasImg()
{
	return atlasImg;
}