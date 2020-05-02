#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("###CServerSocket::OnAccept");

	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	
	CString strShow;

	dlg->m_chat = new CChatSocket;

	// 接受连接
	if (!Accept(*(dlg->m_chat))) {
		TRACE("###Accept error: %d", GetLastError());
		strShow = dlg->CombStr(L"", L"客户端连接失败!");
	}
	else {
		strShow = dlg->CombStr(L"", L"客户端连接成功!");
	}

	// 把字符串添加到消息记录里
	dlg->m_msgRecord.AddString(strShow);

	CAsyncSocket::OnAccept(nErrorCode);
}
