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
		
		// ��ȡ������
		CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

		char recvBuf[MSGBUF_LEN];
		
		// ��������
		int ret = Receive(recvBuf, MSGBUF_LEN);

		// ���ճ���
		if (ret == SOCKET_ERROR) {
			TRACE("###Receive error: %d", GetLastError());
		}

		// ��char����ת��CString
		USES_CONVERSION;
		CString strMsg = (CString)A2W(recvBuf);

		// �ͻ�������
		CString strCliName = L"client";
		// ��ȡ��ǰʱ��
		dlg->m_time = CTime::GetCurrentTime();

		// �ѵ�ǰʱ��ת���ַ���
		CString strTime = dlg->m_time.Format("%X ");

		// �ַ�����ʽ: ʱ�� �ͻ�������: ��Ϣ
		strMsg = strTime + strCliName + L": " + strMsg;
		
		// ��������ӵ���Ϣ��¼
		dlg->m_msgRecord.AddString(strMsg);

		// �Զ��ظ� 
		dlg->AutoReply();
	}
}
