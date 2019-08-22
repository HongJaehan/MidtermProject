#include "pch.h"
#include "Animation_Jump.h"

Animation_Jump::Animation_Jump()
{
	frame = 0;
	state = eState_Jump;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Jump.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Jump.xml");
}

Animation_Jump::~Animation_Jump()
{
	atlasImg.reset();
}

void Animation_Jump::Update( Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.03f)
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
void Animation_Jump::Begin()
{
	frame = 0;
	addDelta = 0;
}

void Animation_Jump::End()
{
	frame = 0;
	addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> Animation_Jump::GetAtlasImg()
{
	return atlasImg;
}