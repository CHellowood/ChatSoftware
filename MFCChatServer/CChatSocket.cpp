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

		
	// ��ȡ������
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	char recvBuf[MSGBUF_LEN];
		
	// ��������
	int ret = Receive(recvBuf, MSGBUF_LEN);

	// ���ճ���
	if (ret == SOCKET_ERROR) {
		TRACE("###Receive error: %d", GetLastError());
		return;
	}

	// ��char����ת��CString
	USES_CONVERSION;
	CString strMsg = (CString)A2W(recvBuf);

	CString strShow = dlg->CombStr(L"", strMsg);
		
	// ��������ӵ���Ϣ��¼
	dlg->m_msgRecord.AddString(strShow);

	// �Զ��ظ� 
	dlg->AutoReply();
	
	CAsyncSocket::OnReceive(nErrorCode);
}
