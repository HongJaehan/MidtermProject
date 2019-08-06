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

//���� �� �ȿ� �ִ� ��� ������Ʈ���� �ѹ��� ���İ��� Control, Update, Render�����ش�.
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

