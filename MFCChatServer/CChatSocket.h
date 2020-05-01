#pragma once

#include <afxsock.h>

// 保存消息的数组的长度
#define MSGBUF_LEN 100

class CChatSocket :
	public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();

	virtual void OnReceive(int nErrorCode);
};

