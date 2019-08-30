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


	//SceneLevel 0부터 시작
	sceneLevel = 0;
	//Scene의 Level 최고값 현재 씬은 3개
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
	//현재을 다음 씬으로 이동
	//max씬의 값보다 작을경우에만
	if (sceneLevel < maxSceneLevel)
	{
 		curScene = sceneVec[++sceneLevel];
	}
}

void SceneManager::Render(CRect rc)
{

}
