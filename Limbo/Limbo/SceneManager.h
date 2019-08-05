#pragma once
#include "Scene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include <vector>

class SceneManager : public Singleton<SceneManager>
{
public:
	void SetCurScene(Scene*);
	Scene* GetCurScene();
	void Init();
	void MoveNextScene();

private:
	Scene* curScene;
	Scene* introScene;
	Scene* gameScene;
	Scene* endScene;

	std::vector<Scene*> sceneVec;
	int sceneLevel;
	int maxSceneLevel;
};

SceneManager* SceneManager::instance = nullptr;






