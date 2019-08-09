#include "pch.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	backgroundImg = AssetManager::GetInstance()->GetImage(TEXT("intro.png"));
}

IntroScene::~IntroScene()
{

}

void IntroScene::Init()
{

}
void IntroScene::Control()
{
   	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
    		SceneManager::GetInstance()->MoveNextScene();
	}
}

void IntroScene::Update(float)
{
}

void IntroScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Gdiplus::Bitmap bm(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	temp.DrawImage(backgroundImg.lock().get(), rect);

	////그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	MemG->DrawImage(&bm, screenPosRect);
}
