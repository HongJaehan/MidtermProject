#include "pch.h"
#include "IntroScene.h"
#include "Limbo.h"

IntroScene::IntroScene()
{
	tag = ESceneTag::eIntroScene;

	backgroundImg = AssetManager::GetInstance()->GetImage(TEXT("Background.png"));
	fadeOutImg = AssetManager::GetInstance()->GetImage(TEXT("black.png"));

	AddDelta = 0.0f;
	rTransparency = 0.4f;
	bm2 = new Gdiplus::Bitmap(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	imgAttr = new Gdiplus::ImageAttributes();
	IntroAnimation = new Animation_Logo();

	sndPlaySound(L"Sound\\Imprison2_OST.wav", SND_ASYNC | SND_LOOP);
}

IntroScene::~IntroScene()
{
	delete bm2;
	delete imgAttr;
	//delete sound;

	/*if (sound->wDeviceID > 0)
	{
		sound->CloseWAV(hWnd, Sound1);
	}*/
}

void IntroScene::Init()
{

}


void IntroScene::Update(float delta)
{
	//if (!sound)
	//{
	//	sound = new MCISound();
	//	hWnd = theApp.GetMainWnd()->GetSafeHwnd();
	//	//Sound1 = sound->LoadWAV(hWnd, L"Sound\\Imprison2_OST.wav");
	//	Sound1 = sound->LoadWAV(hWnd, L"Sound\\walking-1.wav");
	//	sound->PlayWAV_Repeat(hWnd, Sound1);
	//}

	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
		//sound->StopWAV(hWnd, Sound1);
		sndPlaySound(NULL, SND_ASYNC);
		sndPlaySound(L"Sound\\FrogForest.wav", SND_ASYNC | SND_LOOP);
		SceneManager::GetInstance()->MoveNextScene();
		SoundManager::GetInstance()->Play(ESound::sound_GameScene);
		return;
	}

	/////////////////////////////////////////////////

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

	////////////////////////////////////////////////
	IntroAnimation->Update(&atlasRect, delta);
}

void IntroScene::Render(Gdiplus::Graphics* MemG)
{
	//////////////////black.png////////////////////

	Gdiplus::Rect rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Gdiplus::Bitmap bm(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	temp.DrawImage(fadeOutImg.lock().get(), rect);

	////그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, defines.screenSizeX, defines.screenSizeY);

	//////////////////Background.png////////////////////

	Gdiplus::Rect rect2(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Gdiplus::Graphics temp2(bm2);

	temp2.DrawImage(backgroundImg.lock().get(), rect2, 0, 0, 1666, 1321, Gdiplus::UnitPixel, imgAttr);

	////그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect2(0, 0, defines.screenSizeX, defines.screenSizeY);

	//////////////////PRESS.png////////////////////

	Gdiplus::Rect rect3(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Gdiplus::Bitmap bm3(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	Gdiplus::Graphics temp3(&bm3);

	temp3.DrawImage(IntroAnimation->GetAtlasImg().lock().get(), rect3, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	////그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect3(100, 50, defines.screenSizeX - 200, defines.screenSizeY - 150);

	MemG->DrawImage(&bm, screenPosRect);
	MemG->DrawImage(bm2, screenPosRect2);
	MemG->DrawImage(&bm3, screenPosRect3);
}