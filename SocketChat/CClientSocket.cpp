﻿// CClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "SocketChat.h"
#include "CClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수

void CClientSocket::SetWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR strBuffer[1024];
	ZeroMemory(strBuffer, sizeof(strBuffer));

	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // 전달된 데이터가 있을 경우
		strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
	}
	SendMessage(m_hwnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	SendMessage(m_hwnd, WM_CLIENT_CLOSE, 0, (LPARAM)this);
	CSocket::OnClose(nErrorCode);
}