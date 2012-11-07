// debugtoolDlg.h : Header-Datei
//

#if !defined(AFX_DEBUGTOOLDLG_H__FE746604_BE96_11D4_B654_9825E362B931__INCLUDED_)
#define AFX_DEBUGTOOLDLG_H__FE746604_BE96_11D4_B654_9825E362B931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolDlg Dialogfeld

class CDebugtoolDlg : public CDialog
{
// Konstruktion
public:
	CDebugtoolDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDebugtoolDlg)
	enum { IDD = IDD_DEBUGTOOL_DIALOG };
	int		m_xposmov;
	int		m_yposmov;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDebugtoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CDebugtoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadvxd();
	afx_msg void OnNorth();
	afx_msg void OnWest();
	afx_msg void OnEast();
	afx_msg void OnSouth();
	afx_msg void OnSetpos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DEBUGTOOLDLG_H__FE746604_BE96_11D4_B654_9825E362B931__INCLUDED_)
