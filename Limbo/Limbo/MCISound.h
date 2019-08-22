#pragma once
//#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"

class MCISound
{
public:
	MCISound();
	~MCISound();
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	MCI_STATUS_PARMS mciStatus;
	MCI_GENERIC_PARMS mciGenericParms;
	MCI_SEEK_PARMS mciSeek;
	DWORD wDeviceID = 0;

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
	void PlayWAV(HWND hWnd, DWORD dwID);
	void StopWAV(HWND hWnd, DWORD dwID);
	void PauseWAV(HWND hWnd, DWORD dwID); //일시 정시
	void ResumeWAV(HWND hWnd, DWORD dwID); //일시 정시한 것을 다시 플레이
	void CloseWAV(HWND hWnd, DWORD dwID);
};

