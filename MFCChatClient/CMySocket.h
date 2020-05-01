#pragma once

#include <afxsock.h>

// 保存消息的数组的长度
#define MSGBUF_LEN 100

class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

	// 当调用Connect函数后, 系统会自动调用该函数
	virtual void OnConnect(int nErrorCode); 
	// 当调用Receive函数后, 系统会自动调用该函数
	virtual void OnReceive(int nErrorCode); 
};

