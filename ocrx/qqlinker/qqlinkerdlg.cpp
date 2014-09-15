// CrackLinkerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qqlinkerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BLOCK 50

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   1024

// 拿5个点来作为一个方块的特征
typedef struct
{
    COLORREF color[5];
} COLOR_BLOCK_STRUCT;

const int   StepX = 111;       // 第一个方块区域的横坐标
const int   StepY = 90;        // 第一个方块区域的纵坐标
const int   BlockWidth  = 40;  // 方块的宽度
const int   BlockHeight = 50;  // 方块的高度
const int   BLOCK_COL   = 14;
const int   BLOCK_ROW   = 8;
const int   DRAW_POINT[5][2] = 
{
    {20, 10},
    {20, 20},
    {20, 25},
    {20, 30},
    {20, 45}
};

COLOR_BLOCK_STRUCT color_block[MAX_BLOCK];
int block_map[BLOCK_ROW][BLOCK_COL];
int map_blocks = 0;
int solution_map[BLOCK_ROW*BLOCK_COL][2];
int solution_step = 0;

void my_trace(const char *fmt, ...);
void Wait(double dtime);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQLinkerDlg dialog

CQQLinkerDlg::CQQLinkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQQLinkerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQQLinkerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQLinkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQQLinkerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_MAP , m_edit);
}

BEGIN_MESSAGE_MAP(CQQLinkerDlg, CDialog)
	//{{AFX_MSG_MAP(CQQLinkerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_OPEN_LINKER, OnOpenLinker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQLinkerDlg message handlers

BOOL CQQLinkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Init();
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQQLinkerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQQLinkerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQQLinkerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQQLinkerDlg::OnStart() 
{
    // TODO: Add your control notification handler code here
    // TODO: Add extra validation here
    Init();
    
    m_pLinker = FindWindow(NULL, "连连看"); // 得到程序的句柄
    if (m_pLinker == NULL)
    {
        AfxMessageBox("连连看未在运行!");
        return;
    }
    
    m_pLinker->GetClientRect(m_LinkerRect);   // 得到连连看程序的窗口大小
    m_pLinker->ClientToScreen(m_LinkerRect);  // 将其转化为屏幕坐标系

    linerHwnd = m_pLinker->GetSafeHwnd();
    linkerDC = ::GetDC(linerHwnd);
    m_pLinkerDC = CDC::FromHandle(linkerDC);

    this->GetMap();
}

void CQQLinkerDlg::OnOpenLinker() 
{
	// TODO: Add your control notification handler code here
	if (m_hLinker != NULL)
		return;
	
	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi;
	BOOL bSuccess;
	bSuccess = CreateProcess("E:\\vc demo\\linker\\连连看单机版\\zzllk.exe", NULL, NULL, 
                             NULL, FALSE, 0, 
                             NULL, NULL, 
                             &si, &pi);

	if (bSuccess)
	{
		m_hLinker = pi.hProcess;
	}
}

void CQQLinkerDlg::Init(void)
{
    m_hLinker = NULL;
    memset(block_map, 0, sizeof(block_map));
    memset(color_block, 0, sizeof(color_block));
    memset(solution_map, 0xff, sizeof(solution_map));
    map_blocks = 0;
    solution_step = 0;
}

int CQQLinkerDlg::found(COLORREF *color_p)
{
    int i, j;

    // 处理空块
    for (i=0; i<5; i++)
        if (color_p[i] != 0x0)  // black
        {
            break;
        }
    if (i == 5)
        // 空块
        return -2;

    // 正常方块
    for (i=0; i<map_blocks; i++)
    {
        for (j=0; j<5; j++)
            if (color_block[i].color[j] != color_p[j])
            {
                // 有不同的就退出
                break;
            }
        if (j == 5)
        {
            // color_p 与 map_blocks[i] 相同
            break;
        }
    }

    if (i == map_blocks)
    {
        // 没找着
        return -1;
    }
    else
    {   
        // 找着啦
        return i;
    }
}

void CQQLinkerDlg::add_to_color_block(COLORREF *color_p)
{
    int i;

    for (i=0; i<5; i++)
    {
        color_block[map_blocks].color[i] = color_p[i];
    }

    map_blocks++;
}

void CQQLinkerDlg::OutputMap(void)
{
    int i, j;
    CString cs = "";
    CString temp;

    for (i=0; i<BLOCK_ROW; i++)
    {
        for (j=0; j<BLOCK_COL; j++)
        {
            temp.Format("%4d", block_map[i][j]);
            cs += temp;
        }

        cs += "\r\n\r\n";
    }

    m_edit.SetWindowText(cs);
}

int CQQLinkerDlg::CanErase(int x1, int y1, int x2, int y2)
{
    if (block_map[x1][y1] == -1 || block_map[x2][y2] == -1 
     || block_map[x1][y1] != block_map[x2][y2])
    {
        return 0;
    }

    return 0;
}

void CQQLinkerDlg::FindSolution(void)
{
    int i, j, k1, k2 = 0;

    solution_step = 0;

#if 1
    for (i=0; i<BLOCK_COL; i++)
        for (j=0; j<i; j++)
        {
            for (k1=0; k1<BLOCK_ROW; k1++)
                if (block_map[k1][i] != -1)
                    break;

            for (k2=0; k2<BLOCK_ROW; k2++)
                if (block_map[k2][j] != -1)
                    break;

            if (k1 < BLOCK_ROW && k2 < BLOCK_ROW)
                if (block_map[k1][i] == block_map[k2][j] && block_map[k1][i] != -1)
                {
                    solution_map[solution_step][0] = k1;
                    solution_map[solution_step][1] = i;
                    block_map[k1][i] = -1;
                    solution_step++;
                    
                    solution_map[solution_step][0] = k2;
                    solution_map[solution_step][1] = j;
                    block_map[k2][j] = -1;
                    solution_step++;
                }
        }

    for (i=0; i<BLOCK_COL; i++)
        for (j=0; j<i; j++)
        {
            for (k1=BLOCK_ROW-1; k1>=0; k1--)
                if (block_map[k1][i] != -1)
                    break;

            for (k2=BLOCK_ROW-1; k2>=0; k2--)
                if (block_map[k2][j] != -1)
                    break;

            if (k1 < BLOCK_ROW && k2 < BLOCK_ROW)
                if (block_map[k1][i] == block_map[k2][j] && block_map[k1][i] != -1)
                {
                    solution_map[solution_step][0] = k1;
                    solution_map[solution_step][1] = i;
                    block_map[k1][i] = -1;
                    solution_step++;
                    
                    solution_map[solution_step][0] = k2;
                    solution_map[solution_step][1] = j;
                    block_map[k2][j] = -1;
                    solution_step++;
                }
        }

    for (i=0; i<BLOCK_ROW; i++)
        for (j=0; j<i; j++)
        {
            for (k1=0; k1<BLOCK_COL; k1++)
                if (block_map[i][k1] != -1)
                    break;

            for (k2=0; k2<BLOCK_COL; k2++)
                if (block_map[j][k2] != -1)
                    break;

            if (k1 < BLOCK_COL && k2 < BLOCK_COL)
                if (block_map[i][k1] == block_map[j][k2] && block_map[i][k1] != -1)
                {
                    solution_map[solution_step][0] = i;
                    solution_map[solution_step][1] = k1;
                    block_map[i][k1] = -1;
                    solution_step++;
                    
                    solution_map[solution_step][0] = j;
                    solution_map[solution_step][1] = k2;
                    block_map[j][k2] = -1;
                    solution_step++;
                }
        }

    for (i=0; i<BLOCK_ROW; i++)
        for (j=0; j<i; j++)
        {
            for (k1=BLOCK_COL-1; k1>=0; k1--)
                if (block_map[i][k1] != -1)
                    break;

            for (k2=BLOCK_COL-1; k2>=0; k2--)
                if (block_map[j][k2] != -1)
                    break;

            if (k1 < BLOCK_COL && k2 < BLOCK_COL)
                if (block_map[i][k1] == block_map[j][k2] && block_map[i][k1] != -1)
                {
                    solution_map[solution_step][0] = i;
                    solution_map[solution_step][1] = k1;
                    block_map[i][k1] = -1;
                    solution_step++;
                    
                    solution_map[solution_step][0] = j;
                    solution_map[solution_step][1] = k2;
                    block_map[j][k2] = -1;
                    solution_step++;
                }
        }
        
#else
    for (i=0; i<BLOCK_COL; i++)
        for (j=0; j<i; j++)
        {
            if (block_map[0][i] == block_map[0][j] && block_map[0][i] != -1)
            {
                solution_map[solution_step][0] = i;
                solution_map[solution_step][1] = 0;
                solution_step++;
                
                solution_map[solution_step][0] = j;
                solution_map[solution_step][1] = 0;
                solution_step++;
            }
        }
#endif
}

void CQQLinkerDlg::DoIt(void)
{
    int i;
    int x, y;

    if (solution_step == 0)
    {
        AfxMessageBox("No Solution!");
        return;
    }

    for (i=0; i<solution_step; i += 2)
        if (solution_map[i][0] != -1 && solution_map[i][1] != -1)
        {
            x = m_LinkerRect.left + StepX + solution_map[i][1] * BlockWidth + BlockWidth/2;
            y = m_LinkerRect.top + StepY + solution_map[i][0] * BlockHeight + BlockHeight/2;
            
        	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,
        		        x*65535/SCREEN_WIDTH,y*65535/SCREEN_HEIGHT,0,0);
        		
        	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,
        		        0,0,0,0);   

        	Wait(10);

            x = m_LinkerRect.left + StepX + solution_map[i+1][1] * BlockWidth + BlockWidth/2;
            y = m_LinkerRect.top + StepY + solution_map[i+1][0] * BlockHeight + BlockHeight/2;
            
        	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,
        		        x*65535/SCREEN_WIDTH,y*65535/SCREEN_HEIGHT,0,0);
        		
        	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,
        		        0,0,0,0);   

        	Wait(10);

        	//block_map [solution_map[i][0]] [solution_map[i][1]] = -1;
        	//block_map [solution_map[i+1][0]] [solution_map[i+1][1]] = -1;
        }

    OutputMap();

    FindSolution();

    DoIt();
}

void CQQLinkerDlg::GetMap(void)
{
    COLORREF temp_color[5];
    int i, j, k;
    
    for (i=0; i<BLOCK_ROW; i++)
        for (j=0; j<BLOCK_COL; j++)
        {
            for (k=0; k<5; k++)
            {
            	temp_color[k] = m_pLinkerDC->GetPixel(StepX + j*BlockWidth + DRAW_POINT[k][0], 
            	                                      StepY + i*BlockHeight + DRAW_POINT[k][1]);
                //my_trace("color[%d, %d] = 0x%x\n", StepX + i*BlockWidth + DRAW_POINT[k][0], 
                //                                 StepY + i*BlockHeight + DRAW_POINT[k][1], 
                //                                 temp_color[k]);
        	}

        	if (i == 0 && j == 1)
                k = found((COLORREF *)temp_color);
            else
                k = found((COLORREF *)temp_color);

            if (k == -2)
            {
                // empty
                block_map[i][j] = -1;
            }
            else if (k == -1)
            {
                // new block
                add_to_color_block((COLORREF *)temp_color);
                block_map[i][j] = map_blocks - 1;
            }
            else
            {
                block_map[i][j] = k;
            }
        }

   my_trace("map_blocks = %d\n", map_blocks);

   OutputMap();

   FindSolution();

   DoIt();
}

void my_trace(const char *fmt, ...)
{
    static char dbgbuf[256];
    va_list arglist;
	
    va_start(arglist, fmt);
	_vsnprintf_s(dbgbuf, 256-1, fmt, arglist);

	OutputDebugString(dbgbuf);

    va_end(arglist);
}

// 延时函数
void Wait(double dtime)
{
	DWORD dwTicks = 0;
	DWORD dwTickCount = GetTickCount();

	do
	{
		dwTicks = GetTickCount() - dwTickCount;

	} while( dwTicks < dtime );

	return;
}

