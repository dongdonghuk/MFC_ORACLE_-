
#pragma once

#include <memory>
#include <vector>

using namespace std;

class CHospital {
public:
	CHospital() :
		strNo(_T("")),
		strDate(_T("")),
		strSName(_T("")),
		strSValue(_T("")),
		strDetailCode(_T("")),
		strDetailStatus(_T("")),
		strCallNum(_T("")),
		strAderss(_T("")),
		strZipCode(_T("")),
		strHName(_T("")),
		strCol1(_T("")),
		strCol2(_T("")),
		strDoctorNum(_T("")),
		strRoomNum(_T("")),
		strBedNum(_T("")),
		strMedicalClass(_T(""))
	{

	}
	CString strNo;
	CString strDate;
	CString strSName;
	CString strSValue;
	CString strDetailCode;
	CString strDetailStatus;
	CString strCallNum;     
	CString strAderss;
	CString strZipCode;
	CString strHName;
	CString strCol1;
	CString strCol2;
	CString strDoctorNum;
	CString strRoomNum;
	CString strBedNum;
	CString strMedicalClass;



};
using CHospitalPtr = shared_ptr<CHospital>;

class CState {
public:
	CString strSValue;
	CString strSName;
};
using CStatePtr = shared_ptr<CState>;


CHospitalPtr GetHospital(CDatabase& db, CString strEmpNo);