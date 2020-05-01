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

	if (!nErrorCode) {
		
		// 获取主窗口
		CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

		char recvBuf[MSGBUF_LEN];
		
		// 接收数据
		int ret = Receive(recvBuf, MSGBUF_LEN);

		// 接收出错
		if (ret == SOCKET_ERROR) {
			TRACE("###Receive error: %d", GetLastError());
		}

		// 把char数组转成CString
		USES_CONVERSION;
		CString strMsg = (CString)A2W(recvBuf);

		// 客户端名称
		CString strCliName = L"client";
		// 获取当前时间
		dlg->m_time = CTime::GetCurrentTime();

		// 把当前时间转成字符串
		CString strTime = dlg->m_time.Format("%X ");

		// 字符串格式: 时间 客户端名称: 消息
		strMsg = strTime + strCliName + L": " + strMsg;
		
		// 把数据添加到消息记录
		dlg->m_msgRecord.AddString(strMsg);

		// 自动回复 
		dlg->AutoReply();
	}
}
