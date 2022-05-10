// CHospitalDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_ORACLE.h"
#include "CHospitalDialog.h"
#include "afxdialogex.h"


// CHospitalDialog 대화 상자

IMPLEMENT_DYNAMIC(CHospitalDialog, CDialogEx)

CHospitalDialog::CHospitalDialog( 
								vector<CStatePtr>& stateList,
								CHospitalPtr pHospital, 
								CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_DLG, pParent)
	, m_stateList(stateList)
	, m_pHospital(pHospital)
	, m_strNo(0)
	, m_date(COleDateTime::GetCurrentTime())
	, m_nDetailCode(0)
	, m_strDetailStatus(_T(""))
	, m_strCallNum(_T(""))
	, m_strAderss(_T(""))
	, m_nZipCode(0)
	, m_strHName(_T(""))
	, m_strCol1(_T(""))
	, m_strCol2(_T(""))
	, m_nDoctorNum(0)
	, m_nRoomNum(0)
	, m_nBedNum(0)
	, m_strMedicalClass(_T(""))
	, m_strHState(_T(""))
{

}

CHospitalDialog::~CHospitalDialog()
{
}

void CHospitalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOSPITAL_NUM, m_strNo);
	DDX_DateTimeCtrl(pDX, IDC_HOSPITAL_DATE, m_date);
	DDX_Text(pDX, IDC_HOSPITAL_DETAIL, m_nDetailCode);
	DDX_Text(pDX, IDC_HOSPITAL_DETAIL_NUM, m_strDetailStatus);
	DDX_Text(pDX, IDC_HOSPITAL_PHONE, m_strCallNum);
	DDX_Text(pDX, IDC_HOSPITAL_ADRESS, m_strAderss);
	DDX_Text(pDX, IDC_HOSPITAL_ZIPCODE, m_nZipCode);
	DDX_Text(pDX, IDC_HOSPITAL_NAME, m_strHName);
	DDX_Text(pDX, IDC_HOSPITAL_COLUMN1, m_strCol1);
	DDX_Text(pDX, IDC_HOSPITAL_COLUMN2, m_strCol2);
	DDX_Text(pDX, IDC_HOSPITAL_DOCTOR, m_nDoctorNum);
	DDX_Text(pDX, IDC_HOSPITAL_ROOM, m_nRoomNum);
	DDX_Text(pDX, IDC_HOSPITAL_BED, m_nBedNum);
	DDX_Text(pDX, IDC_MEDICAL_CLASS, m_strMedicalClass);
	DDX_CBString(pDX, IDC_HOSPITAL_STATE, m_strHState);
	DDX_Control(pDX, IDC_HOSPITAL_STATE, m_comboHState);
}


BEGIN_MESSAGE_MAP(CHospitalDialog, CDialogEx)
	ON_CBN_SELENDOK(IDC_HOSPITAL_STATE, &CHospitalDialog::OnCbnSelendokHospitalState)
END_MESSAGE_MAP()


// CHospitalDialog 메시지 처리기


BOOL CHospitalDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_strNo = _ttoi(m_pHospital->strNo);
	m_date.ParseDateTime(m_pHospital->strDate);
	m_nDetailCode = _ttoi(m_pHospital->strDetailCode);
	m_strDetailStatus = m_pHospital->strDetailStatus;
	m_strCallNum = m_pHospital->strCallNum;
	m_strAderss = m_pHospital->strAderss;
	m_nZipCode = _ttoi(m_pHospital->strZipCode);
	m_strHName = m_pHospital->strHName;
	m_strCol1 = m_pHospital->strCol1;
	m_strCol2 = m_pHospital->strCol2;
	m_nDoctorNum = _ttoi(m_pHospital->strDoctorNum);
	m_nRoomNum = _ttoi(m_pHospital->strRoomNum);
	m_nBedNum = _ttoi(m_pHospital->strBedNum);
	m_strMedicalClass = m_pHospital->strMedicalClass;
	m_strHState = m_pHospital->strSName;

	int nIndex = 0;
	//combobox에 출력한 부서명을 추가한다
	for (const auto& pState : m_stateList) {
		m_comboHState.InsertString(nIndex++, pState->strSName);
		if (pState->strSName == m_strHState)
			m_strSvalue = pState->strSValue;
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHospitalDialog::OnCbnSelendokHospitalState()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int nCurSel = m_comboHState.GetCurSel();

	if (nCurSel >= 0 && nCurSel <= m_stateList.size() - 1) {

		const CStatePtr pState = m_stateList[nCurSel];

		m_pHospital->strSName = pState->strSName;
		m_strSvalue = pState->strSValue;

	}
}
