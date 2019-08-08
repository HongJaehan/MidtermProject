#include "pch.h"
#include "Animation_Idle.h"

Animation_Idle::Animation_Idle()
{
	frame = 0;
	state = eState_Idle;
	std::wstring imgName(TEXT("Idle.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect,"XML\\Idle.xml");
}

Animation_Idle::~Animation_Idle()
{

}

void Animation_Idle::Update(Gdiplus::Image *img ,float Delta)
{
	//if (img_.expired()) return;

	//auto ptr = img_.lock();//std::wstring temp(TEXT("Asset\\"));
}
void Animation_Idle::Begin()
{

}

void Animation_Idle::End()
{

}