// debugtool.cpp : Legt das Klassenverhalten f�r die Anwendung fest.
//

#include "stdafx.h"
#include "debugtool.h"
#include "debugtoolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolApp

BEGIN_MESSAGE_MAP(CDebugtoolApp, CWinApp)
	//{{AFX_MSG_MAP(CDebugtoolApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolApp Konstruktion

CDebugtoolApp::CDebugtoolApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CDebugtoolApp-Objekt

CDebugtoolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDebugtoolApp Initialisierung

BOOL CDebugtoolApp::InitInstance()
{
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Gr��e Ihrer fertigen 
	//  ausf�hrbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht ben�tigen, entfernen.

	CDebugtoolDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
