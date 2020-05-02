#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{

	// 获取主窗口
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	
	CString strShow;

	if (nErrorCode != SOCKET_ERROR) {
		strShow = dlg->CombStr(L"", L"连接成功!");
	}
	else {
		strShow = dlg->CombStr(L"", L"连接失败!");
	}

	// 添加到消息记录(或改成弹出一个窗口, MessageBox(str))
	dlg->m_msgRecord.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("###CMySocket::OnReceive");

	if (!nErrorCode) {

		// 获取主窗口
		CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

		// 接收数据(消息)
		char csRecvBuf[MSGBUF_LEN];
		int ret = Receive(csRecvBuf, MSGBUF_LEN);
		
		// 接收出错
		if (ret == SOCKET_ERROR) {
			TRACE("###Receive error: %d", GetLastError());
			return;
		}

		// 把char数组转成CString
		USES_CONVERSION;
		CString strMsg = (CString)A2T(csRecvBuf);

		CString strShow = dlg->CombStr(L"", strMsg);

		// 添加到消息记录
		dlg->m_msgRecord.AddString(strShow);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
