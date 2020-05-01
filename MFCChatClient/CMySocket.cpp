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
	
	CString str;
	// ��ȡ��ǰʱ��
	dlg->m_time = CTime::GetCurrentTime();
	
	// �ѵ�ǰʱ��ת���ַ���
	str = dlg->m_time.Format("%X ");
	
	if (nErrorCode != SOCKET_ERROR) {
		str += L"���ӳɹ�!";
	}
	else {
		str += L"����ʧ��!";
	}

	// ��ӵ���Ϣ��¼(��ĳɵ���һ������, MessageBox(str))
	dlg->m_msgRecord.AddString(str);

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
		}

		// ��char����ת��CString
		USES_CONVERSION;
		CString strMsg = (CString)A2T(csRecvBuf);

		// ���������
		CString strSerName = L"server";

		// ��ȡ��ǰʱ��
		dlg->m_time = CTime::GetCurrentTime();

		// �ѵ�ǰʱ��ת���ַ���
		CString strTime = dlg->m_time.Format("%X ");

		// ��Ϣ��ʽ: ʱ�� ����: ��Ϣ
		strMsg = strTime + strSerName + L": " + strMsg;


		// ��ӵ���Ϣ��¼
		dlg->m_msgRecord.AddString(strMsg);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
