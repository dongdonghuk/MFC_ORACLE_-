#pragma once


// CHospitalFindDlg 대화 상자

class CHospitalFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHospitalFindDlg)

public:
	CHospitalFindDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHospitalFindDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITAL_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strHName;
	CString m_strCallNum;
};
