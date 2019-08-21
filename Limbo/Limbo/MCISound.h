#pragma once
//#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

//#include "Digitalv.h"

class MCISound
{
public:
	MCISound();
	~MCISound();
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	MCI_STATUS_PARMS mciStatus;
	UINT wDeviceID = 0;

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
};

