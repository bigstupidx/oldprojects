// OcrxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OcrxDlg.h"


// COcrxDlg �Ի���

IMPLEMENT_DYNAMIC(COcrxDlg, CDialogEx)

COcrxDlg::COcrxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COcrxDlg::IDD, pParent)
{

}

COcrxDlg::~COcrxDlg()
{
}

void COcrxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// ddx control
    DDX_Control(pDX, IDC_QQLINKER_STATIC , m_static[0]);
}

BOOL COcrxDlg::OnInitDialog() 
{
    // fill status struct.
    strncpy_s(m_status[0].name, "QQ��Ϸ - ��������ɫ��", 511);
    
    SetTimer(1, 100, NULL);
    
    return CDialogEx::OnInitDialog();
}

void COcrxDlg::OnTimer(UINT nIDEvent) 
{
    // get status
    getStatus();
    
    CDialogEx::OnTimer(nIDEvent);
}

// set the static font color
HBRUSH COcrxDlg::OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor)
{
    HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    if (nCtlColor == CTLCOLOR_STATIC)
    {
        for (int i = 0; i < SUPPORT_GAME_COUNT; i++)
        {
            if (pWnd->GetDlgCtrlID() == IDC_QQLINKER_STATIC + i)
            {
                if (m_status[i].opened)
                {
                    pDC->SetTextColor(RGB(0,255,0));
                }
                else
                {
                    pDC->SetTextColor(RGB(255,0,0));
                }
            }
        }
    }
    
    return hBrush;
}

void COcrxDlg::getStatus()
{
    // find windows
    for (int i = 0; i < SUPPORT_GAME_COUNT; i++)
    {
        if (!FindWindow(NULL, m_status[i].name))
        {
            m_static[i].SetWindowText("Off");
            m_status[i].opened = false;
        }
        else
        {
            m_static[i].SetWindowText("On");
            m_status[i].opened = true;
        }
    }
}

BEGIN_MESSAGE_MAP(COcrxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COcrxDlg ��Ϣ�������
