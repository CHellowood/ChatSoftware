
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

	// 实时时间
	CTime m_time;
	
	// 自动回复
	CButton m_autoReply;

	afx_msg void OnBnClickedAutoreplyRadio();

	// 自动回复函数
	void AutoReply();
	
};
