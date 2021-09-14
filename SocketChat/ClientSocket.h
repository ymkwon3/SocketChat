#pragma once

#define WM_CLIENT_RECV WM_USER+1
// ClientSocket 명령 대상

class ClientSocket : public CSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();
	void SetWnd(HWND hWnd);
	HWND m_hwnd;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


