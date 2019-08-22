
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Limbo.h"
#include "ChildView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

//Gdiplus::RectF progressRect(0, 0, 1000, 30);
//Gdiplus::RectF progressRect(0, 0, 1000, 30);


//RectF 클래스는 실수영역 Rect이다.

// CChildView

CChildView::CChildView()
{
	//CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	//Gdiplus::Graphics MainG(dc);
	//SceneManager::GetInstance()->MainG = &MainG;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

//static int count = 0;

void CChildView::OnPaint() 
{
	/*CLimboApp::bRender = true;*/
	++theApp.CallCount;
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	Gdiplus::Graphics MainG(dc);

	CRect rc;
	GetClientRect(rc);
	Gdiplus::Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());

	Gdiplus::Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Gdiplus::Graphics MemG(&BackBuffer);

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 202, 202, 202));
	MemG.FillRectangle(&WhiteBrush, rc2);

	SceneManager::GetInstance()->GetCurScene()->Render(&MemG);
	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());
	
	
	
	//Image Img(TEXT("Asset\\bg.png"));
	//Image Img2(TEXT("Asset\\ed.jpg"));
	//static float delta = 1.f;
	//if (ProgressRect2.Width != ProgressRect.Width)
	//{
	//	delta -= 0.1f;
	//	ProgressRect.Width =  + Lerp(0, 100, delta);
	//}
	//else
	//	delta = 1.f;

	//MemG.DrawImage(&Img, ProgressRect, 0, 0, defines.screenSizeY, 30, Gdiplus::Unit::UnitPixel);
	//MemG.DrawImage(&Img2, ProgressRect2, 0, 0, defines.screenSizeY, 30, Gdiplus::Unit::UnitPixel);
	//
	//CMemDC memDC(dc, this);
	//CBrush br(RGB(0, 0, 255));

	//memDC.GetDC().FillRect(rc, &br);

	//DWORD delta = GetTickCount() - theApp.PrevTick;
	//DWORD value = delta == 0 ? 0 :  1000 / delta;
	//memDC.GetDC().SetTextColor(RGB(255, 0, 0));

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//SceneManager::GetInstance().RenderScene(&memDC.GetDC());

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	//CString temp;
	//temp.Format(TEXT("%d"), value);
	//memDC.GetDC().DrawText(temp, rc, DT_LEFT | DT_VCENTER);

	//CLimboApp::bRender = false;
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CLimboApp::FuncThread, NULL);

	return 0;
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (SceneManager::GetInstance()->GetCurScene()->tag == ESceneTag::eEndScene)
	{
		EndScene* endScene = reinterpret_cast<EndScene*>(SceneManager::GetInstance()->GetCurScene());
		endScene->SendKeyDown(nChar, nRepCnt, nFlags);
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
