#include "pch.h"
#include "Animation_Trap.h"

Animation_Trap::Animation_Trap()
{
	std::wstring imgName(TEXT("trap.png"));
	atlasImg = AssetManager::GetInstance()->GetImage(imgName);
	AssetManager::GetInstance()->SetXMLData(XMLRect, "XML\\trap.xml");
}

Animation_Trap::~Animation_Trap()
{
}

void Animation_Trap::Update(Gdiplus::Rect* rect, float Delta)
{
	
}

void Animation_Trap::Begin()
{
}

void Animation_Trap::End()
{
}

std::weak_ptr<Gdiplus::Image> Animation_Trap::GetAtlasImg()
{
	return atlasImg;
}
