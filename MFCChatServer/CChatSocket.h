#pragma once

#include <afxsock.h>

// ������Ϣ������ĳ���
#define MSGBUF_LEN 100

class CChatSocket :
	public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();

	virtual void OnReceive(int nErrorCode);
};

