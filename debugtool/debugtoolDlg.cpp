// debugtoolDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "debugtool.h"
#include "debugtoolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* the following are two control codes
   FMOUSE knows: */

#define WM_MOVEMOUSE	4094
#define WM_SETMOUSE		4095

typedef struct _MOUSEDATA {

	int	X; // either units to move or new position of X
	int	Y; // either units to move or new position of Y
	BYTE	ButtonStatus; // flag variable containing the button status

} MOUSEDATA;

HANDLE hDevice;
MOUSEDATA MouseData = {0,0,0};
LPDWORD lpBytesReturned;
LPOVERLAPPED lpOverlapped;

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolDlg Dialogfeld

CDebugtoolDlg::CDebugtoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugtoolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDebugtoolDlg)
	m_xposmov = 0;
	m_yposmov = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDebugtoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugtoolDlg)
	DDX_Text(pDX, ID_XPOSMOV, m_xposmov);
	DDX_Text(pDX, ID_YPOSMOV, m_yposmov);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDebugtoolDlg, CDialog)
	//{{AFX_MSG_MAP(CDebugtoolDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOADVXD, OnLoadvxd)
	ON_BN_CLICKED(IDC_NORTH, OnNorth)
	ON_BN_CLICKED(IDC_WEST, OnWest)
	ON_BN_CLICKED(IDC_EAST, OnEast)
	ON_BN_CLICKED(IDC_SOUTH, OnSouth)
	ON_BN_CLICKED(IDC_SETPOS, OnSetpos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolDlg Nachrichten-Handler

BOOL CDebugtoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		
		pSysMenu->RemoveMenu (2,MF_BYPOSITION);
		pSysMenu->RemoveMenu (3,MF_BYPOSITION);
	}
	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CDebugtoolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CDebugtoolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDebugtoolDlg::OnLoadvxd() 
{
	hDevice = CreateFile("\\\\.\\FMOUSE.VXD", 
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 0);
	
	if (hDevice == INVALID_HANDLE_VALUE)
		MessageBox ("Could not load FMOUSE virtual device driver\r\nError: Invalid Handle\r\nCheck if the driver is in the current directory\r\nIf this problem persists, try a power-off reboot (wait > 1 min.)", "Error", MB_OK|MB_ICONSTOP);
	else
		GetDlgItem (IDC_LOADVXD)->EnableWindow (FALSE);
}

void CDebugtoolDlg::OnNorth() 
{
	UpdateData (TRUE);
	MouseData.X = 0;
	MouseData.Y = m_yposmov * -1;

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);
}

void CDebugtoolDlg::OnWest() 
{
	UpdateData (TRUE);
	MouseData.X = m_xposmov * -1;
	MouseData.Y = 0;

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);	
}

void CDebugtoolDlg::OnEast() 
{
	UpdateData (TRUE);
	MouseData.X = m_xposmov;
	MouseData.Y = 0;

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);	
}

void CDebugtoolDlg::OnSouth() 
{
	UpdateData (TRUE);
	MouseData.X = 0;
	MouseData.Y = m_yposmov;

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);		
}

void CDebugtoolDlg::OnSetpos() 
{
	UpdateData (TRUE);
	MouseData.X = m_xposmov;
	MouseData.Y = m_yposmov;
	
	DeviceIoControl(hDevice, WM_SETMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);
}
