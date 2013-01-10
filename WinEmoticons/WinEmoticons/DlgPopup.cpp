// DlgPopup.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgPopup.h"


// CDlgPopup
#define IDC_TAB 1

IMPLEMENT_DYNAMIC(CDlgPopup, CDialog)

CDlgPopup::CDlgPopup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPopup::IDD, pParent)
{
	m_pForeWnd = NULL;
	m_pFocusedControl = NULL;
}

CDlgPopup::~CDlgPopup()
{

	::UnregisterHotKey(GetSafeHwnd(), m_nHotKeyId);
}

void CDlgPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPopup, CDialog)
	ON_WM_MOUSEACTIVATE()
	ON_WM_CREATE()
	ON_MESSAGE(CWETabCtrl::MSG_HITITEM,OnMsgTabItemHit)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

int CDlgPopup::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}

void CDlgPopup::PopupWindow()
{
	ShowWindow(SW_SHOWNOACTIVATE);
	if (GetActiveWindow() == this)
	{
		OnActivate(WA_ACTIVE,NULL,FALSE);
	}
}

void CDlgPopup::HideWindow()
{
	ShowWindow(SW_HIDE);
}

int CDlgPopup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//
	m_wndTab.Create(CRect(0,0,lpCreateStruct->cx,lpCreateStruct->cy),this,IDC_TAB);

	CWETabPage *pPage1 = m_wndTab.AppendPage(_T("Page1"));
	m_wndTab.AppendPage(_T("Page2"));
	m_wndTab.AppendPage(_T("Page3"));
	pPage1->AppendItem(_T("ﾍ(￣ω￣ﾍ)"));
	pPage1->AppendItem(_T("(≧ω≦)b"));
	pPage1->AppendItem(_T("（｀・ω・´）"));
	pPage1->AppendItem(_T("_(:3」∠)_"));

	//
	m_nHotKeyId =  ::GlobalAddAtom(_T("WinEmoticonsHotkey")) - 0xC000;
	while(!::RegisterHotKey(GetSafeHwnd(), m_nHotKeyId, MOD_CONTROL, 'E'))
	{
		::UnregisterHotKey(NULL, m_nHotKeyId);
	}

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
void CDlgPopup::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	this->SetWindowPos(
		&CWnd::wndTopMost,
		pRect->left,
		pRect->top,
		pRect->right - pRect->left,
		pRect->bottom - pRect->top,
		SWP_SHOWWINDOW|SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOSENDCHANGING);

	CRect rc;
	GetClientRect(&rc);
	m_wndTab.MoveWindow(rc,TRUE);
}

BOOL CDlgPopup::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

LRESULT CDlgPopup::OnHotKey( WPARAM wParam,LPARAM lParam )
{
	POINT ptCursor;
	if(::GetCursorPos(&ptCursor))
	{
		m_pForeWnd = GetForegroundWindow();

		DWORD activeWindowThread = ::GetWindowThreadProcessId(m_pForeWnd->GetSafeHwnd(), NULL);
		DWORD thisWindowThread = ::GetWindowThreadProcessId(GetSafeHwnd(), NULL);

		if(::AttachThreadInput(thisWindowThread, activeWindowThread, TRUE))
		{
			m_pFocusedControl = GetFocus();
			::AttachThreadInput(thisWindowThread, activeWindowThread, FALSE);
		}

		// Toggle show popup
		if (!IsWindowVisible())
		{
			CRect rcWindow;
			GetWindowRect(rcWindow);
			MoveWindow(ptCursor.x,ptCursor.y,rcWindow.Width(),rcWindow.Height());
			PopupWindow();
		}
		else
		{
			HideWindow();
		}
	}

	return 0;
}

void CDlgPopup::SendEmoticon( CString strText )
{
	if (m_pFocusedControl != NULL && m_pFocusedControl->GetSafeHwnd() != NULL)
	{
		for (int i = 0;i < strText.GetLength();i ++)
		{
			m_pFocusedControl->SendMessage(WM_CHAR,WPARAM(strText[i]),LPARAM(0));
		}
	}
}

LRESULT CDlgPopup::OnMsgTabItemHit( WPARAM wParam,LPARAM lParam )
{
	SendEmoticon((LPCTSTR)wParam);
	HideWindow();

	return 0;
}

void CDlgPopup::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	if (nState == WA_ACTIVE)
	{
		DWORD activeWindowThread = ::GetWindowThreadProcessId(m_pForeWnd->GetSafeHwnd(), NULL);
		DWORD thisWindowThread = ::GetWindowThreadProcessId(GetSafeHwnd(), NULL);

		if(::AttachThreadInput(thisWindowThread, activeWindowThread, TRUE))
		{
			m_pForeWnd->SetActiveWindow();
			::AttachThreadInput(thisWindowThread, activeWindowThread, FALSE);
		}
	}
}
