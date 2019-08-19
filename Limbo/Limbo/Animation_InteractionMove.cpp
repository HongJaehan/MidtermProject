#include "pch.h"
#include "Animation_InteractionMove.h"

Animation_InteractionMove::Animation_InteractionMove()
{
	frame = 0;
	state = eState_InteractionMove;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Interaction_Move.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Interaction_Move.xml");
}

Animation_InteractionMove::~Animation_InteractionMove()
{
	atlasImg.reset();
}

void Animation_InteractionMove::Update(Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.08f)
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

void Animation_InteractionMove::Begin()
{
}

void Animation_InteractionMove::End()
{
	frame = 0;
	addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> Animation_InteractionMove::GetAtlasImg()
{
	return atlasImg;
}
