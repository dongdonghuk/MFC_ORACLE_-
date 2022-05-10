// CHospitalFindDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_ORACLE.h"
#include "CHospitalFindDlg.h"
#include "afxdialogex.h"


// CHospitalFindDlg 대화 상자

IMPLEMENT_DYNAMIC(CHospitalFindDlg, CDialogEx)

CHospitalFindDlg::CHospitalFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_SEARCH, pParent)
	, m_strHName(_T(""))
	, m_strCallNum(_T(""))
{

}

CHospitalFindDlg::~CHospitalFindDlg()
{
}

void CHospitalFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEARCH_NAME, m_strHName);
	DDX_Text(pDX, IDC_SEARCH_PHONE, m_strCallNum);
}


BEGIN_MESSAGE_MAP(CHospitalFindDlg, CDialogEx)
	ON_EN_CHANGE(IDC_SEARCH_NAME, &CHospitalFindDlg::OnEnChangeSearchName)
END_MESSAGE_MAP()


// CHospitalFindDlg 메시지 처리기



