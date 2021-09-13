// CCreate.cpp: 구현 파일
//

#include "pch.h"
#include "SocketChat.h"
#include "CCreate.h"
#include "afxdialogex.h"

#define PORT 9999

// CCreate 대화 상자

IMPLEMENT_DYNAMIC(CCreate, CDialogEx)

CCreate::CCreate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREATE, pParent)
{

}

CCreate::~CCreate()
{
}

void CCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_client);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
}

BOOL CCreate::OnInitDialog()
{
	//Listen 소켓 초기화
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);

	//소켓 Listen하기
	m_pServerSocket->Create(PORT);
	m_pServerSocket->Listen();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


BEGIN_MESSAGE_MAP(CCreate, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_CLIENT, &CCreate::OnLbnSelchangeListClient)
	ON_LBN_SELCHANGE(IDC_LIST_MSG, &CCreate::OnLbnSelchangeListMsg)
//	ON_WM_ACTIVATE()
ON_MESSAGE(WM_ACCEPT_SOCKET, &CCreate::OnAcceptSocket)
ON_MESSAGE(WM_CLIENT_MSG_RECV, &CCreate::OnClientMsgRecv)
ON_MESSAGE(WM_CLIENT_CLOSE, &CCreate::OnClientClose)
END_MESSAGE_MAP()


// CCreate 메시지 처리기


void CCreate::OnLbnSelchangeListClient()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCreate::OnLbnSelchangeListMsg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void CCreate::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


afx_msg LRESULT CCreate::OnAcceptSocket(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_pClientSocket = (CClientSocket*)lParam;
	m_ptrClientSocketList.AddTail(m_pClientSocket);

	str.Format(_T("Client (%d)"), (int)(m_pClientSocket));
	m_list_client.InsertString(-1, str);

	m_pClientSocket = NULL;
	delete m_pClientSocket;
	return 0;
}


afx_msg LRESULT CCreate::OnClientMsgRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;

	//BroadCasting
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();

	while (pos != NULL)
	{
		CClientSocket* pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			//UNICODE 사용하면 기존 메모리크기 *2 해야함
			//Client에 Broadcasting하기
			pClient->Send(lpszStr, lstrlen(lpszStr) * 2);
		}
	}

	//m_list_msg에 메시지 추가
	m_list_msg.InsertString(-1, lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	return 0;
}


afx_msg LRESULT CCreate::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	CClientSocket* pClient = (CClientSocket*)lParam;
	CString str;
	UINT idx = 0;
	POSITION pos = m_ptrClientSocketList.Find(pClient);

	if (pos != NULL)
	{
		//m_list_client에서 해당 Client 삭제
		str.Format(_T("Client (%d)"), (int)pClient);
		idx = m_list_client.SelectString(-1, (LPCTSTR)str);
		m_list_client.DeleteString(idx);

		//CPtrList에서도 해당 Client 삭제
		m_ptrClientSocketList.RemoveAt(pos);
	}
	return 0;
}
