// ocrx.h : main header file for the ocrx application
//

#if !defined(AFX_CRACKLINKER_H__E7FF9084_241C_451A_883A_0F4E4AC31E7B__INCLUDED_)
#define AFX_CRACKLINKER_H__E7FF9084_241C_451A_883A_0F4E4AC31E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COcrxApp:
// See ocrx.cpp for the implementation of this class
//

class COcrxApp : public CWinApp
{
public:
	COcrxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COcrxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COcrxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKLINKER_H__E7FF9084_241C_451A_883A_0F4E4AC31E7B__INCLUDED_)
