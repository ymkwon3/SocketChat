#pragma once

#define WM_CLIENT_MSG_RECV WM_USER+2 // 클라이언트가 서버로 메시지를 보낼때 IDC_LIST_MSG에 메시지 표시
#define WM_CLIENT_CLOSE WM_USER+3 // 클라이언트가 서버와 연결 해제시의 대처
// CClientSocket 명령 대상

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	void SetWnd(HWND hwnd); // SendMessage 활용을 위한 메인의 핸들을 받는 함수
	HWND m_hwnd;
	virtual void OnReceive(int nErrorCode); // 서버 통신 받을시의 처리 함수
	virtual void OnClose(int nErrorCode); // 소켓 해제시의 처리 함수
};


