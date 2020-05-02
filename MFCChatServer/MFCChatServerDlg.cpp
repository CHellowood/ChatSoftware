
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
	, m_server(NULL), m_chat(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCChatServerDlg::~CMFCChatServerDlg() 
{
	if (m_server) delete m_server;
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGRECORD_LIST, m_msgRecord);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_AUTOREPLY_RADIO, &CMFCChatServerDlg::OnBnClickedAutoreplyRadio)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化网络
	AfxSocketInit();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 按启动按钮
void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strPort, strIP;

	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	//GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	if (strPort.IsEmpty()) {
		MessageBox(L"端口为空!");
		return;
	}

	USES_CONVERSION;
	LPCSTR csPort = (LPCSTR)T2A(strPort);
	//LPCSTR csIP = (LPCSTR)T2A(strIP);

	TRACE("###CMFCChatServerDlg::OnBnClickedStartBtn");
	//TRACE("port: %s ip: %s", csPort, csIP);
	TRACE("###port: %s", csPort);

	// 创建服务端监听套接字
	if (!m_server) {
		
		m_server = new CServerSocket;

		// 内存申请失败
		if (!m_server) {
			TRACE("###m_server new CServerSocket failed!");
			return;
		}

		// 把字符串转成整数
		int iPort = _ttoi(strPort);
		// 创建套接字
		bool ret = m_server->Create(iPort);

		// 创建失败
		if (!ret) {
			TRACE("###m_server create error: %d", GetLastError());
			delete m_server;
			return;
		}

		// 开始监听连接请求
		ret = m_server->Listen();
		
		// 监听失败
		if (!ret) {
			TRACE("###m_server listen error: %d", GetLastError());
			delete m_server;
			return;
		}

		
		CString strShow = CombStr(L"", L"服务器启动成功!");

		// 把字符串添加到消息记录里
		m_msgRecord.AddString(strShow);
	}
}

// 按自动回复按钮
void CMFCChatServerDlg::OnBnClickedAutoreplyRadio()
{
	// 获取自动回复按钮
	CButton* autoReply = (CButton*)GetDlgItem(IDC_AUTOREPLY_RADIO);
	// 设置为相反的状态
	autoReply->SetCheck(!(autoReply->GetCheck()));
}

// 实现自动回复
void CMFCChatServerDlg::AutoReply()
{
	TRACE("###CMFCChatServerDlg::AutoReply");

	// 自动回复按钮被选中
	if (((CButton*)GetDlgItem(IDC_AUTOREPLY_RADIO))->GetCheck() == BST_CHECKED) {
		// 获取消息框内容
		CString strMsg;
		GetDlgItem(IDC_MSG_EDIT)->GetWindowText(strMsg);

		// 消息为空
		if (strMsg.IsEmpty()) return;

		CString strNickname = L"server";
		strNickname += L"[自动回复]";

		// 拼接要发送消息
		CString strSendBuf = CombStr(strNickname, strMsg, false);

		// CString转成char*
		USES_CONVERSION;
		char* csSendBuf = (char*)T2A(strSendBuf);
	
		// 发送消息
		int ret = m_chat->Send(csSendBuf, MSGBUF_LEN);
		
		// 发送出错
		if (ret == SOCKET_ERROR) {
			TRACE("###Send error: %d", GetLastError());
			MessageBox(L"发送出错!");
			return;
		}

		// -----在消息记录里显示发送的消息-----

		CString strShow = CombStr(strNickname, strMsg);

		// 添加到消息记录
		m_msgRecord.AddString(strShow);

		// 更新控件数据
		UpdateData();
	}
}

// 按发送按钮
void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	TRACE("###CMFCChatServerDlg::OnBnClickedSendBtn");

	CString strNickname = L"server"; // 昵称
	CString strMsg;                  // 消息

	// 获取指定控件的文本
	GetDlgItemText(IDC_MSG_EDIT, strMsg);

	// 消息为空
	if (strMsg.IsEmpty()) return;

	// 拼接要发送的消息
	CString strSendBuf = CombStr(strNickname, strMsg, false);

	// 把CString转成char*
	USES_CONVERSION;
	char* csSendBuf = (char*)T2A(strSendBuf);

	// 发送消息
	int ret = m_chat->Send(csSendBuf, MSGBUF_LEN, 0);

	if (ret == SOCKET_ERROR) {
		TRACE("###Send error: %d", GetLastError());
		MessageBox(L"发送出错!");
		return;
	}

	// 拼接在消息记录里显示的字符串
	CString strShow = CombStr(strNickname, strMsg);

	m_msgRecord.AddString(strShow);

	// 把输入框的内容清空
	SetDlgItemText(IDC_MSG_EDIT, L"");

	UpdateData(FALSE);
}

// 消息字符串拼接
CString CMFCChatServerDlg::CombStr(const CString& strNickname,
	const CString& strMsg, bool isAddTime)
{
	CString strTime = L"";

	if (isAddTime) {
		// 获取当前时间并把当前时间转成字符串
		// 时间字符串带了一个空格                            
		strTime = CTime::GetCurrentTime().Format("%X ");
	}

	// 如果昵称为空, 则等于 (L"") , 否则等于 (昵称 + ": ")
	CString strNick = strNickname.IsEmpty() ? L"" : strNickname + L": ";

	// 拼接字符串, 格式: 时间 + 空格 + 昵称 + ": " + 消息
	CString strRet = strTime + strNick + strMsg;

	return strRet;
}
