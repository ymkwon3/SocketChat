#pragma once
#include "CClientSocket.h"

#define WM_ACCEPT_SOCKET WM_USER+1 // 클라이언트가 서버에 접속할때 IDC_LIST_CLIENT에 접속 표시
// CServerSocket 명령 대상

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	void SetWnd(HWND hwnd); // SendMessage 활용을 위한 메인의 핸들을 받는 함수
	HWND m_hwnd;
	virtual void OnAccept(int nErrorCode); // 클라이언트가 서버와 연결 시 처리 시의 함수
};


