#pragma once
#include "MySocket.h"

class CMySocketClientDlg : public CDialogEx
{
public:
	CMySocketClientDlg(CWnd* pParent = nullptr);	


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSOCKETCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	



protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_recv_text;

	CMySocket m_client_sock;

public:
	void InitSocket();
	CString m_send_text;
	afx_msg void OnBnClickedButton1();
	LRESULT OnRecvText(WPARAM wParam,LPARAM lParam);
	CString AnsiToUnicode(char * szAnsi);
	char* UsrCStringToChar(CString str);
	CString m_str_ip;
	CString m_str_port;
	afx_msg void OnBnClickedConnect();
	void RecvText(CMySocket& sock);
};
