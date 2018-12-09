#include "stdafx.h"
#include "MySocket.h"



CMySocket::CMySocket()
{
	pWnd = NULL;

}

CMySocket::~CMySocket()
{
}



void CMySocket::AttachCWnd(CWnd *p_Wnd)
{
	pWnd = p_Wnd;
}

void CMySocket::OnSend(int nErrorCode)
{
	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, SEND);

	CSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, RECV);

	CSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, CLOSE);

	CSocket::OnClose(nErrorCode);
}

void CMySocket::OnAccept(int nErrorCode)
{
	if (pWnd)
		pWnd->SendMessage(SOCKET_EVENT, (WPARAM)this, ACCEPT);

	CSocket::OnAccept(nErrorCode);
}