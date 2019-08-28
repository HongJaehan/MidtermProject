#pragma once
#include "Scene.h"
#include "Player.h"
#include "object.h"
#include "Background.h"
#include "ColliderObject.h"
#include "Niddle.h"
#include "Trap.h"
#include "Spider.h"
#include "RotateRock.h"
#include "Corpse.h"
#include "SquareTrap.h"
#include "Rope.h"
#include "FelledTrap.h"
#include "FallenRock.h"
#include "Trap_Black.h"
#include "ObjectXMLData.h"

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
	void SoundEnd();

private:
	Player* player;
	Object* terrain;
	std::vector<Background*> backgroundVec;
	std::vector<Object*> objectVec;
	ECheckPoint checkPoint;
	bool bFlagCollision;

	std::vector<ObjectXMLData> objXmlVec;
};

