#pragma once
#include "Scene.h"
#include "Player.h"
#include "object.h"
#include "Terrain.h"
#include "Background.h"
#include "ColliderObject.h"
#include "Niddle.h"
#include "Trap.h"
#include "Spider.h"
#include "RotateRock.h"
#include "Corpse.h"

class GameScene :	public Scene
{
public:
	GameScene();
	~GameScene();
	
	void Init();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	bool CollisionCheck(Object*,Object*);
	void SceneReset();

private:
	Object* player;
	Object* terrain;
	std::vector<Background*> backgroundVec;
	std::vector<Object*> objectVec;
	ECheckPoint checkPoint;
};

