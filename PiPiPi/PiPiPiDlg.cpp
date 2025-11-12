
// PiPiPiDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PiPiPi.h"
#include "PiPiPiDlg.h"
#include "afxdialogex.h"


#include <iostream>
#include <cmath>
#include <iomanip> // For std::setprecision

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPiPiPiDlg 대화 상자



CPiPiPiDlg::CPiPiPiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIPIPI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPiPiPiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
IDC_LIST_TRACE
}

BEGIN_MESSAGE_MAP(CPiPiPiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_STL_METHOD, &CPiPiPiDlg::OnBnClickedBtStlMethod)
	ON_BN_CLICKED(IDC_BT_LEIBNIZ, &CPiPiPiDlg::OnBnClickedBtLeibniz)
	ON_BN_CLICKED(IDC_BT_MPFR, &CPiPiPiDlg::OnBnClickedBtMpfr)
END_MESSAGE_MAP()


// CPiPiPiDlg 메시지 처리기

/**
 * @brief Initialize the dialog: calls the base class OnInitDialog, adds an "About..." item to the system menu (if available), sets the dialog's large and small icons, and performs any additional initialization.
 * @example
 * BOOL result = dlg.OnInitDialog();
 * std::cout << (result ? "TRUE" : "FALSE") << std::endl; // Expected output: TRUE
 * 
 * @return BOOL - Returns TRUE to indicate that the dialog did not set the input focus to a control (standard MFC behavior). The method also performs assertions to ensure IDM_ABOUTBOX is within the valid system command range and loads the "About" menu string if present.
 */
BOOL CPiPiPiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

/**
 * @brief Handle system command messages for the CPiPiPiDlg dialog.
 * @example
 * CPiPiPiDlg dlg;
 * dlg.OnSysCommand(IDM_ABOUTBOX, 0); // Opens the About dialog modally.
 * dlg.OnSysCommand(SC_CLOSE, 0);     // Delegates to CDialogEx::OnSysCommand.
 * 
 * @param {UINT} nID - System command identifier; masked with 0xFFF0 and compared to IDM_ABOUTBOX to detect the About command.
 * @param {LPARAM} lParam - Additional message parameter supplied with the system command.
 * @return {void} - No return value; either displays the About dialog or forwards the command to the base class handler.
 */
void CPiPiPiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

/**
 * @brief Handles the WM_PAINT message for the dialog. When the dialog is iconic (minimized),
 * it prepares a paint device context, clears the icon background, centers the application icon
 * in the client area and draws it. When not iconic, it delegates painting to the base class.
 * @example
 * // For an instance dlg of CPiPiPiDlg:
 * dlg.OnPaint(); // If the dialog is minimized, the dialog's icon is drawn centered. Otherwise, default painting occurs.
 * 
 * @return void - No return value.
 */
void CPiPiPiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPiPiPiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPiPiPiDlg::OnBnClickedBtStlMethod()
{
    double pi_acos = 2 * std::acos(0.0); // acos(0) returns pi/2
    double pi_asin = 2 * std::asin(1.0); // asin(1) returns pi/2


	CString strTrace;

	strTrace.Format(L"Pi using acos(0.0): %.*f", 20, pi_asin);
	m_TraceListBox.AddString(strTrace);

	strTrace.Format(L"Pi using asin(1.0): %.*f", 20, pi_asin);
	m_TraceListBox.AddString(strTrace);
}

void CPiPiPiDlg::OnBnClickedBtLeibniz()
{
	double pi_approx = 0.0;
	long long num_terms = 1000000; // Number of terms for approximation

	for (long long i = 0; i < num_terms; ++i)
	{
		double term = 1.0 / (2.0 * i + 1.0);

		if (i % 2 == 0)	// Add for even terms
		{
			pi_approx += term;
		}
		else			// Subtract for odd terms
		{
			pi_approx -= term;
		}
	}

	pi_approx *= 4.0;

	CString strTrace;
	strTrace.Format(L"Pi using Leibniz formula: %.*f", 20, pi_approx);
	m_TraceListBox.AddString(strTrace);
}
using Sdcb.Arithmetic.Gmp;
void CPiPiPiDlg::OnBnClickedBtMpfr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
