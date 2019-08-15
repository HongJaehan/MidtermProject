#pragma once
#include "Scene.h"
#include "Player.h"
#include "object.h"
#include "Terrain.h"
#include "Background.h"
#include "ColliderObject.h"

class GameScene :	public Scene
{
public:
	GameScene();
	~GameScene();
	
	void Init();
	void Update(float);
	void Render(Gdiplus::Graphics*);
	bool CollisionCheck(Object*,Object*);
	void Func(int);

private:
	Object* player;
	Object* terrain;
	std::vector<Background*> backgroundVec;
	std::vector<Object*> objectVec;
	ECheckPoint checkPoint;
};

