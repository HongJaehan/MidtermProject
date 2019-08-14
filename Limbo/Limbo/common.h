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
	ePlayer,
	eGrass,
	eTerrain
};

static enum EPlayerState 
{
	eState_Idle,
	eState_Run,
	eState_Jump,
	eState_Interaction,
	eState_IteractionMove,
	eState_Die
};

enum EEvent
{
	eEvent_PlayerDie
};

static struct SFileImgName
{
public:
	std::string Player = "Player.png";
};

struct Defines
{
public:
	//int playerWidth = 116;
	//int playerHeight = 163;
	int playerWidth = 61;
	int playerHeight = 86;
	int screenSizeX = 1024;
	int screenSizeY = 576;
	int mapImgSizeX = 1024;
	int mapImgSizeY = 1024;

	std::string img_Player_Idle = "Player_Idle.png";
	//std::wstring s = std::TEXT(img_Player_Idle);
};

static Defines defines;

SFileImgName fileImgName;