#include "pch.h"
#include "Animation_Run.h"

Animation_Run::Animation_Run()
{
	frame = 0;
	state = eState_Run;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Run.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Run.xml");
}

Animation_Run::~Animation_Run()
{

}
void Animation_Run::Update( Gdiplus::Rect* rect, float Delta)
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
void Animation_Run::Begin()
{

}

void Animation_Run::End()
{
	frame = 0;
	addDelta = 0;
}
std::weak_ptr<Gdiplus::Image> Animation_Run::GetAtlasImg()
{
	return atlasImg;
}