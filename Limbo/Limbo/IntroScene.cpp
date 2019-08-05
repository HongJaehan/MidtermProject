#include "pch.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{

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

void IntroScene::Update()
{
	int x = 0;
}

void IntroScene::Render()
{
	int y = 0;

}
