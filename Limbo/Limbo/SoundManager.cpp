#include "pch.h"
#include "SoundManager.h"
#include "Limbo.h"

SoundManager::SoundManager()
{
	soundM = new MCISound();
	hWnd = theApp.GetMainWnd()->GetSafeHwnd();
	//DWORD Sound1 = sound->LoadWAV(hWnd, L"Sound\\walking-1.wav");
	//DWORD Sound2 = sound->LoadWAV(hWnd, L"Sound\\Dead1.wav");

	//DWORD Sound3 = sound->LoadWAV(hWnd, L"Sound\\walking-3.wav");
	//DWORD Sound4 = sound->LoadWAV(hWnd, L"Sound\\FrogForest.wav");

	//soundList.emplace_back(Sound1);
	//soundList.emplace_back(Sound2);
	//soundList.emplace_back(Sound3);
	//soundList.emplace_back(Sound4);
}

SoundManager::~SoundManager()
{
	delete soundM;
	soundList.clear();
}

void SoundManager::Play(ESound eSound)
{
	Sound2 = soundM->LoadWAV(hWnd, L"Sound\\Dead1.wav");
	//sound->PlayWAV(hWnd, soundList[eSound]);
	soundM->PlayWAV(hWnd,Sound2);
}

void SoundManager::Stop(ESound eSound)
{
	
	//soundM->StopWAV(hWnd, soundList[eSound]);
	//soundM->StopWAV(hWnd, Sound2);

}

void SoundManager::AllStop()
{
	for (auto& it : soundList)
	{
		soundM->StopWAV(hWnd, it);
	}
}
