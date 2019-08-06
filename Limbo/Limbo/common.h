#pragma once
#include <string>

enum eCheckPoint
{
	eCheckPoint1,
	eCheckPoint2,
	eCheckPoint3,
	eCheckPoint4,
	eCheckPoint5
};

enum eTag
{
	ePlayer,
	eGrass,
	eTerrain
};

static enum ePlayerState 
{
	eState_Idle,
	eState_Run,
	eState_Jump,
	eState_Interaction,
	eState_Die
};

static struct sFileImgName
{
public:
	std::string Player = "Player.png";
};

struct defines
{
public:
	int playerWidth = 116;
	int playerHeight = 163;
};
static defines define;


sFileImgName fileImgName;