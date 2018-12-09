#pragma once
#include <afxsock.h>

#pragma once

#define SOCKET_EVENT    WM_USER + 11
#define WM_MYMESSAGE    WM_USER + 12 


enum {
	ACCEPT = 0, 
	SEND = 1, 
	RECV = 2, 
	CLOSE = 3 
};


class CMySocket : public CSocket
{
public:
	CWnd *pWnd;

	CMySocket();
	virtual ~CMySocket();

	void AttachCWnd(CWnd *p_Wnd);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);    //接受连接

};