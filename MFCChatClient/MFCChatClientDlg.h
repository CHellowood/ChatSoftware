
// MFCChatClientDlg.h: 头文件
//

#pragma once

#include "CMySocket.h"

// 昵称长度
#define NICKNAME_LEN 10
// 默认昵称
#define DEFAULT_NICKNAME "client"

// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CMFCChatClientDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLIENT_DIALOG };
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
	afx_msg void OnBnClickedConnectBtn();
	
	// 客户端套接字
	CMySocket* m_client;
	// 消息记录
	CListBox m_msgRecord;

	afx_msg void OnBnClickedSendmsgBtn();

	// 消息字符串拼接, 第三个参数 isAddTime 表示是否要添加时间
	//格式: 时间(函数内部获取) + 空格 + 昵称 + ": " + 消息
	// 返回拼接后的字符串
	CString CombStr(const CString& strNickname, const CString& strMsg, bool isAddTime = true);
	afx_msg void OnBnClickedAutoreplyRadio();
	// 实现自动回复
	void CMFCChatClientDlg::AutoReply();
	afx_msg void OnBnClickedSavenicknameBtn();
};
