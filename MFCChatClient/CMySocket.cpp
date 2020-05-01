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
	
	CString str;
	// 获取当前时间
	dlg->m_time = CTime::GetCurrentTime();
	
	// 把当前时间转成字符串
	str = dlg->m_time.Format("%X ");
	
	if (nErrorCode != SOCKET_ERROR) {
		str += L"连接成功!";
	}
	else {
		str += L"连接失败!";
	}

	// 添加到消息记录(或改成弹出一个窗口, MessageBox(str))
	dlg->m_msgRecord.AddString(str);

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
		}

		// 把char数组转成CString
		USES_CONVERSION;
		CString strMsg = (CString)A2T(csRecvBuf);

		// 服务端名称
		CString strSerName = L"server";

		// 获取当前时间
		dlg->m_time = CTime::GetCurrentTime();

		// 把当前时间转成字符串
		CString strTime = dlg->m_time.Format("%X ");

		// 消息格式: 时间 名称: 消息
		strMsg = strTime + strSerName + L": " + strMsg;


		// 添加到消息记录
		dlg->m_msgRecord.AddString(strMsg);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
