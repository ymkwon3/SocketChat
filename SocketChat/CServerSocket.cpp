// CServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "SocketChat.h"
#include "CServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 멤버 함수
void CServerSocket::SetWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

void CServerSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket; // Client 소켓 포인터 추가

	if (Accept(*pClient)) // Listen에서 클라이언트 접속을 확인하면
	{
		pClient->SetWnd(m_hwnd); // Client 소켓에 메인핸들 연결
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR: Failed can't accept new Client!"));
	}
	SendMessage(m_hwnd, WM_ACCEPT_SOCKET, 0, (LPARAM)pClient);
	CSocket::OnAccept(nErrorCode);
}