#include "DlgPopup.h"
// WinEmoticonsDlg.h : ͷ�ļ�
//

#pragma once


// CWinEmoticonsDlg �Ի���
class CWinEmoticonsDlg : public CDialog
{
// ����
public:
	CWinEmoticonsDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CWinEmoticonsDlg();

// �Ի�������
	enum { IDD = IDD_WINEMOTICONS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int m_nHotKeyId;
	CMenu m_menu;
	CWnd *m_pForeWnd;
	CWnd *m_pFocusedControl;
	CDlgPopup m_dlgPopup;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
