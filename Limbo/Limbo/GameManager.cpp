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
	//checkPoint���� key�� ã���� ���
	if (it != checkPoint.end())
	{
		//�ι�° x,y ���� ������ �ִ� pair�� ��ȯ���ش�.
		return it->second;
	}
}