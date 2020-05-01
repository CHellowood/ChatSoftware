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
	
	// ��ȡ��ǰʱ��
	dlg->m_time = CTime::GetCurrentTime();

	// �ѵ�ǰʱ��ת���ַ���
	CString str = dlg->m_time.Format("%X ");

	dlg->m_chat = new CChatSocket;

	// ��������
	if (!Accept(*(dlg->m_chat))) {
		TRACE("###Accept error: %d", GetLastError());
		str += L"�ͻ�������ʧ��!";
	}
	else {
		str += L"�ͻ������ӳɹ�!";
	}

	// ���ַ�����ӵ���Ϣ��¼��
	dlg->m_msgRecord.AddString(str);

	CAsyncSocket::OnAccept(nErrorCode);
}
