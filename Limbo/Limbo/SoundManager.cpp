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
	DWORD Sound6 = soundM->LoadWAV(hWnd, L"Sound\\Rope.wav"); // 로프 끊길때
	DWORD Sound7 = soundM->LoadWAV(hWnd, L"Sound\\Slide.wav"); // 무언가 끄는 소리 (덫, 시체..)
	DWORD Sound8 = soundM->LoadWAV(hWnd, L"Sound\\FallenRock.wav"); // 떨어지는 지형
	DWORD Sound9 = soundM->LoadWAV(hWnd, L"Sound\\FelledTrap.wav"); // 떨어지는 Trap
	DWORD Sound10 = soundM->LoadWAV(hWnd, L"Sound\\Spider.wav"); // 거미

	soundList.emplace_back(Sound1);
	soundList.emplace_back(Sound2);
	soundList.emplace_back(Sound3);
	soundList.emplace_back(Sound4);
	soundList.emplace_back(Sound5);
	soundList.emplace_back(Sound6);
	soundList.emplace_back(Sound7);
	soundList.emplace_back(Sound8);
	soundList.emplace_back(Sound9);
	soundList.emplace_back(Sound10);
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
