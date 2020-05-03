#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	TRACE("###CChatSocket::OnReceive");

		
	// 获取主窗口
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	char recvBuf[MSGBUF_LEN];
		
	// 接收数据
	int ret = Receive(recvBuf, MSGBUF_LEN);

	// 接收出错
	if (ret == SOCKET_ERROR) {
		TRACE("###Receive error: %d", GetLastError());
		return;
	}

	// 把char数组转成CString
	USES_CONVERSION;
	CString strMsg = (CString)A2W(recvBuf);

	CString strShow = dlg->CombStr(L"", strMsg);
		
	// 把数据添加到消息记录
	dlg->m_msgRecord.AddString(strShow);

	// 自动回复 
	dlg->AutoReply();
	
	CAsyncSocket::OnReceive(nErrorCode);
}
