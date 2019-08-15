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
	objectVec.clear();

	for (auto& it2 : backgroundVec)
	{
		delete it2;
	}
	backgroundVec.clear();
}

//void GameScene::Func(int x)
//{
//	int k = x;
//}
void GameScene::Init()
{
	//EventManager::GetInstance()->AddEvent(std::bind(&GameScene::Func, this, std::placeholders::_1), eEvent_PlayerDie);
	//EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
	player = new Player();
	//objectVec.emplace_back(player);
	//terrain = new Terrain();
	//objectVec.emplace_back(terrain);
	ColliderObject *cObject = new ColliderObject(ETag::eCollider, 95, 206, 190, 412);
	objectVec.emplace_back(cObject);

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
	player->Update(Delta);
	
	//���� ��ũ�� ��ǥ
	int screenLeft = GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f;
	int screenRight = GameManager::GetInstance()->GetPlayerPosX() + defines.screenSizeX * 0.5f;

	for (auto& it : objectVec)
	{
		//������Ʈ�� ��ǥ
		int objRight = it->GetPosX() + it->GetWidth() * 0.5f;
		int objLeft = it->GetPosX() - it->GetWidth() * 0.5f;
		//��ũ�� ��ǥ �ȿ� ������Ʈ�� �����ϸ� enable -> true �� ����, Update����
		if (objRight >= screenLeft || objLeft <= screenRight)
		{
			it->SetEnable(true);
			//�浹 üũ
			if (CollisionCheck(player, it))
			{
				switch (it->GetTag())
				{
					//Ʈ���� �浹���� ���
				case ETag::eTrap:
					EventManager::GetInstance()->OnEvent(eEvent_PlayerDie);
					break;
					//Collider�� �ܼ� �浹�� ���
				case ETag::eCollider:
				{
					auto _player = dynamic_cast<Player*>(player);
					_player->Collision(it);
					break;
				}
				default:
					break;
				}
			}
			it->Update(Delta);
		}
		else
		{
			it->SetEnable(false);
		}
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

	player->Render(MemG);
	//ojbect�� �׷��ֱ�
	for (auto& it : objectVec)
	{
		//enable�� true�� object�� Render
		if (it->GetEnable())
		{
			it->Render(MemG);
		}
	}
}


bool GameScene::CollisionCheck(Object* obj1, Object* obj2)
{

	int obj1_Top = obj1->GetPosY() - obj1->GetHeight() * 0.5f;
	int obj1_Bottom = obj1->GetPosY() + obj1->GetHeight() * 0.5f;
	int obj1_Left = obj1->GetPosX() - obj1->GetWidth() * 0.5f;
	int obj1_Right = obj1->GetPosX() + obj1->GetWidth() * 0.5f;

	int obj2_Top = obj2->GetPosY() - obj2->GetHeight() * 0.5f;
	int obj2_Bottom = obj2->GetPosY() + obj2->GetHeight() * 0.5f;
	int obj2_Left = obj2->GetPosX() - obj2->GetWidth() * 0.5f;
	int obj2_Right = obj2->GetPosX() + obj2->GetWidth() * 0.5f;

	//AABB
	//��ũ�� ��ǥ�δ� y���� �Ʒ��� Ŀ���� ������
	if (obj1_Top > obj2_Bottom )
	{
		return false;
	}
	if (obj1_Bottom < obj2_Top)
	{
		return false;
	}
	if (obj1_Left > obj2_Right)
	{
		return false;
	}
	if (obj1_Right < obj2_Left)
	{
		return false;
	}

	return true;
}