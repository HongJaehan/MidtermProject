#include "pch.h"
#include "FadeOut.h"

FadeOut::FadeOut()
{
	enable = false;
	EventManager::GetInstance()->AddEvent(std::bind(&FadeOut::OnFadeOutEvent, this), EEvent::eEvent_ResetGameScene);
	fadeOutImg = AssetManager::GetInstance()->GetImage(TEXT("black.png"));
}

FadeOut::~FadeOut()
{
	delete bm2;
	delete imgAttr;
}

void FadeOut::Update(float delta)
{
	if (enable)
	{
		//점점 흐려진다
		////투명도 조절 4행 4열
		Gdiplus::ColorMatrix clrMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		AddDelta += delta;
		if (AddDelta > 0.001f)
		{
			imgAttr->SetColorMatrix(&clrMatrix);
		}

		//다 흐려지면 active = false;
	}
}

void FadeOut::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Gdiplus::Bitmap bm(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	temp.DrawImage(fadeOutImg.lock().get(), rect);

	////그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, defines.screenSizeX, defines.screenSizeY);

	MemG->DrawImage(&bm, screenPosRect);
}

void FadeOut::Collision(Object*)
{
}

void FadeOut::OnFadeOutEvent()
{
	enable = true;
}

bool FadeOut::HasInteraction()
{
	return false;
}
