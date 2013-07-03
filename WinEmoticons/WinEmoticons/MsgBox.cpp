#include "stdafx.h"
#include "MsgBox.h"

void CMsgBox::Error( CString strMsg,CWnd *pParent /*= NULL*/ )
{
    ::MessageBox(pParent->GetSafeHwnd(),strMsg,_T("����"),MB_OK|MB_ICONERROR);
}

void CMsgBox::Info( CString strMsg,CWnd *pParent /*= NULL*/ )
{
    ::MessageBox(pParent->GetSafeHwnd(),strMsg,_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
}