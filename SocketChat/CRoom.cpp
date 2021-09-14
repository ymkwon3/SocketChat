// CRoom.cpp: 구현 파일
//

#include "pch.h"
#include "SocketChat.h"
#include "CRoom.h"
#include "afxdialogex.h"

#define PORT 9999
// CRoom 대화 상자

IMPLEMENT_DYNAMIC(CRoom, CDialogEx)

CRoom::CRoom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JOIN, pParent)
{

}

CRoom::~CRoom()
{
}

void CRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
}


BEGIN_MESSAGE_MAP(CRoom, CDialogEx)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CRoom::OnBnClickedSendButton)
	ON_MESSAGE(WM_CLIENT_RECV, &CRoom::OnClientRecv)
END_MESSAGE_MAP()

BOOL CRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if (m_ClientSocket.Connect(_T("127.0.0.1"), PORT) == FALSE) {
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// CRoom 메시지 처리기


void CRoom::OnBnClickedSendButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	UpdateData(TRUE);
	m_edit_send.GetWindowTextW(str);
	m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	m_edit_send.SetWindowTextW(_T(""));
	UpdateData(FALSE);
}

afx_msg LRESULT CRoom::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;

	m_list_msg.InsertString(-1, lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	return 0;
}
