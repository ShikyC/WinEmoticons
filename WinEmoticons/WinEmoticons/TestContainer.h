#pragma once
#include "afxwin.h"
#include "WETabCtrl.h"


// CTestContainer �Ի���

class CTestContainer : public CDialog
{
	DECLARE_DYNAMIC(CTestContainer)

public:
	CTestContainer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestContainer();

// �Ի�������
	enum { IDD = IDD_TESTCONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWETabCtrl m_wndWETabCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
};
