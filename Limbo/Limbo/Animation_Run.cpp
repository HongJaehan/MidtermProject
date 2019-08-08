#include "pch.h"
#include "Animation_Run.h"

Animation_Run::Animation_Run()
{
	frame = 0;
	state = eState_Run;
	//std::wstring imgName(TEXT("Run.png"));
	//atlasImg = AssetManager::GetInstance()->GetImage(imgName);
}

Animation_Run::~Animation_Run()
{

}

void Animation_Run::Update(Gdiplus::Image *img ,float Delta)
{

}
void Animation_Run::Begin()
{

}

void Animation_Run::End()
{

}
