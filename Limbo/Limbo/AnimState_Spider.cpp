#include "pch.h"
#include "AnimState_Spider.h"

#define MAX_DOWN_FRAME 
AnimState_Spider::AnimState_Spider()
{

}

AnimState_Spider::~AnimState_Spider()
{
	atlasImg.lock().reset();
}

void AnimState_Spider::Init()
{
	frame = 0;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Spider.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Spider.xml");
}


void AnimState_Spider::Update(Gdiplus::Rect* rect, float Delta)
{
}

void AnimState_Spider::Update(Gdiplus::Rect* rect, float Delta, ESpiderState state)
{
	addDelta += Delta;
	switch (state)
	{
	case eSpiderState_Idle:
		rect->X = XMLRect[0].X;
		rect->Y = XMLRect[0].Y;
		rect->Width = XMLRect[0].Width;
		rect->Height = XMLRect[0].Height;
		return;
		break;
	case eSpiderState_Down:
		if (addDelta > 0.1f)
		{
			++frame;
			addDelta = 0.0f;
		}
		if (frame >= XMLRect.size() - 1)
		{
			frame = XMLRect.size() - 1;
			addDelta = 0.0f;
		}
		break;
	case eSpiderState_Up:
		if (addDelta > 0.1f)
		{
			--frame;
			addDelta = 0.0f;
		}
		if (frame <= 0)
		{
			frame = 0;
		}
		break;
	}
	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void AnimState_Spider::Begin()
{
}

void AnimState_Spider::End()
{
}


std::weak_ptr<Gdiplus::Image> AnimState_Spider::GetAtlasImg()
{
	return atlasImg;
}
