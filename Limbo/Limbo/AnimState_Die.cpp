#include "pch.h"
#include "AnimState_Die.h"


static int countInt = 0;

AnimState_Die::AnimState_Die()
{

}

AnimState_Die::~AnimState_Die()
{
	atlasImg.reset();
}

void AnimState_Die::Init()
{
	frame = 0;
	state = eState_Die;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Die.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Die.xml");
}


void AnimState_Die::Update(Gdiplus::Rect* rect, float Delta)
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

void AnimState_Die::Begin()
{
}

void AnimState_Die::End()
{
}

std::weak_ptr<Gdiplus::Image> AnimState_Die::GetAtlasImg()
{
	return atlasImg;
}

void AnimState_Die::CountSceneChange(float Delta)
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

