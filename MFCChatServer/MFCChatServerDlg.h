
// MFCChatServerDlg.h: 头文件
//

#pragma once

#include "CServerSocket.h"
#include "CChatSocket.h"

// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CMFCChatServerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();

	// 服务端的监听套接字
	CServerSocket* m_server;

	// 聊天套接字
	CChatSocket* m_chat;

	// 消息记录
	CListBox m_msgRecord;

	afx_msg void OnBnClickedAutoreplyRadio();

	// 自动回复函数
	void AutoReply();
	
	afx_msg void OnBnClickedSendBtn();

	// 消息字符串拼接, 第三个参数 isAddTime 表示是否要添加时间
	//格式: 时间(函数内部获取) + 空格 + 昵称 + ": " + 消息
	// 返回拼接后的字符串
	CString CombStr(const CString& strNickname, const CString& strMsg, bool isAddTime = true);
};
