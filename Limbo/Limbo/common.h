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
	eState_Die
};

static struct SFileImgName
{
public:
	std::string Player = "Player.png";
};

struct Defines
{
public:
	int playerWidth = 116;
	int playerHeight = 163;
	int screenSizeX = 1920;
	int screenSizeY = 1080;

	std::string img_Player_Idle = "Player_Idle.png";
	//std::wstring s = std::TEXT(img_Player_Idle);
};

static Defines defines;

SFileImgName fileImgName;