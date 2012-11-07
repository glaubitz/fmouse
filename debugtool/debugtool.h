// debugtool.h : Haupt-Header-Datei für die Anwendung DEBUGTOOL
//

#if !defined(AFX_DEBUGTOOL_H__FE746602_BE96_11D4_B654_9825E362B931__INCLUDED_)
#define AFX_DEBUGTOOL_H__FE746602_BE96_11D4_B654_9825E362B931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolApp:
// Siehe debugtool.cpp für die Implementierung dieser Klasse
//

class CDebugtoolApp : public CWinApp
{
public:
	CDebugtoolApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDebugtoolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDebugtoolApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DEBUGTOOL_H__FE746602_BE96_11D4_B654_9825E362B931__INCLUDED_)
