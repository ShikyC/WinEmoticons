#include "stdafx.h"
#include "MsgBox.h"

void CMsgBox::Error( CString strMsg,HWND hwndParent /*= NULL*/ )
{
    ::MessageBox(hwndParent,strMsg,_T("����"),MB_OK|MB_ICONERROR);
}

void CMsgBox::Info( CString strMsg,HWND hwndParent /*= NULL*/ )
{
    ::MessageBox(hwndParent,strMsg,_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
}