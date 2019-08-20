
// Limbo.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Limbo.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLimboApp

BEGIN_MESSAGE_MAP(CLimboApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CLimboApp::OnAppAbout)
END_MESSAGE_MAP()


// CLimboApp 생성

CLimboApp::CLimboApp() noexcept
{
	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Limbo.AppID.NoVersion"));
	
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CLimboApp 개체입니다.

CLimboApp theApp;
DWORD CLimboApp::PrevTick = 0;
bool CLimboApp::bRender = false;
int CLimboApp::CallCount = 0;
DWORD CLimboApp::StaticTick = 0;


// CLimboApp 초기화
ULONG_PTR gpToken;
BOOL CLimboApp::InitInstance()
{
	CWinApp::InitInstance();

	Gdiplus::GdiplusStartupInput start;
	Gdiplus::GdiplusStartup(&gpToken, &start, nullptr);
	EnableTaskbarInteraction(FALSE);

	//_CrtSetBreakAlloc(356);
	//_CrtMemDumpAllObjectsSince(0); 


	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));


	// 주 창을 만들기 위해 이 코드에서는 새 프레임 창 개체를
	// 만든 다음 이를 애플리케이션의 주 창 개체로 설정합니다.
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 프레임을 만들어 리소스와 함께 로드합니다.
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);





	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CLimboApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	Gdiplus::GdiplusShutdown(gpToken);
	return CWinApp::ExitInstance();
}

// CLimboApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CLimboApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//UINT CLimboApp::FuncThread(LPVOID pParam)
//{
//	while (1)
//	{
//		DWORD tick = GetTickCount();
//		DWORD Delta = tick - PrevTick;
//		static DWORD AddDelta = 0;
//		PrevTick = tick;
//		StaticTick += Delta;
//		AddDelta += Delta;
//		static DWORD minDelta = 1000 / 60;
//
//		if (CMainFrame * MainFrm = static_cast<CMainFrame*>(theApp.GetMainWnd()))
//		{
//			if (AddDelta < minDelta)
//			{
//				continue;
//				//   Sleep(minDelta - AddDelta);
//			}
//			else
//			{
//				if (AddDelta > 100)
//					AddDelta = 0;
//				else
//					AddDelta = AddDelta - minDelta;
//				Delta = minDelta;
//			}
//
//			// Update
//			++CallCount;
//			SceneManager::GetInstance()->GetCurScene()->Update(Delta);
//			// Render
//			CChildView* view = MainFrm->GetView();
//
//			CRect rc;
//			view->GetClientRect(rc);
//			if (!rc.IsRectNull())
//				view->InvalidateRect(rc);
//
//			if (StaticTick > 1000)
//			{
//				printf("CallCount: %d \n", CallCount);
//				CallCount = 0;
//				StaticTick = 0;
//			}
//		}
//
//		Sleep(1);
//
//		// Release
//		//SceneManager::GetInstance().Release();
//	}
//
//	return  -1;
//}


//UINT CLimboApp::FuncThread(LPVOID pParam)
//{
//	CallCount = 0;
//
//	while (1)
//	{
//
//		DWORD tick = GetTickCount();
//		DWORD Delta = tick - PrevTick;
//		PrevTick = tick;
//		static DWORD PrevStaticDelta = GetTickCount();
//		static int AddDelta = 0;
//		
//		//system("cls");
//		//printf("%d", 1000 / Delta);
//		
//
//		if (CMainFrame * MainFrm = static_cast<CMainFrame*>(theApp.GetMainWnd()))
//		{
//			//if (!bRender)
//			{
//				//현재Scene의 Update을 전부 돌려준다.
//				SceneManager::GetInstance()->GetCurScene()->Update(Delta * 0.001f);
//				// Render
//				//Main에서 가져온 CChildView
//				CChildView* view = MainFrm->GetView();
//
//				//++CallCount;
//				CRect rc;
//				//CDC* pDC = view->GetDC();
//				view->GetClientRect(rc);
//
//				if (!rc.IsRectNull())
//					view->Invalidate();
//					//SceneManager::GetInstance()->Render(pDC, rc);
//
//				
//				//pDC->DrawText(temp, rc, DT_LEFT | DT_VCENTER);
//
//				//view->ReleaseDC(pDC);
//				if (GetTickCount() - PrevStaticDelta > 1000)
//				{
//					PrevStaticDelta = GetTickCount();
//					CString temp;
//					temp.Format(TEXT("%d\n"), CallCount);
//					CString temp2;
//					temp2.Format(TEXT("%d\n"), GameManager::GetInstance()->GetPlayerPosX());
//					OutputDebugString(temp.GetBuffer());
//					OutputDebugString(temp2.GetBuffer());
//
//					CallCount = 0;
//				}
//			}
//		}
//		Sleep(1);
//	}
//	return  -1;
//}


UINT CLimboApp::FuncThread(LPVOID pParam)
{
	while (1)
	{
		DWORD tick = GetTickCount();
		DWORD Delta = tick - PrevTick;
		static DWORD AddDelta = 0;
		PrevTick = tick;
		StaticTick += Delta;
		AddDelta += Delta;
		static DWORD minDelta = 1000 / 60;

		if (CMainFrame * MainFrm = static_cast<CMainFrame*>(theApp.GetMainWnd()))
		{
			if (AddDelta < minDelta)
			{
				continue;
				//   Sleep(minDelta - AddDelta);
			}
			else
			{
				if (AddDelta > 100)
					AddDelta = 0;
				else
					AddDelta = AddDelta - minDelta;
				Delta = minDelta;
			}

			// Update
			++CallCount;
			SceneManager::GetInstance()->GetCurScene()->Update(Delta*0.001f);

			// Render
			CChildView* view = MainFrm->GetView();

			
			CRect rc;
			view->GetClientRect(rc);
			if (!rc.IsRectNull())
				view->InvalidateRect(rc);

			//SceneManager::GetInstance()->Render(rc);

			if (StaticTick > 1000)
			{
				CallCount = 0;
				StaticTick = 0;
			}
		}

		Sleep(1);

		//// Release
		//SceneManager::GetInstance().Release();
	}

	return  -1;
}