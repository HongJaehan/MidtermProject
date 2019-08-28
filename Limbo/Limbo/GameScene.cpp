#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
	tag = ESceneTag::eGameScene;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	player = new Player();
	player->Init();
	AssetManager::GetInstance()->SetObjectXMLData(objXmlVec,"XML\\ObjectCreateData.xml");
	bFlagCollision = false;

	//Object 생성
	int i = 0;
	for (auto& it : objXmlVec)
	{
		++i;
		switch(it.GetNum())
		{
		case eTag_Collider:
		{
			ColliderObject* cObject = new ColliderObject(ETag::eTag_Collider, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Niddle:
		{
			Niddle* cObject = new Niddle(ETag::eTag_Niddle, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Trap:
		{
			Trap* cObject = new Trap(ETag::eTag_Trap, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Spider:
		{
			Spider* cObject= new Spider(ETag::eTag_Spider, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Rock:
		{
			RotateRock* cObject = new RotateRock(ETag::eTag_Rock, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Corpse:
		{
			Corpse* cObject = new Corpse(ETag::eTag_Corpse, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_SquareRock:
		{
			SquareTrap* cObject = new SquareTrap(ETag::eTag_SquareRock, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_Rope:
		{
			Rope* cObject= new Rope(ETag::eTag_Rope, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_FallenTrap:
		{
			FelledTrap* cObject = new FelledTrap(ETag::eTag_FallenTrap, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		case eTag_FallenRock:
		{
			if (i % 2 == 0)
			{
				FallenRock* cObject = new FallenRock(ETag::eTag_FallenRock, it.GetX(), it.GetY(), it.GetW(), it.GetH(), EObjectNum::eRock1);
				objectVec.emplace_back(cObject);
			}
			else
			{
				FallenRock* cObject = new FallenRock(ETag::eTag_FallenRock, it.GetX(), it.GetY(), it.GetW(), it.GetH(), EObjectNum::eRock2);
				objectVec.emplace_back(cObject);
			}
			break;
		}
		case eTag_Trap_Black:
		{
			Trap_Black* cObject = new Trap_Black(ETag::eTag_Trap_Black, it.GetX(), it.GetY(), it.GetW(), it.GetH());
			objectVec.emplace_back(cObject);
			break;
		}
		default:
			break;
		}
	}

	int mapCount = 9;
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

void GameScene::Realease()
{
	player->Release();

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

	for (auto& it : objXmlVec)
	{
		delete& it;
	}
	objXmlVec.clear();
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
	//출력할 부분의 좌/우 값  -> 현재 PlayerPosX() - 스크린 X좌표 / 2
	int renderLeftPos = GameManager::GetInstance()->GetPlayerPosX() - defines.screenSizeX / 2;
	int renderRightPos = GameManager::GetInstance()->GetPlayerPosX() + defines.screenSizeX / 2;

	//배경 그리기
	for (auto& bg : backgroundVec)
	{

		if (bg->GetStartPosX() <= renderLeftPos && bg->GetEndPosX() >= renderRightPos)
		{
			//현재 Player좌표와 계산하여 화면에 출력할 간격(interval)을 보내줌
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
	//각 충돌체크할 오브젝트들의 Left, Right, Top, Bottom 계산
	int obj1_Top = obj1->GetCollider()->GetY() - obj1->GetCollider()->GetHeight() * 0.5f;
	int obj1_Bottom = obj1->GetCollider()->GetY() + obj1->GetCollider()->GetHeight() * 0.5f;
	int obj1_Left = obj1->GetCollider()->GetX() - obj1->GetCollider()->GetWidth() * 0.5f;
	int obj1_Right = obj1->GetCollider()->GetX() + obj1->GetCollider()->GetWidth() * 0.5f;

	int obj2_Top = obj2->GetCollider()->GetY() - obj2->GetCollider()->GetHeight() * 0.5f;
	int obj2_Bottom = obj2->GetCollider()->GetY() + obj2->GetCollider()->GetHeight()*0.5f;
	int obj2_Left = obj2->GetCollider()->GetX() - obj2->GetCollider()->GetWidth() * 0.5f;
	int obj2_Right = obj2->GetCollider()->GetX() + obj2->GetCollider()->GetWidth() * 0.5f;

	//AABB
	//충돌하지 않을 경우부터 계산
	if (obj1_Right < obj2_Left || obj1_Left > obj2_Right) return false;
	if (obj1_Top > obj2_Bottom || obj1_Bottom < obj2_Top) return false;
	
	//충돌
	return true;
}

void GameScene::SceneReset()
{
	Player* _player = dynamic_cast<Player*>(player);
	_player->SetX(GameManager::GetInstance()->GetCheckPointPosX());
	_player->SetY(player->GetPosX());
	_player->GetCollider()->SetX(_player->GetPosX());
	_player->GetCollider()->SetY(_player->GetPosY());

	_player->ChangeState(eState_Idle);
}

void GameScene::SoundEnd()
{
	sndPlaySound(NULL, SND_ASYNC);
}
