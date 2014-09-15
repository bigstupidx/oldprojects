#pragma once

#include <resource.h>
#include "afxdialogex.h"

// COcrxDlg 对话框

#define SUPPORT_GAME_COUNT  1

struct OcrxStatus
{
    char    name[512];
    bool    opened;
};

class COcrxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COcrxDlg)

public:
	COcrxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COcrxDlg();

// 对话框数据
	enum { IDD = IDD_OCRX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
    void getStatus();

private:
    CStatic     m_static[SUPPORT_GAME_COUNT];
    OcrxStatus  m_status[SUPPORT_GAME_COUNT];
};
