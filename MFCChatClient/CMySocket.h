#pragma once

#include <afxsock.h>

// ������Ϣ������ĳ���
#define MSGBUF_LEN 100

class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

	// ������Connect������, ϵͳ���Զ����øú���
	virtual void OnConnect(int nErrorCode); 
	// ������Receive������, ϵͳ���Զ����øú���
	virtual void OnReceive(int nErrorCode); 
};

