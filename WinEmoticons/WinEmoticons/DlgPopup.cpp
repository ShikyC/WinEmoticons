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
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPopup::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgPopup 消息处理程序

int CDlgPopup::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE;
}

LRESULT CDlgPopup::OnNcHitTest(CPoint point)
{
	CDialog::OnNcHitTest(point);
	return HTCAPTION;
}

void CDlgPopup::PopupWindow()
{
	ShowWindow(SW_SHOWNOACTIVATE);
}

void CDlgPopup::HideWindow()
{
	ShowWindow(SW_HIDE);
}

void CDlgPopup::OnBnClickedButton1()
{
	// 
	SendEmoticon(_T("ﾍ(￣ω￣ﾍ)"));
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