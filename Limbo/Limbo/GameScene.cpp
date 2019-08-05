#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{

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

void GameScene::Update()
{
	for (auto& it : objectVec)
	{
		it->Update();
	}
}

void GameScene::Render()
{
	for (auto& it : objectVec)
	{
		it->Render();
	}
}

