// qqlinkerdlg.h : header file
//

#if !defined(AFX_CRACKLINKERDLG_H__0F81CD3A_7FC5_48D4_A53D_EF059E7C5223__INCLUDED_)
#define AFX_CRACKLINKERDLG_H__0F81CD3A_7FC5_48D4_A53D_EF059E7C5223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <resource.h>

/////////////////////////////////////////////////////////////////////////////
// CQQLinkerDlg dialog

class CQQLinkerDlg : public CDialog
{
// Construction
public:
	CQQLinkerDlg(CWnd* pParent = NULL);	// standard constructor

// My Data
	HANDLE  m_hLinker;
	CWnd    *m_pLinker;
	HDC     linkerDC;
    HWND    linerHwnd;
    CDC     *m_pLinkerDC;
    CRect   m_LinkerRect;

    CEdit   m_edit;

// My Function    
    void    Init(void);
	void    GetMap(void);
	int     found(COLORREF *);
	void    add_to_color_block(COLORREF *);
	void    OutputMap(void);
	void    FindSolution(void);
	void    DoIt(void);
	int     CanErase(int, int, int, int);

// Dialog Data
	//{{AFX_DATA(CQQLinkerDlg)
	enum { IDD = IDD_CRACKLINKER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQLinkerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQQLinkerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnOpenLinker();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKLINKERDLG_H__0F81CD3A_7FC5_48D4_A53D_EF059E7C5223__INCLUDED_)
