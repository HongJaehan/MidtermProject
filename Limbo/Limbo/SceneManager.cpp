#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
void SceneManager::SetCurScene(Scene* scene)
{
	curScene = scene;
}

Scene* SceneManager::GetCurScene()
{
	return curScene;
}

void SceneManager::Init()
{
	//_crtBreakAlloc = 497;
	//1283 1266 1250 1233 1216 1199
	introScene = new IntroScene();
	introScene->Init();
	gameScene = new GameScene();
	gameScene->Init();
	endScene = new EndScene();
	endScene->Init();

 	curScene = introScene;
	

	sceneVec.emplace_back(introScene);
	sceneVec.emplace_back(gameScene);
	sceneVec.emplace_back(endScene);


	//SceneLevel 0���� ����
	sceneLevel = 0;
	//Scene�� Level �ְ� ���� ���� 3��
 	maxSceneLevel = 2;
}

void SceneManager::Release()
{
	for (auto& it : sceneVec)
	{
		SafeRelease(&it);
	}
}

void SceneManager::MoveNextScene()
{
	//������ ���� ������ �̵�
	//max���� ������ ������쿡��
	if (sceneLevel < maxSceneLevel)
	{
 		curScene = sceneVec[++sceneLevel];
	}
}

void SceneManager::Render(CRect rc)
{

}
