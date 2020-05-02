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

	// ��ȡ������
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	
	CString strShow;

	if (nErrorCode != SOCKET_ERROR) {
		strShow = dlg->CombStr(L"", L"���ӳɹ�!");
	}
	else {
		strShow = dlg->CombStr(L"", L"����ʧ��!");
	}

	// ��ӵ���Ϣ��¼(��ĳɵ���һ������, MessageBox(str))
	dlg->m_msgRecord.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("###CMySocket::OnReceive");

	if (!nErrorCode) {

		// ��ȡ������
		CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

		// ��������(��Ϣ)
		char csRecvBuf[MSGBUF_LEN];
		int ret = Receive(csRecvBuf, MSGBUF_LEN);
		
		// ���ճ���
		if (ret == SOCKET_ERROR) {
			TRACE("###Receive error: %d", GetLastError());
			return;
		}

		// ��char����ת��CString
		USES_CONVERSION;
		CString strMsg = (CString)A2T(csRecvBuf);

		CString strShow = dlg->CombStr(L"", strMsg);

		// ��ӵ���Ϣ��¼
		dlg->m_msgRecord.AddString(strShow);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
