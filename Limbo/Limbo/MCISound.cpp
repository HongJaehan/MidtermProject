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
	//DWORD Result;
	MCIERROR mciError;

	mciOpen.lpstrElementName = lpszWave;
	mciOpen.lpstrDeviceType = L"WaveAudio";

	mciError = mciSendCommand((DWORD)(LPVOID)nullptr, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)& mciOpen);

	if (mciError)
		MessageBox(hWnd, L"Open Error!", L"Error", MB_OK);

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	return wDeviceID;
}

void MCISound::PlayWAV(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlay);

	if (mciError)
		MessageBox(hWnd, L"Play Error!", L"Error", MB_OK);
}

void MCISound::PlayWAV_Repeat(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlay);

	if (mciError)
		MessageBox(hWnd, L"Play Error!", L"Error", MB_OK);
}

void MCISound::StopWAV(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_STOP, MCI_WAIT, (DWORD)(LPVOID)& mciGenericParms);

	if (mciError)
		MessageBox(hWnd, L"Stop Error!", L"Error", MB_OK);
}

void MCISound::PauseWAV(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)(LPVOID)& mciGenericParms);

	if (mciError)
		MessageBox(hWnd, L"Pause Error!", L"Error", MB_OK);
}

void MCISound::ResumeWAV(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_RESUME, MCI_WAIT, (DWORD)(LPVOID)& mciGenericParms);

	if (mciError)
		MessageBox(hWnd, L"Resume Error!", L"Error", MB_OK);
}

void MCISound::CloseWAV(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_CLOSE, MCI_WAIT, (DWORD)(LPVOID)& mciGenericParms);

	if (mciError)
		MessageBox(hWnd, L"Close Error!", L"Error", MB_OK);
}

void MCISound::MoveStartPosition(HWND hWnd, DWORD dwID)
{
	MCIERROR mciError;

	mciPlay.dwCallback = (DWORD)hWnd;
	mciError = mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)& mciSeek);

	if (mciError)
		MessageBox(hWnd, L"Set Length Format Error!", L"Error", MB_OK);
}

//DWORD MCISound::MoveStartCurrentPosition(HWND hWnd, DWORD dwID)
//{
//	MCIERROR mciError;
//
//	mciStatus.dwItem = MCI_STATUS_POSITION;
//	mciError = mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)& mciStatus);
//
//	if (mciError)
//		MessageBox(hWnd, L"Status Position Error!", L"Error", MB_OK);
//
//	return mciStatus.dwReturn;
//}
//
//void MCISound::SetCurrentPosition(HWND hWnd, DWORD dwID, DWORD dwPos)
//{
//	MCIERROR mciError;
//
//	mciSeek.dwTo = dwPos;
//	mciError = mciSendCommand(dwID, MCI_SEEK, MCI_TO, (DWORD)& mciSeek);
//
//	if (mciError)
//		MessageBox(hWnd, L"Set Length Format Error!", L"Error", MB_OK);
//}
