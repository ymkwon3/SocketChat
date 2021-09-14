#pragma once
#include "ClientSocket.h"

// CRoom 대화 상자

class CRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CRoom)

public:
	CRoom(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRoom();

// 대화 상자 데이터입니다.

enum { IDD = IDD_JOIN };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	ClientSocket m_ClientSocket;
public:
	CListBox m_list_msg;
	CEdit m_edit_send;
	afx_msg void OnBnClickedSendButton();
protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);  //사용자 메시지 함수 추가
};
