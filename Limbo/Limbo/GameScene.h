#pragma once
#include "Scene.h"
#include "Player.h"
#include "object.h"

class GameScene :	public Scene
{
public:
	GameScene();
	~GameScene();
	
	void Init();
	void Control();
	void Update(int);
	void Render(Gdiplus::Graphics*);

private:
	Object* player;
	std::vector<Object*> objectVec;
	eCheckPoint checkPoint;
};

