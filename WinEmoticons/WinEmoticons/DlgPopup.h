#include "WETabCtrl.h"
#pragma once


// CDlgPopup �Ի���

class CDlgPopup : public CDialog
{
	DECLARE_DYNAMIC(CDlgPopup)

public:
	CDlgPopup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPopup();

	void PopupWindow();
	void HideWindow();

	void SendEmoticon(CString strText);

	CWETabCtrl m_wndTab;

	int m_nHotKeyId;
	CWnd *m_pForeWnd;
	CWnd *m_pFocusedControl;
// �Ի�������
	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMsgTabItemHit(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnHotKey( WPARAM wParam,LPARAM lParam );
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
