
#include "stdafx.h"
#include "MySocketClient.h"
#include "MySocketClientDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()





CMySocketClientDlg::CMySocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYSOCKETCLIENT_DIALOG, pParent)
	, m_recv_text(_T(""))
	, m_send_text(_T(""))
	, m_str_ip(_T(""))
	, m_str_port(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, m_recv_text);
	DDX_Text(pDX, IDC_SEND_TEXT, m_send_text);
	DDX_Text(pDX, IDC_IP, m_str_ip);
	DDX_Text(pDX, IDC_PORT, m_str_port);
}

BEGIN_MESSAGE_MAP(CMySocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMySocketClientDlg::OnBnClickedButton1)
	ON_MESSAGE(SOCKET_EVENT, &CMySocketClientDlg::OnRecvText)
	ON_BN_CLICKED(IDC_CONNECT, &CMySocketClientDlg::OnBnClickedConnect)
END_MESSAGE_MAP()



BOOL CMySocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	InitSocket();
	return TRUE; 
}

void CMySocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



void CMySocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CMySocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMySocketClientDlg::InitSocket()
{
	m_client_sock.AttachCWnd(this);
	if(!m_client_sock.Create())
	{
		MessageBox(L"Failed to create socket");
	}
	return;
}





//send to server
void CMySocketClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	char *buff = NULL;
	buff = UsrCStringToChar(m_send_text);

	m_client_sock.Send(buff,sizeof(buff));
}


//Recv text from server
LRESULT CMySocketClientDlg::OnRecvText(WPARAM wParam, LPARAM lParam)
{
	char recv_buff[1024] = {0};
	int recv_len = 0;
	switch (lParam)
	{
	case ACCEPT:

		break;
	case RECV:
		RecvText(m_client_sock);
		break;
	case SEND:
		m_client_sock.OnSend(0);
		break;
	case CLOSE:

		break;
	default:
		break;
	}

	return 0;
}


//////////////////////////////////////////////////
//Cstring to char
char* CMySocketClientDlg::UsrCStringToChar(CString str)
{
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char *cs_text = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, cs_text, len, NULL, NULL);
	return cs_text;
}


CString CMySocketClientDlg::AnsiToUnicode(char * szAnsi)
{
	CString str;
	int wcsLen = 0;
	wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
	wszString[wcsLen] = '\0';
	str = wszString;
	delete wszString;
	return str;
}

//connect to server
void CMySocketClientDlg::OnBnClickedConnect()
{
	UpdateData(TRUE);

	if (!m_client_sock.Connect(m_str_ip,_wtoi(m_str_port)))
	{
		MessageBox(L"Failed to connect...");
	}
}


void CMySocketClientDlg::RecvText(CMySocket& sock)
{
	char sz_buff[1024];
	sock.Receive(sz_buff, 1024, 0);
	m_recv_text = AnsiToUnicode(sz_buff);
	UpdateData(FALSE);
}