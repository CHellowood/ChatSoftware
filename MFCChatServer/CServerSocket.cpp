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
	
	// 获取当前时间
	dlg->m_time = CTime::GetCurrentTime();

	// 把当前时间转成字符串
	CString str = dlg->m_time.Format("%X ");

	dlg->m_chat = new CChatSocket;

	// 接受连接
	if (!Accept(*(dlg->m_chat))) {
		TRACE("###Accept error: %d", GetLastError());
		str += L"客户端连接失败!";
	}
	else {
		str += L"客户端连接成功!";
	}

	// 把字符串添加到消息记录里
	dlg->m_msgRecord.AddString(str);

	CAsyncSocket::OnAccept(nErrorCode);
}
