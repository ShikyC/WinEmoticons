// WinEmoticonsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WinEmoticonsDlg.h"
#include "DlgPopup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_BEGIN	0x500
#define ID_END		ID_BEGIN + 5000
// CWinEmoticonsDlg �Ի���




CWinEmoticonsDlg::CWinEmoticonsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinEmoticonsDlg::IDD, pParent),m_dlgPopup(m_pFocusedControl,this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CWinEmoticonsDlg::~CWinEmoticonsDlg()
{
	m_menu.DestroyMenu();
	::UnregisterHotKey(GetSafeHwnd(), m_nHotKeyId);
}

void CWinEmoticonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinEmoticonsDlg, CDialog)
	ON_WM_PAINT()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_COMMAND_RANGE(ID_BEGIN,ID_END,OnMenuItem)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWinEmoticonsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CWinEmoticonsDlg ��Ϣ�������

BOOL CWinEmoticonsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_dlgPopup.Create(CDlgPopup::IDD,this);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nHotKeyId =  ::GlobalAddAtom(_T("WinEmoticonsHotkey")) - 0xC000;
	while(!::RegisterHotKey(GetSafeHwnd(), m_nHotKeyId, MOD_CONTROL, 'E'))
	{
		::UnregisterHotKey(NULL, m_nHotKeyId);
	}
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

LRESULT CWinEmoticonsDlg::OnHotKey( WPARAM wParam,LPARAM lParam )
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
		if (!m_dlgPopup.IsWindowVisible())
		{
			m_dlgPopup.PopupWindow();
		}
		else
		{
			m_dlgPopup.HideWindow();
		}
		//m_menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RETURNCMD|TPM_NONOTIFY,ptCursor.x,ptCursor.y,this);
	}
	
	return 0;
}

void CWinEmoticonsDlg::OnMenuItem( UINT nID )
{
// 	if (m_pForeWnd != NULL && m_pForeWnd->GetSafeHwnd() != NULL)
// 	{
// 		m_pForeWnd->SetForegroundWindow();
// 	}

	if (m_pFocusedControl != NULL && m_pFocusedControl->GetSafeHwnd() != NULL)
	{
		m_pFocusedControl->SendMessage(WM_CHAR,WPARAM('A'),LPARAM(0));
	}
}
void CWinEmoticonsDlg::OnBnClickedOk()
{
	//OnOK();

	this->ShowWindow(SW_HIDE);
}
