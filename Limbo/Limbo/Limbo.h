﻿
// Limbo.h: Limbo 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CLimboApp:
// 이 클래스의 구현에 대해서는 Limbo.cpp을(를) 참조하세요.
//

class CLimboApp : public CWinApp
{
public:
	CLimboApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void EndGameProcess();
// 구현입니다.
	static DWORD PrevTick;
	static bool bRender;

	static DWORD StaticTick;
	static int CallCount;

	static bool bGameProcess;
public:
	afx_msg void OnAppAbout();
	static UINT FuncThread(LPVOID pParam);
	DECLARE_MESSAGE_MAP()

};

extern CLimboApp theApp;
