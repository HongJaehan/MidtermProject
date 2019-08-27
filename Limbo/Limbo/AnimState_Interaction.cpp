#include "pch.h"
#include "AnimState_Interaction.h"

AnimState_Interaction::AnimState_Interaction()
{

}

AnimState_Interaction::~AnimState_Interaction()
{
	atlasImg.reset();
}

void AnimState_Interaction::Init()
{
	frame = 0;
	state = eState_Interaction;
	addDelta = 0.0f;
	std::wstring imgName(TEXT("Interaction.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\Interaction.xml");
}
void AnimState_Interaction::Update(Gdiplus::Rect* rect, float Delta)
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
		//이벤트 발생
		EventManager::GetInstance()->OnEvent(eEvent_MoveReady);
		return;
	}

	rect->X = XMLRect[frame].X;
	rect->Y = XMLRect[frame].Y;
	rect->Width = XMLRect[frame].Width;
	rect->Height = XMLRect[frame].Height;
}

void AnimState_Interaction::Begin()
{
}

void AnimState_Interaction::End()
{
	frame = 0;
	addDelta = 0;
}

std::weak_ptr<Gdiplus::Image> AnimState_Interaction::GetAtlasImg()
{
	return atlasImg;
}
