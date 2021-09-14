// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "SocketChat.h"
#include "ClientSocket.h"


// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// ClientSocket 멤버 함수

void ClientSocket::SetWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

void ClientSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024];
	ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0) {
		SendMessage(m_hwnd, WM_CLIENT_RECV, 0, (LPARAM)szBuffer);
	}

	CSocket::OnReceive(nErrorCode);
}

void ClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR:Disconnected from server!"));
	PostQuitMessage(0);
}