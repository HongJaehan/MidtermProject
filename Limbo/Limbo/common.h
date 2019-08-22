#pragma once
#include <string>

enum ECheckPoint
{
	eCheckPoint1,
	eCheckPoint2,
	eCheckPoint3,
	eCheckPoint4,
	eCheckPoint5
};

enum ETag
{
	eTag_Player,
	eTag_Grass, //id = 1
	eTag_Collider, //id = 2
	eTag_Trap, //id =3 
	eTag_AutoMovement, // id = 4
	eTag_Niddle,
	eTag_Spider,
	eTag_Rock,
	eTag_Corpse,
	eTag_SquareRock,
	eTag_FallenTrap,
	eTag_FallenRock,
	eTag_Rope,
	eTag_Trap_Black
};

static enum EPlayerState 
{
	eState_Idle = 0,
	eState_Run = 1,
	eState_Jump = 2,
	eState_Die = 3,
	eState_Interaction = 4,
	eState_InteractionMove = 5,
};

enum ESpiderState
{
	eSpiderState_Idle,
	eSpiderState_Down,
	eSpiderState_Up
};

enum ERotateRockState
{
	eRotateRock_Idle,
	eRotateRock_Move,
	eRotateRock_Stop
};
enum EEvent
{
	eEvent_PlayerDie,
	eEvent_ResetGameScene,
	eEvent_MoveReady,
	eEvent_CutRope
};

static struct SFileImgName
{
public:
	std::string Player = "Player.png";
};

enum ESceneTag
{
	eIntroScene,
	eGameScene,
	eEndScene
};

enum EObjectNum
{
	eCorpse = 0,
	eGeer = 1,
	eGrass = 2,
	eMovement1 = 3,
	eMovement2 = 4,
	eMovement3 = 5,
	eOwl = 6,
	eRabbit = 7,
	eRotateRock = 8,
	eRock1 = 9,
	eRock2 = 10,
	eSquareTrap = 11,
	eFallTrap = 12
};

enum ESound
{
	sound_walk,
	sound_Dead,
	sound_GameScene,
	sound_Cave,
	sound_Rock,
	sound_Rope,
	sound_Slide,
	sound_FallenRock,
	sound_FelledTrap,
	sound_Spider
};

struct Defines
{
public:
	int playerWidth = 61;
	int playerHeight = 86;
	int screenSizeX = 1024;
	int screenSizeY = 576;
	int mapImgSizeX = 1024;
	int mapImgSizeY = 1024;
	int playerWidth_Die = 80;
	int playerHeight_Die = 120;
	int playerWidth_InterMove = 80;
	int playerHeight_InterMove = 65;

	std::string img_Player_Idle = "Player_Idle.png";
	//std::wstring s = std::TEXT(img_Player_Idle);
};

static Defines defines;

SFileImgName fileImgName;