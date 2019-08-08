#include "pch.h"
#include "Animation_Jump.h"

Animation_Jump::Animation_Jump()
{
	frame = 0;
	state = eState_Jump;
	//std::wstring imgName(TEXT("Jump.png"));
	//atlasImg = AssetManager::GetInstance()->GetImage(imgName);
}

Animation_Jump::~Animation_Jump()
{

}

void Animation_Jump::Update(Gdiplus::Image *img ,float Delta)
{

}
void Animation_Jump::Begin()
{

}

void Animation_Jump::End()
{

}