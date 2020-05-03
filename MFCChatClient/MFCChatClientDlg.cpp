
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
	, m_client(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCChatClientDlg::~CMFCChatClientDlg()
{
	if (m_client) delete m_client;
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGRECORD_LIST, m_msgRecord);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SENDMSG_BTN, &CMFCChatClientDlg::OnBnClickedSendmsgBtn)
	ON_BN_CLICKED(IDC_AUTOREPLY_RADIO, &CMFCChatClientDlg::OnBnClickedAutoreplyRadio)
	ON_BN_CLICKED(IDC_SAVENICKNAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenicknameBtn)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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

	TRACE("###CMFCChatClientDlg::OnInitDialog");

	// 初始化网络
	AfxSocketInit();

	// 初始化配置,    昵称长度 + 1(字符串结束符)
	WCHAR wcsNickname[NICKNAME_LEN+1] = _T(DEFAULT_NICKNAME);
	
	// 设置默认昵称
	SetDlgItemText(IDC_NICKNAME_EDIT, wcsNickname);

	// 获取当前目录
	WCHAR wcsPath[MAX_PATH];
	if (!GetCurrentDirectoryW(MAX_PATH, wcsPath)) {
		TRACE("###GetCurrentDirectoryW error: ", GetLastError());
		return -1;
	}

	// 配置文件路径
	CString strFilePath;
	strFilePath.Format(L"%s//client.ini", wcsPath);

	// 从配置文件里读取昵称
	if (!GetPrivateProfileStringW(L"CLIENT", L"NICKNAME", L"client",
		wcsNickname, NICKNAME_LEN+1, strFilePath)) {

		TRACE("###GetPrivateProfileStringW error: ", GetLastError());
		return -1;
	}

	// 设置昵称
	SetDlgItemText(IDC_NICKNAME_EDIT, wcsNickname);

	// 更新控件数据
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 点击连接按钮
void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strPort, strIP;

	// 获取端口和IP
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	if (strPort.IsEmpty() || strIP.IsEmpty()) {
		MessageBox(L"端口或IP为空!");
		return;
	}

	// CString类型转char*类型
	USES_CONVERSION;
	LPCSTR csPort = (LPCSTR)T2A(strPort);
	LPCSTR csIP = (LPCSTR)T2A(strIP);

	// 在DebugView上显示
	TRACE("###MFCChatClientDlg::OnBnClickedConnectBtn");
	TRACE("###port: %s ip: %s", csPort, csIP);

	// 套接字指针为空时创建套接字
	if (!m_client) {
	
		m_client = new CMySocket;
		
		// 申请内存失败
		if (!m_client) {
			TRACE("###m_client new CMySocket failed!");
			return;
		}

		// 创建套接字
		BOOL ret = m_client->Create();

		// 套接字创建失败
		if (!ret) {
			TRACE("###m_client create error %d", GetLastError());
			delete m_client;
			return;
		}

		// 端口, 把字符串转成整形
		int iPort = _ttoi(strPort);

		// 连接服务端(服务器)
		ret = m_client->Connect(strIP, iPort);

		// 连接服务端(服务器)失败
		if (ret == SOCKET_ERROR) {
			TRACE("###m_client connect error %d", GetLastError());
			delete m_client;
			return;
		}
	}
}


// 点击发送按钮
void CMFCChatClientDlg::OnBnClickedSendmsgBtn()
{
	TRACE("###CMFCChatClientDlg::OnBnClickedSendmsgBtn");

	// 获取消息输入框的消息
	CString strMsg;
	GetDlgItem(IDC_MSG_EDIT)->GetWindowTextW(strMsg);

	// 消息为空
	if (strMsg.IsEmpty()) return;

	// 获取昵称
	CString strNickname;
	GetDlgItemText(IDC_NICKNAME_EDIT, strNickname);

	// 昵称为空
	if (strNickname.IsEmpty()) {
		// 设为默认昵称
		strNickname = _T(DEFAULT_NICKNAME);
	}

	// 拼接要发送的消息
	CString strSendBuf = CombStr(strNickname, strMsg, false);

	USES_CONVERSION;
	char* csSendBuf = (char*)T2A(strSendBuf);

	// 发送消息
	int ret = m_client->Send(csSendBuf, MSGBUF_LEN);
	
	// 发送出错
	if (ret == SOCKET_ERROR) {
		TRACE("m_client send error: %d", GetLastError());
		MessageBox(L"发送出错!");
		return;
	}

	CString strShow = CombStr(strNickname, strMsg);

	// 把消息添加到消息记录里
	m_msgRecord.AddString(strShow);

	// 更新数据
	UpdateData();

	// 把消息输入框的清空
	GetDlgItem(IDC_MSG_EDIT)->SetWindowText(L"");
}

// 消息字符串拼接
CString CMFCChatClientDlg::CombStr(const CString& strNickname,
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

// 按自动回复按钮
void CMFCChatClientDlg::OnBnClickedAutoreplyRadio()
{
	// 获取自动回复按钮
	CButton* autoReply = (CButton*)GetDlgItem(IDC_AUTOREPLY_RADIO);
	// 设置为相反的状态
	autoReply->SetCheck(!(autoReply->GetCheck()));
}

// 实现自动回复
void CMFCChatClientDlg::AutoReply()
{
	TRACE("###CMFCChatClientDlg::AutoReply");

	// 自动回复按钮被选中
	if (((CButton*)GetDlgItem(IDC_AUTOREPLY_RADIO))->GetCheck() == BST_CHECKED) {
		// 获取消息框内容
		CString strMsg;
		GetDlgItem(IDC_MSG_EDIT)->GetWindowText(strMsg);

		// 消息为空
		if (strMsg.IsEmpty()) return;

		// 获取昵称
		CString strNickname;
		GetDlgItemText(IDC_NICKNAME_EDIT, strNickname);

		// 昵称为空
		if (strNickname.IsEmpty()) {
			// 设为默认昵称
			strNickname = _T(DEFAULT_NICKNAME);
		}

		strNickname += L"[自动回复]";

		// 拼接要发送消息
		CString strSendBuf = CombStr(strNickname, strMsg, false);

		// CString转成char*
		USES_CONVERSION;
		char* csSendBuf = (char*)T2A(strSendBuf);

		// 发送消息
		int ret = m_client->Send(csSendBuf, MSGBUF_LEN);

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

// 保存昵称
void CMFCChatClientDlg::OnBnClickedSavenicknameBtn()
{
	TRACE("###CMFCChatClientDlg::OnBnClickedSavenicknameBtn");

	// 获取昵称
	CString strNickname;
	GetDlgItemText(IDC_NICKNAME_EDIT, strNickname);

	if (strNickname.IsEmpty()) {
		MessageBox(L"昵称为空!");
		return;
	}
	// 昵称长度过长
	else if (strNickname.GetLength() > NICKNAME_LEN) {
		// 把昵称设为默认昵称
		SetDlgItemText(IDC_NICKNAME_EDIT, _T(DEFAULT_NICKNAME));

		CString str;
		str.Format(L"昵称长度大于%d!", NICKNAME_LEN);
		MessageBox(str);
		return;
	}

	// 获取当前目录
	WCHAR wcsPath[MAX_PATH];
	if (!GetCurrentDirectoryW(MAX_PATH, wcsPath)) {
		TRACE("###GetCurrentDirectoryW error: ", GetLastError());
		MessageBox(L"昵称保存失败!");
		return;
	}

	// 配置文件路径
	CString strFilePath;
	strFilePath.Format(L"%s//client.ini", wcsPath);

	// 把昵称保存到配置文件里, 如果配置文件不存在, 则创建一个配置文件
	if (!WritePrivateProfileStringW(L"CLIENT", L"NICKNAME", strNickname, strFilePath)) {
		TRACE("###WritePrivateProfileStringW error: ", GetLastError());
		MessageBox(L"昵称保存失败!");
		return;
	}

}
