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

	// ��������
	if (!Accept(*(dlg->m_chat))) {
		TRACE("###Accept error: %d", GetLastError());
		strShow = dlg->CombStr(L"", L"�ͻ�������ʧ��!");
	}
	else {
		strShow = dlg->CombStr(L"", L"�ͻ������ӳɹ�!");
	}

	// ���ַ�����ӵ���Ϣ��¼��
	dlg->m_msgRecord.AddString(strShow);

	CAsyncSocket::OnAccept(nErrorCode);
}
