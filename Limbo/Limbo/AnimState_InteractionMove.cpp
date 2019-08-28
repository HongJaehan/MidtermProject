#include "pch.h"
#include "AnimState_InteractionMove.h"

AnimState_InteractionMove::AnimState_InteractionMove()
{
}

AnimState_InteractionMove::~AnimState_InteractionMove()
{
	atlasImg.reset();
}

void AnimState_InteractionMove::Init()
{
	frame = 0;
	state = eState_InteractionMove;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Interaction_Move.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Interaction_Move.xml");
}

static float soundDelta =0.0f;
void AnimState_InteractionMove::Update(Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;
	soundDelta += Delta;

	if (soundDelta > 2.0)
	{
		soundDelta = 0;
		SoundManager::GetInstance()->Stop(ESound::sound_Slide);
		SoundManager::GetInstance()->Play(ESound::sound_Slide);

	}

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

void AnimState_InteractionMove::Begin()
{
	SoundManager::GetInstance()->Play(ESound::sound_Slide);
}

void AnimState_InteractionMove::End()
{
	SoundManager::GetInstance()->Stop(ESound::sound_Slide);
	frame = 0;
	addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> AnimState_InteractionMove::GetAtlasImg()
{
	return atlasImg;
}
