#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
	delete player;
	for (auto& it : objectVec)
	{
		delete it;
	}

	for (auto& it2 : backgroundVec)
	{
		delete it2;
	}
}

void GameScene::Init()
{
	player = new Player();
	//terrain = new Terrain();
	//objectVec.emplace_back(terrain);
	objectVec.emplace_back(player);

	//�ӽ÷�
	int mapCount = 10;
	int startPosX = 0;

	for (int i = 1; i < mapCount; ++i)
	{
		std::wstring s = TEXT("\\Map\\map");
		s.append(std::to_wstring(i));
		s.append(TEXT(".png"));

		auto b = new Background(startPosX, s);
		backgroundVec.emplace_back(b);
		startPosX += defines.screenSizeX * 2;
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
	int renderLeftPos = GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX / 2;
	int renderRightPos = GameManager::GetInstance()->GetPlayerPosX() + defines.screenSizeX / 2;

	//��� �׸���
	for (auto& bg : backgroundVec)
	{
		if (bg->GetStartPosX() <= renderLeftPos && bg->GetEndPosX() >= renderRightPos)
		{
			int interval = renderLeftPos - bg->GetStartPosX();
			bg->Render(MemG, interval);
			break;
		}
		if (bg->GetEndPosX() >= renderLeftPos && bg->GetStartPosX() <= renderLeftPos)
		{
			//�׷��� ��ũ�� ũ�⸦ ������
			bg->RenderLeft(MemG,bg->GetEndPosX() - renderLeftPos);
		}
		else if (bg->GetStartPosX() <= renderRightPos && bg->GetEndPosX() >= renderRightPos)
		{
			bg->RenderRight(MemG, renderRightPos - bg->GetStartPosX());
			break;
		}
	}

	//ojbect�� �׷��ֱ�
	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}
}

