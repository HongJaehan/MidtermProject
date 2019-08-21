#include "pch.h"
#include "MCISound.h"

MCISound::MCISound()
{

}

MCISound::~MCISound()
{

}

DWORD MCISound::LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;

	mciOpen.lpstrElementName = lpszWave;
	mciOpen.lpstrDeviceType = L"WaveAudio";

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)& mciOpen);

	if (Result)
		return Result;

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}