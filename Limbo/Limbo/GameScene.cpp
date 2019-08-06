#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::Init()
{
	player = new Player();
	objectVec.emplace_back(player);
}

//현재 씬 안에 있는 모든 오브젝트들을 한번씩 거쳐가며 Control, Update, Render돌려준다.
void GameScene::Control()
{
	for (auto& it : objectVec)
	{
		it->Control();
	}
}

void GameScene::Update(float Delta)
{
	for (auto& it : objectVec)
	{
		it->Update(Delta);
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}

