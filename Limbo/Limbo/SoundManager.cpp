#include "pch.h"
#include "SoundManager.h"
#include "Limbo.h"

SoundManager::SoundManager()
{
	soundM = new MCISound();
	hWnd = theApp.GetMainWnd()->GetSafeHwnd();
	//Sound2 = soundM->LoadWAV(hWnd, L"Sound\\Dead1.wav");
	DWORD Sound1 = soundM->LoadWAV(hWnd, L"Sound\\walking-1.wav");
	DWORD Sound2 = soundM->LoadWAV(hWnd, L"Sound\\Dead1.wav");
	DWORD Sound3 = soundM->LoadWAV(hWnd, L"Sound\\FrogForest.wav");
	DWORD Sound4 = soundM->LoadWAV(hWnd, L"Sound\\Cave.wav");
	DWORD Sound5 = soundM->LoadWAV(hWnd, L"Sound\\Rock.wav");

	soundList.emplace_back(Sound1);
	soundList.emplace_back(Sound2);
	soundList.emplace_back(Sound3);
	soundList.emplace_back(Sound4);
	soundList.emplace_back(Sound5);


}

SoundManager::~SoundManager()
{
	delete soundM;
	soundList.clear();
}

void SoundManager::Play(ESound eSound)
{
	soundM->PlayWAV(hWnd, soundList[eSound]);
	//soundM->PlayWAV(hWnd,Sound2);
}

void SoundManager::Stop(ESound eSound)
{
	soundM->MoveStartPosition(hWnd, soundList[eSound]);
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
