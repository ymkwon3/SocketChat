#pragma once
#include "CServerSocket.h"

// CCreate 대화 상자

class CCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CCreate)

public:
	CCreate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCreate();

// 대화 상자 데이터입니다.

enum { IDD = IDD_CREATE };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CClientSocket* m_pClientSocket;
	CServerSocket* m_pServerSocket;
public:
	afx_msg void OnLbnSelchangeListClient();
	afx_msg void OnLbnSelchangeListMsg();
	CListBox m_list_client;
	CListBox m_list_msg;
	CPtrList m_ptrClientSocketList; // For manage Client Socket
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	afx_msg LRESULT OnAcceptSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);
};
