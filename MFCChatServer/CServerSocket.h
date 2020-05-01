#pragma once

#include <afxSock.h>

class CServerSocket :
	public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	virtual void OnAccept(int nErrorCode);
};

