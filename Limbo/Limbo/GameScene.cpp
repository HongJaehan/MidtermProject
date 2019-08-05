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

//���� �� �ȿ� �ִ� ��� ������Ʈ���� �ѹ��� ���İ��� Control, Update, Render�����ش�.
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

