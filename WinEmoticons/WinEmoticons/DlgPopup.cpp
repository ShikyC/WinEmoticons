// DlgPopup.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgPopup.h"
#include "ConfigManager.h"
#include "MsgBox.h"


// CDlgPopup
#define IDC_TAB 1

IMPLEMENT_DYNAMIC(CDlgPopup, CWnd)

CDlgPopup::CDlgPopup(CWnd* pParent /*=NULL*/)
	:m_hwndParent(pParent == NULL ? NULL : pParent->GetSafeHwnd())
{
	m_pForeWnd = NULL;
	m_pFocusedControl = NULL;
}

CDlgPopup::~CDlgPopup()
{

	::UnregisterHotKey(GetSafeHwnd(), m_nHotKeyId);
}
// 
// void CDlgPopup::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialog::DoDataExchange(pDX);
// }


BEGIN_MESSAGE_MAP(CDlgPopup, CWnd)
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

	CRect rcWindow;
	this->GetWindowRect(rcWindow);
	CConfigManager::Inst()->PopWindow.Width = rcWindow.Width();
	CConfigManager::Inst()->PopWindow.Height = rcWindow.Height();
	CConfigManager::Inst()->SaveConfig();
}

void CDlgPopup::Create()
{
	CWnd::CreateEx(
		WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
		AfxRegisterWndClass(NULL),
		_T(""),
		WS_THICKFRAME,
		0,
		0,
		CConfigManager::Inst()->PopWindow.Width,
		CConfigManager::Inst()->PopWindow.Height,
		m_hwndParent,
		NULL);

	//
	m_wndTab.Create(
		CRect(0,0,
			CConfigManager::Inst()->PopWindow.Width,
			CConfigManager::Inst()->PopWindow.Height)
		,this,IDC_TAB);

	// load emoticons
	ReloadEmoticons();

	// 
	ReloadHotkey();
}

int CDlgPopup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->cx = CConfigManager::Inst()->PopWindow.Width;
	lpCreateStruct->cy = CConfigManager::Inst()->PopWindow.Height;
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CDlgPopup::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	//
	if (nType == SIZE_RESTORED && cx != 0 && cy != 0 && m_wndTab.GetSafeHwnd() != NULL)
	{
		CRect rcCtrl(0,0,cx,cy);

		m_wndTab.MoveWindow(rcCtrl,TRUE);
	}
}
void CDlgPopup::OnSizing(UINT fwSide, LPRECT pRect)
{
	CWnd::OnSizing(fwSide, pRect);

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
	if (CConfigManager::Inst()->IsOnConfig)
	{
		return 0;
	}

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

void CDlgPopup::ReloadEmoticons()
{
	m_wndTab.RemoveAllPages();

	for (POSITION pos = CConfigManager::Inst()->Emoticons.Pages.GetHeadPosition();
		pos != NULL;)
	{
		const CConfigManager::_tag_emoticons::_tag_page &page =
			CConfigManager::Inst()->Emoticons.Pages.GetNext(pos);

		CWETabPage *pWEPage = m_wndTab.AppendPage(page.Caption);
		for (POSITION posItem = page.Items.GetHeadPosition();posItem != NULL;)
		{
			const CConfigManager::_tag_emoticons::_tag_page::_tag_item &item = 
				page.Items.GetNext(posItem);

			pWEPage->AppendItem(item.Content);
		}
	}
}

BOOL CDlgPopup::ReloadHotkey()
{
	UINT nModifier = 0;
	UINT nVKey = 0;
	if (!CConfigManager::ParseCombineKeys(
		CConfigManager::Inst()->AccerateKey.PopSelect,
		nModifier,
		nVKey))
	{
		CString strErr;
		strErr.Format(_T("Cannot parse accerate key <%s>"),CConfigManager::Inst()->AccerateKey.PopSelect);
		CMsgBox::Error(strErr,this);

		return FALSE;
	}

	m_nHotKeyId =  ::GlobalAddAtom(_T("WinEmoticonsHotkey")) - 0xC000;
	while(!::RegisterHotKey(GetSafeHwnd(), m_nHotKeyId, nModifier, nVKey))
	{
		::UnregisterHotKey(NULL, m_nHotKeyId);

		CString strErr;
		strErr.Format(_T("Cannot register hot key <%s>"),CConfigManager::Inst()->AccerateKey.PopSelect);
		CMsgBox::Error(strErr,this);
		return FALSE;
	}

	return TRUE;
}