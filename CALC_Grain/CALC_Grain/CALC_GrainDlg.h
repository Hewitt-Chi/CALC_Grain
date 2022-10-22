
// CALC_GrainDlg.h : header file
//

#pragma once
#include <vector>
using namespace std;
// CCALC_GrainDlg dialog
class CCALC_GrainDlg : public CDialogEx
{
// Construction
public:
	CCALC_GrainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALC_GRAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	typedef struct tagColAtt
	{
		int nColIndex;
		CString strColText;
		int nPrintX;
		int nSubItemIndex;


	}COLATT;
	

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitListCtrl();
	void ClearItem();

	double rounding(double num, int index);
//	BOOL MakeSurePathExists(CString &Path, bool FilenameIncluded);
	BOOL PrintListCtrl(CListCtrl   &list);
private:

	struct data
	{
		CString Name;
		CString BuyCNT;
		CString CounCNT;
		CString MrmainCNT;
		CString Change1;
		CString Change2;
		CString Change3;
		CString Change4;
		CString Treight;
		CString Money;
	};

	vector<data> m_DataVec;

	CEdit m_EdtName;
	CEdit m_edtBuyCNT;
	CEdit m_edtCounCNT;
	CEdit m_edtMrmainCNT;
	CEdit m_EdtChange1;
	CEdit m_EdtChange2;
	CEdit m_EdtChange3;
	CEdit m_EdtChange4;
	CEdit m_EdtTreight;
	CEdit m_EdtMoney;
	CListCtrl m_listctrl;

	int m_DDXChange1;
	int m_DDXChange2;
	int m_DDXChange3;
	int m_DDXChange4;

	int m_Rslt1;
	int m_Rslt2;
	int m_Rslt3;
	int m_Rslt4;

	CFont m_Font;

//	CString m_ColumnStr[11];
public:
	afx_msg void OnEnChangeEdtbuycnt();
	afx_msg void OnBnClickedOk();

	afx_msg void OnEnChangeEdtcoun();
	afx_msg void OnEnChangeEdtremaincnt();
	afx_msg void OnBnClickedbtnnew();
	afx_msg void OnBnClickedbtnmodify();
	afx_msg void OnBnClickedbtnread();
	afx_msg void OnBnClickedbtnsave();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedbtndelete();
	afx_msg void OnBnClickedbtnprint();
};
