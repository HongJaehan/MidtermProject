#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	for (auto& it : sceneVec)
	{
		delete it;
	}
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
	introScene = new IntroScene();
	gameScene = new GameScene();
	endScene = new EndScene();
	//curScene = introScene;
	

	sceneVec.emplace_back(introScene);
	sceneVec.emplace_back(gameScene);
	sceneVec.emplace_back(endScene);

	curScene = gameScene;

	//SceneLevel 0부터 시작
	sceneLevel = 0;
	//Scene의 Level 최고값 현재 씬은 3개
 	maxSceneLevel = 2;
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
