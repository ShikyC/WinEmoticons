#pragma once
#include "afxwin.h"
#include "ConfigManager.h"


// CDlgEditEmoticons

class CDlgEditEmoticons : public CDialog
{
	DECLARE_DYNAMIC(CDlgEditEmoticons)

public:
	CDlgEditEmoticons(CWnd* pParent = NULL);   // 
	virtual ~CDlgEditEmoticons();

// 
	enum { IDD = IDD_EDIT_EMOTICONS };

protected:
	CFont m_font;
    CListBox m_lbxGroup;
    CListBox m_lbxEmos;
    CButton m_btnAddEmo;
    CButton m_btnDelEmo;
	CButton m_btnModEmo;
	CButton m_btnLeftEmo;
	CButton m_btnRightEmo;
	CButton m_btnDelGroup;
	CButton m_btnRenGroup;
	CButton m_btnLeftGroup;
	CButton m_btnRightGroup;
	CConfigManager::_tag_emoticons m_emoticons;
	void showEmoCtrlsVisible(BOOL bVisble);
	POSITION getGroupPos(int nIndex);
	POSITION getEmoPos(int nIndex,CConfigManager::_tag_emoticons::_tag_page &curPage);
	void addGroup(CString strName);
	void addEmo(CString strEmo);
	void reloadData(CConfigManager::_tag_emoticons &emoticons);
	void clearAll();

    virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editRow;
	CEdit m_editCol;
	int m_nRowCount;
	int m_nColCount;
	afx_msg void OnBnClickedAddgroup();
	afx_msg void OnBnClickedDelgroup();
	afx_msg void OnBnClickedModgroup();
	afx_msg void OnBnClickedLeftgroup();
	afx_msg void OnBnClickedRightgroup();
	afx_msg void OnBnClickedAddemo();
	afx_msg void OnBnClickedDelemo();
	afx_msg void OnOK();
	afx_msg void OnLbnSelchangeListGroup();
	afx_msg void OnBnClickedModemo();
	afx_msg void OnBnClickedLeftemo();
	afx_msg void OnBnClickedRightemo();
	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedOk();
	CStatic m_wndGroupEmoticon;
};