// DlgPopup.cpp : 实现文件
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgPopup.h"


// CDlgPopup 对话框

IMPLEMENT_DYNAMIC(CDlgPopup, CDialog)

CDlgPopup::CDlgPopup(CWnd *&pwndFocused,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPopup::IDD, pParent),m_pwndFocused(pwndFocused)
{
	
}

CDlgPopup::~CDlgPopup()
{
}

void CDlgPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPopup, CDialog)
	ON_WM_MOUSEACTIVATE()
	ON_WM_NCHITTEST()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_MESSAGE(CWETabCtrl::MSG_HITITEM,OnMsgTabItemHit)
END_MESSAGE_MAP()


// CDlgPopup 消息处理程序

int CDlgPopup::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}

LRESULT CDlgPopup::OnNcHitTest(CPoint point)
{
	if (m_wndTab.HitTest(point) == NULL)
	{
		return HTCAPTION;
	}
	return CDialog::OnNcHitTest(point);
}

void CDlgPopup::PopupWindow()
{
	ShowWindow(SW_SHOWNOACTIVATE);
}

void CDlgPopup::HideWindow()
{
	ShowWindow(SW_HIDE);
}

void CDlgPopup::SendEmoticon( CString strText )
{
	if (m_pwndFocused != NULL && m_pwndFocused->GetSafeHwnd() != NULL)
	{
		for (int i = 0;i < strText.GetLength();i ++)
		{
			m_pwndFocused->SendMessage(WM_CHAR,WPARAM(strText[i]),LPARAM(0));
		}
	}
}
int CDlgPopup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//
	m_wndTab.Create(CWETabCtrl::IDD,this);
	m_wndTab.ShowWindow(SW_SHOW);
	CWETabPage *pPage1 = m_wndTab.AppendPage(_T("Page1"));
	m_wndTab.AppendPage(_T("Page2"));
	m_wndTab.AppendPage(_T("Page3"));
	pPage1->AppendItem(_T("ﾍ(￣ω￣ﾍ)"));
	pPage1->AppendItem(_T("(≧ω≦)b"));
	pPage1->AppendItem(_T("（｀・ω・´）"));
	pPage1->AppendItem(_T("_(:3」∠)_"));

	return 0;
}

void CDlgPopup::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//
	if (nType == SIZE_RESTORED && cx != 0 && cy != 0 && m_wndTab.GetSafeHwnd() != NULL)
	{
		CRect rcCtrl(0,0,cx,cy);

		m_wndTab.MoveWindow(rcCtrl,TRUE);
	}
}

LRESULT CDlgPopup::OnMsgTabItemHit( WPARAM wParam,LPARAM lParam )
{
	SendEmoticon((LPCTSTR)wParam);
	HideWindow();

	return 0;
}