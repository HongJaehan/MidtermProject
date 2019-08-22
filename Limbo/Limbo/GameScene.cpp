#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
	tag = ESceneTag::eGameScene;
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

	////XML 파싱 예시
	//for (auto& it : XML)
	//{
	//	switch (it->id)
	//	{
	//	case id:
	//		ColliderObject* object = new ColliderObject(XML, ~~~~~);
	//		break;
	//	case id2:
	//		break;
	//	}
	//}
	bFlagCollision = false;
	
	ColliderObject *cObject = new ColliderObject(ETag::eTag_Collider, 95, 206, 190, 412);
	ColliderObject *cObject2 = new ColliderObject(ETag::eTag_Collider, 3278, 410, 80, 50);
	ColliderObject *cObject3 = new ColliderObject(ETag::eTag_Collider, 3890, 350, 60, 36);
	ColliderObject *cObject4 = new ColliderObject(ETag::eTag_Collider, 9478, 360, 65, 40);
	Niddle* cObject5 = new Niddle(ETag::eTag_Niddle, 1360, 480, 80, 72);
	Trap* cObject6 = new Trap(ETag::eTag_Trap, 2940, 390, 120, 70);
	Trap* cObject7 = new Trap(ETag::eTag_Trap, 3066,460, 120, 70);
	Spider* cObject8 = new Spider(ETag::eTag_Spider, 5566, -171, 438, 524);
	RotateRock* cObject9 = new RotateRock(ETag::eTag_Rock, 9297, 233, 160, 160);
	Corpse* cObject10 = new Corpse(ETag::eTag_Corpse, 6328, 485, 100, 50);
	SquareTrap* cObject11 = new SquareTrap(ETag::eTag_SquareRock, 6906, -100, 330, 612);
	Rope* cObject12 = new Rope(ETag::eTag_Trap, 6906, 500, 350, 50);
	FelledTrap* cObject13 = new FelledTrap(ETag::eTag_FallenTrap, 10505, 145, 50, 74);
	Niddle* cObject14 = new Niddle(ETag::eTag_Niddle, 10160, 450, 200, 90);
	Niddle* cObject15 = new Niddle(ETag::eTag_Niddle, 11618, 603, 937, 100);
	FallenRock* cObject16 = new FallenRock(ETag::eTag_FallenRock, 11350, 470, 188, 182, EObjectNum::eRock1);
	FallenRock* cObject17 = new FallenRock(ETag::eTag_FallenRock, 11600, 475, 146, 128, EObjectNum::eRock2);
	FallenRock* cObject18 = new FallenRock(ETag::eTag_FallenRock, 11830, 450, 152, 100, EObjectNum::eRock1);


	objectVec.emplace_back(cObject);
	objectVec.emplace_back(cObject2);
	objectVec.emplace_back(cObject3);
	objectVec.emplace_back(cObject4);
	objectVec.emplace_back(cObject5);
	objectVec.emplace_back(cObject6);
	objectVec.emplace_back(cObject7);
	objectVec.emplace_back(cObject8);
	objectVec.emplace_back(cObject9);
	objectVec.emplace_back(cObject10);
	objectVec.emplace_back(cObject11);
	objectVec.emplace_back(cObject12);
	objectVec.emplace_back(cObject13);
	objectVec.emplace_back(cObject14);
	objectVec.emplace_back(cObject15);
	objectVec.emplace_back(cObject16);
	objectVec.emplace_back(cObject17);
	objectVec.emplace_back(cObject18);



	//임시로
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

	//Event등록
	EventManager::GetInstance()->AddEvent(std::bind(&GameScene::SceneReset, this), EEvent::eEvent_ResetGameScene);
}

void GameScene::Update(float Delta)
{
	//현재 스크린 좌표
	int screenLeft = GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX * 0.5f;
	int screenRight = GameManager::GetInstance()->GetPlayerPosX() + defines.screenSizeX * 0.5f;

	for (auto& it : objectVec)
	{
		//오브젝트의 좌표
		int objRight = it->GetPosX() + it->GetWidth() * 0.5f;
		int objLeft = it->GetPosX() - it->GetWidth() * 0.5f;
		//스크린 좌표 안에 오브젝트가 존재하면 enable -> true 로 변경, Update실행
		if (objRight >= screenLeft && (abs(objRight-screenLeft) < defines.screenSizeX) 
			|| objLeft <= screenRight && (abs(screenRight - objLeft) < defines.screenSizeX))
		{
			it->SetEnable(true);
			//충돌 체크
			if (it->HasCollider() && CollisionCheck(player, it) && player->GetState() != EPlayerState::eState_Die)
			{
				it->Collision(player);
				player->Collision(it);
				player->SetNowColState(true);
			}
			it->Update(Delta);

			if (it->HasInteraction())
			{
				auto pLeft = player->GetPosX() - player->GetWidth() * 0.4f;
				auto pRight = player->GetPosX() + player->GetWidth() * 0.4f;
				auto oLeft = it->GetPosX() - it->GetCollider()->GetWidth() * 0.5f;
				auto oRight = it->GetPosX() + it->GetCollider()->GetWidth() * 0.5f;

				//x범위
				if ((abs(oLeft - pRight) < 15 && pRight < oLeft) || (abs(pLeft - oRight) < 15 && pLeft > oRight))
				{
					//y범위
					if (abs(player->GetPosY() - it->GetPosY()) < it->GetHeight()+3)
					{
						player->InInteractionDistance(it);
					}
					else
					{
						if (player->GetState() == EPlayerState::eState_InteractionMove)
						{
							player->ChangeState(EPlayerState::eState_Idle);
						}
					}
					
				}
			}
		}
		else
		{
			it->SetEnable(false);
		}
	}

	player->Update(Delta);
	player->InitColState();
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	int renderLeftPos = GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX / 2;
	int renderRightPos = GameManager::GetInstance()->GetPlayerPosX() + defines.screenSizeX / 2;

	//배경 그리기
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
			//그려줄 스크린 크기를 보내줌
			bg->RenderLeft(MemG,bg->GetEndPosX() - renderLeftPos);
		}
		else if (bg->GetStartPosX() <= renderRightPos && bg->GetEndPosX() >= renderRightPos)
		{
			bg->RenderRight(MemG, renderRightPos - bg->GetStartPosX());
			break;
		}
	}

	player->Render(MemG);
	//ojbect들 그려주기
	for (auto& it : objectVec)
	{
		//enable이 true인 object만 Render
		if (it->GetEnable())
		{
			it->Render(MemG);
		}
	}
}


bool GameScene::CollisionCheck(Object* obj1, Object* obj2)
{
	int obj1_Top = obj1->GetCollider()->GetY() - obj1->GetCollider()->GetHeight() * 0.5f;
	int obj1_Bottom = obj1->GetCollider()->GetY() + obj1->GetCollider()->GetHeight() * 0.5f;
	int obj1_Left = obj1->GetCollider()->GetX() - obj1->GetCollider()->GetWidth() * 0.5f;
	int obj1_Right = obj1->GetCollider()->GetX() + obj1->GetCollider()->GetWidth() * 0.5f;

	int obj2_Top = obj2->GetCollider()->GetY() - obj2->GetCollider()->GetHeight() * 0.5f;
	int obj2_Bottom = obj2->GetCollider()->GetY() + obj2->GetCollider()->GetHeight()*0.5f;
	int obj2_Left = obj2->GetCollider()->GetX() - obj2->GetCollider()->GetWidth() * 0.5f;
	int obj2_Right = obj2->GetCollider()->GetX() + obj2->GetCollider()->GetWidth() * 0.5f;

	//AABB
	//스크린 좌표로는 y축이 아래로 커지기 때문에
	//if (obj1_Top >= obj2_Bottom )
	//{
	//	return false;
	//}
	//if (obj1_Bottom <= obj2_Top)
	//{
	//	return false;
	//}
	//if (obj1_Left >= obj2_Right)
	//{
	//	return false;
	//}
	//if (obj1_Right <= obj2_Left)
	//{
	//	return false;
	//}
	if (obj1_Right < obj2_Left || obj1_Left > obj2_Right) return false;
	if (obj1_Top > obj2_Bottom || obj1_Bottom < obj2_Top) return false;
	
	return true;
}

void GameScene::SceneReset()
{
	Player* _player = dynamic_cast<Player*>(player);
	_player->ChangeState(eState_Idle);
	_player->SetX(GameManager::GetInstance()->GetCheckPointPosX());
	_player->SetY(player->GetPosX());
}
