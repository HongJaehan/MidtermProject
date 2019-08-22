#include "pch.h"
#include "Animation_Die.h"


static int countInt = 0;

Animation_Die::Animation_Die()
{
	frame = 0;
	state = eState_Die;
	addDelta = 0.0f;
 	std::wstring imgName(TEXT("Die.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Die.xml");
}

Animation_Die::~Animation_Die()
{
	atlasImg.reset();
}

void Animation_Die::Update(Gdiplus::Rect* rect, float Delta)
{
	addDelta += Delta;

	if (addDelta > 0.08f)
	{
		addDelta = 0;
		++frame;
	}

	if (frame > XMLRect.size() - 1)
	{
		frame = XMLRect.size() - 1;
		CountSceneChange(Delta);
	}

	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void Animation_Die::Begin()
{
}

void Animation_Die::End()
{
}

std::weak_ptr<Gdiplus::Image> Animation_Die::GetAtlasImg()
{
	return atlasImg;
}

void Animation_Die::CountSceneChange(float Delta)
{
	countInt++;
	if (countInt >= 15)
	{
		EventManager::GetInstance()->OnEvent(eEvent_ResetGameScene);
		SoundManager::GetInstance()->Stop(ESound::sound_Dead);
		countInt = 0;
		frame = 0;
		addDelta = 0;
	}
}

