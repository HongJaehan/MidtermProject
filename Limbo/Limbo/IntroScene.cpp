#include "pch.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	backgroundImg = AssetManager::GetInstance()->GetImage(TEXT("Background.png"));
	fadeOutImg = AssetManager::GetInstance()->GetImage(TEXT("black.png"));

	AddDelta = 0.0f;
	rTransparency = 0.4f;
	bm2 = new Gdiplus::Bitmap(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), PixelFormat32bppARGB);
	imgAttr = new Gdiplus::ImageAttributes();
	IntroAnimation = new Animation_Logo();

	tag = ESceneTag::eIntroScene;
	/*soundA = sndPlaySound(TEXT("Sound\\Imprison2_OST.wav"), SND_ASYNC | SND_LOOP | SND_NOSTOP);
	soundB = sndPlaySound(TEXT("Sound\\walking-1.wav"), SND_ASYNC | SND_LOOP);*/
	//////////////////////////////////////////////////////////////////////////////////////////////

	//Sound1 = sound->LoadWAV(hWnd, L"Sound\\Imprison2_OST.wav");
	//Sound2 = sound->LoadWAV(hWnd, L"Sound\\walking-1.wav");
	//Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& sound->mciPlay); //play

	//////////////////////////////////////////////////////////////////////////////////////////////
}

IntroScene::~IntroScene()
{
	delete bm2;
	delete imgAttr;
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)nullptr);
	mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)nullptr);
}

void IntroScene::Init()
{

}


void IntroScene::Update(float delta)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
		//soundA = sndPlaySound(NULL, SND_ASYNC);
		Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)nullptr);
		SceneManager::GetInstance()->MoveNextScene();
	}

	/*if (GetAsyncKeyState(VK_UP) & 0x1001)
	{
		soundB = sndPlaySound(NULL, SND_ASYNC);
	}*/

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
