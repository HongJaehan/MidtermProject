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
	atlasImg.reset();
}
void Animation_Run::Update( Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.017f)
	{
		++frame;
		addDelta = 0;
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
	SoundManager::GetInstance()->Play(ESound::sound_walk);
}

void Animation_Run::End()
{
	SoundManager::GetInstance()->Stop(ESound::sound_walk);
	frame = 0;
	addDelta = 0;
}
std::weak_ptr<Gdiplus::Image> Animation_Run::GetAtlasImg()
{
	return atlasImg;
}