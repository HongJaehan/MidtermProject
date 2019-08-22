#pragma once
#include "Singleton.h"
#include "MCISound.h"

class SoundManager :
	public Singleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();
	void Play(ESound);
	void Stop(ESound);
	void AllStop();
private:
	MCISound* soundM;
	HWND hWnd;
	std::vector<DWORD> soundList;
	DWORD Sound2;
};

SoundManager* SoundManager::instance = nullptr;