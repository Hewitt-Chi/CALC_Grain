
// CALC_GrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CALC_Grain.h"
#include "CALC_GrainDlg.h"
#include "afxdialogex.h"
//#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCALC_GrainDlg dialog




CCALC_GrainDlg::CCALC_GrainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCALC_GrainDlg::IDD, pParent)
	,m_DDXChange1(0)
	,m_DDXChange2(0)
	,m_DDXChange3(0)
	,m_DDXChange4(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_CALC);
      // lpszFacename
	//m_DataVec.clear();
	//m_ColumnStr = { _T("姓名"),_T("收購數量"),_T("輔導數量"),_T("餘糧數量"),_T("換算台斤"),_T("收購價款*26"),_T("輔導價款*23"),_T("餘糧價款*21.6"),_T("補助運費"),_T("實存金額") };
	
}

void CCALC_GrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EdtName, m_EdtName);
	DDX_Control(pDX, IDC_EdtBuyCNT, m_edtBuyCNT);
	DDX_Control(pDX, IDC_EdtCoun, m_edtCounCNT);
	DDX_Control(pDX, IDC_EdtRemainCNT, m_edtMrmainCNT);
	DDX_Control(pDX, IDC_EdtChange, m_EdtChange1);	
	DDX_Control(pDX, IDC_EdtBuy2, m_EdtChange2);
	DDX_Control(pDX, IDC_EdtBuy3, m_EdtChange3);
	DDX_Control(pDX, IDC_EdtBuy4, m_EdtChange4);
	DDX_Control(pDX, IDC_Edtreight, m_EdtTreight);
	DDX_Control(pDX, IDC_EdtMoney, m_EdtMoney);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BEGIN_MESSAGE_MAP(CCALC_GrainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EdtBuyCNT, &CCALC_GrainDlg::OnEnChangeEdtbuycnt)
	ON_BN_CLICKED(IDOK, &CCALC_GrainDlg::OnBnClickedOk)

	ON_EN_CHANGE(IDC_EdtCoun, &CCALC_GrainDlg::OnEnChangeEdtcoun)
	ON_EN_CHANGE(IDC_EdtRemainCNT, &CCALC_GrainDlg::OnEnChangeEdtremaincnt)
	ON_BN_CLICKED(IDC_btnNew, &CCALC_GrainDlg::OnBnClickedbtnnew)
	ON_BN_CLICKED(IDC_btnModify, &CCALC_GrainDlg::OnBnClickedbtnmodify)
	ON_BN_CLICKED(IDC_btnRead, &CCALC_GrainDlg::OnBnClickedbtnread)
	ON_BN_CLICKED(IDC_btnSave, &CCALC_GrainDlg::OnBnClickedbtnsave)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCALC_GrainDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_btnDelete, &CCALC_GrainDlg::OnBnClickedbtndelete)
	ON_BN_CLICKED(IDC_btnPrint, &CCALC_GrainDlg::OnBnClickedbtnprint)
END_MESSAGE_MAP()


// CCALC_GrainDlg message handlers

BOOL CCALC_GrainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//獲得原有風格
	DWORD dwStyle = ::GetWindowLong(m_listctrl.m_hWnd, GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	//設定新風格
	SetWindowLong(m_listctrl.m_hWnd, GWL_STYLE, dwStyle |LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	//設定擴充套件風格
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES ;
	ListView_SetExtendedListViewStyleEx(m_listctrl.m_hWnd, styles, styles);
	//m_listctrl.SetFont(&m_Font);
	LPCTSTR LColumnStr[] = { ("姓名"),("收購數量"),("輔導數量"),("餘糧數量"),("換算台斤"),("收購價款*26"),("輔導價款*23"),("餘糧價款*21.6"),("補助運費"),("實存金額")};
	for (int i = 0; i < 10;i++)
	{
	//	WideCharToMultiByte(CP_ACP, 0, LColumnStr[i], strlen(LColumnStr[i]), pFileName, len + 1, NULL, NULL);
		m_listctrl.InsertColumn(i ,LColumnStr[i], LVCFMT_CENTER, 80);
	}
	InitListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCALC_GrainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCALC_GrainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCALC_GrainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCALC_GrainDlg::InitListCtrl()
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_listctrl.GetDlgItem(0);
	ASSERT(pHeader);
	if (pHeader)
	{
		m_listctrl.SetRedraw(FALSE);
		int iNbrOfColumns = pHeader->GetItemCount();
		int iNbrOfCols = 10;
		for (int iCurrCol = 0;iCurrCol < iNbrOfColumns + 1;iCurrCol++)
		{
			// m_ListCtrl.SetColumnWidth(iCurrCol,LVSCW_AUTOSIZE);
			int nCurrWidth = m_listctrl.GetColumnWidth(iCurrCol);

			m_listctrl.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_listctrl.GetColumnWidth(iCurrCol);
			m_listctrl.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
		}
		m_listctrl.SetRedraw(true);
		m_listctrl.Invalidate();
	}
}

void CCALC_GrainDlg::OnEnChangeEdtbuycnt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString rslt;
	double DRslt;
	int IRslt;
	// rslt2;
	 m_edtBuyCNT.GetWindowTextA(rslt) ;
	 m_DDXChange2 = _ttoi(rslt );
	 IRslt = m_DDXChange2 * 26;
	 rslt.Format(_T("%d"), IRslt) ;
	 m_EdtChange2.SetWindowTextA(rslt.GetBuffer(1024));

	 DRslt = (m_DDXChange2 + m_DDXChange3 + m_DDXChange4) /0.6;
	 DRslt = rounding(DRslt, 0);
	 rslt.Format(_T("%.0f"), DRslt);
	 m_EdtChange1.SetWindowTextA(rslt.GetBuffer(1024));

	 IRslt = (m_DDXChange2 + m_DDXChange3) / 2;
	 rslt.Format(_T("%d"), IRslt);
	 m_EdtTreight.SetWindowTextA(rslt.GetBuffer(1024));

	 m_EdtChange2.GetWindowTextA(rslt);
	 IRslt = _ttoi(rslt);
	 m_EdtChange3.GetWindowTextA(rslt);
	 IRslt += _ttoi(rslt);
	 m_EdtChange4.GetWindowTextA(rslt);
	 IRslt += _ttoi(rslt);
	 m_EdtTreight.GetWindowTextA(rslt);
	 IRslt += _ttoi(rslt);
	 rslt.Format(_T("%d"), IRslt);
	 m_EdtMoney.SetWindowTextA(rslt.GetBuffer(1024));
}


void CCALC_GrainDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	__super::OnOK();
}



void CCALC_GrainDlg::OnEnChangeEdtcoun()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString rslt;
	double DRslt;
	int IRslt;
	// rslt2;
	m_edtCounCNT.GetWindowTextA(rslt);
	m_DDXChange3 = _ttoi(rslt);
	IRslt = m_DDXChange3 * 23;
	rslt.Format(_T("%d"), IRslt);
	m_EdtChange3.SetWindowTextA(rslt.GetBuffer(1024));

	DRslt = (m_DDXChange2 + m_DDXChange3 + m_DDXChange4) / 0.6;
	DRslt = rounding(DRslt, 0);
	rslt.Format(_T("%.0f"), DRslt);
	m_EdtChange1.SetWindowTextA(rslt.GetBuffer(1024));

	IRslt = (m_DDXChange2 + m_DDXChange3 ) / 2 ;
	rslt.Format(_T("%d"), IRslt);
	m_EdtTreight.SetWindowTextA(rslt.GetBuffer(1024));

	m_EdtChange2.GetWindowTextA(rslt);
	IRslt = _ttoi(rslt);
	m_EdtChange3.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	m_EdtChange4.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	m_EdtTreight.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	rslt.Format(_T("%d"), IRslt);
	m_EdtMoney.SetWindowTextA(rslt.GetBuffer(1024));



}
void CCALC_GrainDlg::ClearItem()
{
	m_EdtName.SetWindowTextA(_T(""));
	m_edtBuyCNT.SetWindowTextA(_T(""));
	m_edtCounCNT.SetWindowTextA(_T(""));
	m_edtMrmainCNT.SetWindowTextA(_T(""));
	m_EdtChange1.SetWindowTextA(_T(""));
	m_EdtChange2.SetWindowTextA(_T(""));
	m_EdtChange3.SetWindowTextA(_T(""));
	m_EdtChange4.SetWindowTextA(_T(""));

	m_EdtTreight.SetWindowTextA(_T(""));
	m_EdtMoney.SetWindowTextA(_T(""));

}

void CCALC_GrainDlg::OnEnChangeEdtremaincnt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString rslt;
	double DRslt;
	int IRslt;
	// rslt2;
	m_edtMrmainCNT.GetWindowTextA(rslt);
	m_DDXChange4 = _ttoi(rslt);
	IRslt = m_DDXChange4 * 21.6;
	rslt.Format(_T("%d"), IRslt);
	m_EdtChange4.SetWindowTextA(rslt.GetBuffer(1024));

	DRslt = (m_DDXChange2 + m_DDXChange3 + m_DDXChange4) / 0.6;
	DRslt = rounding(DRslt, 0);
	rslt.Format(_T("%.0f"), DRslt);
	m_EdtChange1.SetWindowTextA(rslt.GetBuffer(1024));

	IRslt = (m_DDXChange2 + m_DDXChange3 ) / 2;
	rslt.Format(_T("%d"), IRslt);
	m_EdtTreight.SetWindowTextA(rslt.GetBuffer(1024));

	m_EdtChange2.GetWindowTextA(rslt);
	IRslt = _ttoi(rslt);
	m_EdtChange3.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	m_EdtChange4.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	m_EdtTreight.GetWindowTextA(rslt);
	IRslt += _ttoi(rslt);
	rslt.Format(_T("%d"), IRslt);
	m_EdtMoney.SetWindowTextA(rslt.GetBuffer(1024));
}


void CCALC_GrainDlg::OnBnClickedbtnnew()
{
	// TODO: Add your control notification handler code here

	

	data Ldata;
	CString rslt;
	m_EdtName.GetWindowTextA(rslt);
	Ldata.Name= rslt;
	m_edtBuyCNT.GetWindowTextA(rslt);
	Ldata.BuyCNT = rslt;
	m_edtCounCNT.GetWindowTextA(rslt);
	Ldata.CounCNT = rslt;
	m_edtMrmainCNT.GetWindowTextA(rslt);
	Ldata.MrmainCNT = rslt;
	m_EdtChange1.GetWindowTextA(rslt);
	Ldata.Change1 = rslt;
	m_EdtChange2.GetWindowTextA(rslt);
	Ldata.Change2 = rslt;
	m_EdtChange3.GetWindowTextA(rslt);
	Ldata.Change3 = rslt;
	m_EdtChange4.GetWindowTextA(rslt);
	Ldata.Change4  = rslt;

	m_EdtTreight.GetWindowTextA(rslt);
	Ldata.Treight  = rslt;
	m_EdtMoney.GetWindowTextA(rslt);
	Ldata.Money  = rslt;

	if (Ldata.Name == "" || Ldata.CounCNT == "" || Ldata.MrmainCNT == "")
		return;
	
	//m_DataVec.push_back(Ldata);
	int LIdx = m_listctrl.InsertItem(m_listctrl.GetHeaderCtrl()->GetItemCount()  ,Ldata.Name);
	m_listctrl.SetItemText(LIdx, 1, Ldata.BuyCNT);
	m_listctrl.SetItemText(LIdx, 2, Ldata.CounCNT);
	m_listctrl.SetItemText(LIdx, 3, Ldata.MrmainCNT);
	m_listctrl.SetItemText(LIdx, 4, Ldata.Change1);
	m_listctrl.SetItemText(LIdx, 5, Ldata.Change2);
	m_listctrl.SetItemText(LIdx, 6, Ldata.Change3);
	m_listctrl.SetItemText(LIdx, 7, Ldata.Change4 );
	m_listctrl.SetItemText(LIdx, 8, Ldata.Treight );
	m_listctrl.SetItemText(LIdx, 9, Ldata.Money );

	ClearItem();

}


void CCALC_GrainDlg::OnBnClickedbtnmodify()
{
	// TODO: Add your control notification handler code here
	POSITION LPos;
	int LIndex;
	data Ldata;
	CString rslt;
	LPos = m_listctrl.GetFirstSelectedItemPosition();
	LIndex = m_listctrl.GetNextSelectedItem(LPos);

	if (LIndex >= 0 || LIndex < m_listctrl.GetItemCount())
	{
		m_EdtName.GetWindowTextA(rslt);
		Ldata.Name = rslt;
		m_edtBuyCNT.GetWindowTextA(rslt);
		Ldata.BuyCNT = rslt;
		m_edtCounCNT.GetWindowTextA(rslt);
		Ldata.CounCNT = rslt;
		m_edtMrmainCNT.GetWindowTextA(rslt);
		Ldata.MrmainCNT = rslt;
		m_EdtChange1.GetWindowTextA(rslt);
		Ldata.Change1 = rslt;
		m_EdtChange2.GetWindowTextA(rslt);
		Ldata.Change2 = rslt;
		m_EdtChange3.GetWindowTextA(rslt);
		Ldata.Change3 = rslt;
		m_EdtChange4.GetWindowTextA(rslt);
		Ldata.Change4 = rslt;

		m_EdtTreight.GetWindowTextA(rslt);
		Ldata.Treight = rslt;
		m_EdtMoney.GetWindowTextA(rslt);
		Ldata.Money = rslt;

	//	m_DataVec[LIndex] = Ldata;

		m_listctrl.DeleteItem(LIndex);
		
		int LIdx = m_listctrl.InsertItem(LIndex, Ldata.Name);
		m_listctrl.SetItemText(LIdx, 1, Ldata.BuyCNT);
		m_listctrl.SetItemText(LIdx, 2, Ldata.CounCNT);
		m_listctrl.SetItemText(LIdx, 3, Ldata.MrmainCNT);
		m_listctrl.SetItemText(LIdx, 4, Ldata.Change1);
		m_listctrl.SetItemText(LIdx, 5, Ldata.Change2);
		m_listctrl.SetItemText(LIdx, 6, Ldata.Change3);
		m_listctrl.SetItemText(LIdx, 7, Ldata.Change4);
		m_listctrl.SetItemText(LIdx, 8, Ldata.Treight);
		m_listctrl.SetItemText(LIdx, 9, Ldata.Money);


	}
}


void CCALC_GrainDlg::OnBnClickedbtnread()
{
	// TODO: Add your control notification handler code here

	CStdioFile CALCOut;
	CFileDialog fileDlg2(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, NULL, NULL);
	CStdioFile *LTempFile;
	CString LPathName;
	CString LFileData;
	int LIndex = 0;
	int Start = 0;
	int FileCount = 0;
	int listctrlCount = m_listctrl.GetItemCount();
	fileDlg2.m_ofn.lpstrTitle = _T("讀取CSV檔案");
	fileDlg2.m_ofn.lpstrFilter = _T("CSV Files(*.csv)\0*.csv\0");
	fileDlg2.m_ofn.lpstrDefExt = _T("CSV");
	fileDlg2.DoModal();
	LPathName = fileDlg2.GetPathName();

	if (!CALCOut.Open(LPathName, CFile::modeRead| CFile::typeBinary))
	{
		return;
	}

	CALCOut.ReadString(LFileData);
	m_listctrl.DeleteAllItems();
	while (CALCOut.ReadString(LFileData) !=FALSE)
	{
		data Ldata;
		CString rslt;
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Name = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.BuyCNT = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.CounCNT = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.MrmainCNT = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Change1 = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Change2 = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Change3 = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Change4 = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Treight = rslt;

		LFileData = LFileData.Right(LFileData.GetLength() - (Start + 1));
		Start = LFileData.Find(',');
		rslt = LFileData.Left(Start);
		Ldata.Money = rslt;

		int LIdx = m_listctrl.InsertItem(LIndex, Ldata.Name);
		m_listctrl.SetItemText(LIdx, 1, Ldata.BuyCNT);
		m_listctrl.SetItemText(LIdx, 2, Ldata.CounCNT);
		m_listctrl.SetItemText(LIdx, 3, Ldata.MrmainCNT);
		m_listctrl.SetItemText(LIdx, 4, Ldata.Change1);
		m_listctrl.SetItemText(LIdx, 5, Ldata.Change2);
		m_listctrl.SetItemText(LIdx, 6, Ldata.Change3);
		m_listctrl.SetItemText(LIdx, 7, Ldata.Change4);
		m_listctrl.SetItemText(LIdx, 8, Ldata.Treight);
		m_listctrl.SetItemText(LIdx, 9, Ldata.Money);

		LIndex++;
	}
}


void CCALC_GrainDlg::OnBnClickedbtnsave()
{
	// TODO: Add your control notification handler code here
	CStdioFile CALCOut;
	CFileDialog fileDlg2(FALSE);
	CStdioFile *LTempFile;
	CString LPathName;
	
	int FileCount = 0;
	int listctrlCount = m_listctrl.GetItemCount();
	fileDlg2.m_ofn.lpstrTitle = _T("寫入CSV檔案");
	fileDlg2.m_ofn.lpstrFilter = _T("CSV Files(*.csv)\0*.csv\0");
	fileDlg2.m_ofn.lpstrDefExt = _T("CSV");
	fileDlg2.DoModal();
	LPathName = fileDlg2.GetPathName();

	if (!CALCOut.Open(LPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		return;
	}
	//CString LColumnStr[] = { _T("姓名"),_T("收購數量"),_T("輔導數量"),_T("餘糧數量"),_T("換算台斤"),_T("收購價款*26"),_T("輔導價款*23"),_T("餘糧價款*21.6"),_T("補助運費"),_T("實存金額") };
	CALCOut.WriteString(_T("姓名,收購數量,輔導數量,餘糧數量,換算台斤,收購價款*26,輔導價款*23, 餘糧價款*21.6,補助運費,實存金額 \r\n"));

	while (FileCount < listctrlCount)
	{
		CString LTemp;
		for (int i = 0; i < 11; i++)
		{
			LTemp.Append(  m_listctrl.GetItemText(FileCount, i));
			LTemp.Append(_T(","));
			

		}
		LTemp.Append(_T("\r\n"));
		CALCOut.WriteString(LTemp.GetBuffer(1024) );
	//	TRACE("m_XmlDataLogList[LCountIndex] =%s\n", m_XmlDataLogList[LCountIndex]);
	//	TRACE("LCountIndex =%d\n", LCountIndex);
		FileCount++;
	}
	CALCOut.Close();

}


void CCALC_GrainDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	POSITION LPos;
	int LIndex;
	data Ldata;
	CString Lrslt;
	LPos = m_listctrl.GetFirstSelectedItemPosition();
	LIndex = m_listctrl.GetNextSelectedItem(LPos);
	if (LIndex >= 0 || LIndex < m_listctrl.GetItemCount() )
	{
		//Ldata = m_DataVec[LIndex];
		Lrslt = m_listctrl.GetItemText(LIndex, 0);
		m_EdtName.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 1);
		m_edtBuyCNT.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 2);
		m_edtCounCNT.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 3);
		m_edtMrmainCNT.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 4);
		m_EdtChange1.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 5);
		m_EdtChange2.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 6);
		m_EdtChange3.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 7);
		m_EdtChange4.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 8);
		m_EdtTreight.SetWindowTextA(Lrslt);
		Lrslt = m_listctrl.GetItemText(LIndex, 9);
		m_EdtMoney.SetWindowTextA(Lrslt);
	}
	*pResult = 0;

	 
}


void CCALC_GrainDlg::OnBnClickedbtndelete()
{
	// TODO: Add your control notification handler code here
	POSITION LPos;
	int LIndex;
	int Idx = 0;
	LPos = m_listctrl.GetFirstSelectedItemPosition();
	LIndex = m_listctrl.GetNextSelectedItem(LPos);
	if (LIndex >= 0 || LIndex < m_DataVec.size())
	{
		m_listctrl.DeleteItem(LIndex);

		//for (vector<data>::iterator iter = m_DataVec.begin(); iter != m_DataVec.end(); iter++)
		//{
		//	if (Idx == LIndex)
		//	{
		//		m_DataVec.erase(iter);
		//		break;
		//	}
		//	else
		//	{
		//		Idx++;
		//	}
		//}
	}
	ClearItem();
}

double CCALC_GrainDlg::rounding(double num, int index)
{
	bool isNegative = false; // whether is negative number or not

	if (num < 0) // if this number is negative, then convert to positive number
	{
		isNegative = true;
		num = -num;
	}

	if (index >= 0)
	{
		int multiplier;
		multiplier = pow(10, index);
 		num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
	}

	if (isNegative) // if this number is negative, then convert to negative number
	{
		num = -num;
	}

	return num;
}

/****************************************************************************************
/// BOOL MakeSurePathExists( CString &Path,bool FilenameIncluded)
// 参数：//  Path    路径//  FilenameIncluded 路径是否包含文件名//
返回值://  文件是否存在//
说明://  判断Path文件(FilenameIncluded=true)是否存在,存在返回TURE，不存在返回FALSE//  自动创建目录///
****************************************************************************************/
/*BOOL CCALC_GrainDlg::MakeSurePathExists(CString &Path, bool FilenameIncluded)
{
	int Pos = 0; while ((Pos = Path.Find('//', Pos + 1)) != -1)
		CreateDirectory(Path.Left(Pos), NULL);
	if (!FilenameIncluded)
		CreateDirectory(Path, NULL);
	// 
	return ((!FilenameIncluded) ? !_access(Path, 0) : !_access(Path.Left(Path.ReverseFind('//')), 0));
	return !_access(Path, 0);
}*/
/****************************************************************************************///  
//BOOL   PrintListCtrl(CListCtrl   &list)
// 参数：//  list    需要打印的列表控件// 返回值://  TRUE:    打印成功//  FALSE:    打印失败
/****************************************************************************************/
BOOL  CCALC_GrainDlg::PrintListCtrl(CListCtrl   &list)
{
	PRINTDLG   pd;
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC;
	pd.hDC = NULL;
	pd.hwndOwner = NULL;
	pd.hInstance = NULL;
	pd.nMaxPage = 1;
	pd.nMinPage = 1;
	pd.nFromPage = 1;
	pd.nToPage = 1;
	pd.nCopies = 1;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
	//显示打印对话框，由用户来设定纸张大小等。   
	if (!PrintDlg(&pd))   return   FALSE;
	ASSERT(pd.hDC != NULL);
	int   nHorRes = GetDeviceCaps(pd.hDC, HORZRES);
	int   nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	int   nXMargin = 2;
	int   nYMargin = 2;
	TEXTMETRIC   tm;
	GetTextMetrics(pd.hDC, &tm);
	int   nCharHeight = tm.tmHeight;
	int   nCharWidth = tm.tmAveCharWidth;
	CHeaderCtrl*   pHeader = list.GetHeaderCtrl();
	//获得行，列的个数   
	int   nColCount = pHeader->GetItemCount();
	int   nLineCount = list.GetItemCount();
	int   ColOrderArray[100];
	COLATT   ca[100];
	list.GetColumnOrderArray(ColOrderArray, nColCount);
	int   nColX = nXMargin * nCharWidth;
	//检索各列的信息，确定列标题的内容长度。   
	for (int i = 0; i < nColCount; i++)
	{
		ca[i].nColIndex = ColOrderArray[i];
		LVCOLUMN   lvc;       char   text[100];
		lvc.mask = LVCF_TEXT | LVCF_SUBITEM;
		lvc.pszText = text;
		lvc.cchTextMax = 100;
		list.GetColumn(ca[i].nColIndex, &lvc);
		ca[i].strColText = lvc.pszText;
		ca[i].nSubItemIndex = lvc.iSubItem;
		ca[i].nPrintX = nColX;
		nColX += nCharWidth * strlen(ca[i].strColText);
		if (nColX > nHorRes)
		{
			DeleteDC(pd.hDC);
			AfxMessageBox("字段太多，无法在一行内打印，请试用较大的纸，或横向打印。");
			return   FALSE;
		}
	}
	DOCINFO   di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "ListCtrl   Data   Printing";
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;
	StartDoc(pd.hDC, &di);
	StartPage(pd.hDC);
	//调整各列的宽度，以使各列在后面的打印输出时更均匀的打印在纸上。  
	int   space = (nHorRes - nXMargin * nCharWidth - nColX) / (nColCount - 1);
	for (int i = 1; i < nColCount; i++)
	{
		ca[i].nPrintX += i * space;
	}      //输出列标题   
	for (int i = 0; i < nColCount; i++)
	{
		TextOut(pd.hDC, ca[i].nPrintX, nYMargin, ca[i].strColText, strlen(ca[i].strColText));
	}
	int   nMaxLinePerPage = nVerRes / nCharHeight - 3;
	int   nCurPage = 1;
	//输出各列的数据   
	for (int i = 0; i < nLineCount; i++)
	{
		for (int j = 0; j < nColCount; j++)
		{
			if (i + 1 - (nCurPage - 1)*nMaxLinePerPage > nMaxLinePerPage)
			{
				//新的一页    
				EndPage(pd.hDC);
				StartPage(pd.hDC);
				nCurPage++;
			}
			CString   subitem = list.GetItemText(i, ca[j].nColIndex);
			TextOut(pd.hDC, ca[j].nPrintX, nYMargin + (i + 1 - (nCurPage - 1)*nMaxLinePerPage)*nCharHeight, subitem, strlen(subitem));
		}
	}
	EndPage(pd.hDC);
	EndDoc(pd.hDC);
	//打印结束   
	DeleteDC(pd.hDC);
	return   TRUE;
}



void CCALC_GrainDlg::OnBnClickedbtnprint()
{
	// TODO: Add your control notification handler code here
	PrintListCtrl(m_listctrl);
}
