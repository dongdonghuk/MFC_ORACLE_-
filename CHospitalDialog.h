#pragma once

#include "hospital.h"

// CHospitalDialog 대화 상자

class CHospitalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHospitalDialog)

public:
	CHospitalDialog(vector<CStatePtr>&stateList, 
					CHospitalPtr pHospital,CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHospitalDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITAL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	vector<CStatePtr>& m_stateList;
	CHospitalPtr m_pHospital;

	int m_strNo;
	COleDateTime m_date;
	int m_nDetailCode;
	CString m_strDetailStatus;
	CString m_strCallNum;
	CString m_strAderss;
	int m_nZipCode;
	CString m_strHName;
	CString m_strCol1;
	CString m_strCol2;
	int m_nDoctorNum;
	int m_nRoomNum;
	int m_nBedNum;
	CString m_strMedicalClass;
	CString m_strHState;
	CString m_strSvalue;

	CComboBox m_comboHState;


	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelendokHospitalState();
};
