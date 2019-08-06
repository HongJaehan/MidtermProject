#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	nowCheckPoint = 0;
}

GameManager::~GameManager()
{

}

std::pair<int, int> GameManager::GetCheckPoint()
{
	auto& it = checkPoint.find(nowCheckPoint);
	//checkPoint에서 key를 찾았을 경우
	if (it != checkPoint.end())
	{
		//두번째 x,y 값을 가지고 있는 pair을 반환해준다.
		return it->second;
	}
}