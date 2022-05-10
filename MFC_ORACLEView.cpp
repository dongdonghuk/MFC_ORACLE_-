
// MFC_ORACLEView.cpp: CMFCORACLEView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_ORACLE.h"
#endif

#include "MFC_ORACLEDoc.h"
#include "MFC_ORACLEView.h"
#include "CHospitalDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CHospitalFindDlg.h"


// CMFCORACLEView


vector<CHospitalPtr> GetListHospital(CDatabase& db)
{
	vector<CHospitalPtr> resultList;

	//2. SQL 구문 실행 
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, _T("select \
		a.번호,\
		a.인허가일자,\
		b.영업상태명,\
		a.상세영업상태코드,\
		a.상세영업상태명,\
		a.소재지전화,\
		a.도로명전체주소,\
		a.도로명우편번호,\
		a.사업장명,\
		a.업태구분명,\
		a.의료기관종별명,\
		a.의료인수,\
		a.입원실수,\
		a.병상수,\
		a.진료과목내용명\
		from 병원 a, 병원영업상태 b\
		where a.영업상태명 = b.영업상태값;"));

	//3. SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체생성함
		CHospitalPtr pHospital = make_shared<CHospital>();
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		rs.GetFieldValue((short)0, pHospital->strNo);
		rs.GetFieldValue((short)1, pHospital->strDate);
		rs.GetFieldValue((short)2, pHospital->strSName);
		rs.GetFieldValue((short)3, pHospital->strDetailCode);
		rs.GetFieldValue((short)4, pHospital->strDetailStatus);
		rs.GetFieldValue((short)5, pHospital->strCallNum);
		rs.GetFieldValue((short)6, pHospital->strAderss);
		rs.GetFieldValue((short)7, pHospital->strZipCode);
		rs.GetFieldValue((short)8, pHospital->strHName);
		rs.GetFieldValue((short)9, pHospital->strCol1);
		rs.GetFieldValue((short)10, pHospital->strCol2);
		rs.GetFieldValue((short)11, pHospital->strDoctorNum);
		rs.GetFieldValue((short)12, pHospital->strRoomNum);
		rs.GetFieldValue((short)13, pHospital->strBedNum);
		rs.GetFieldValue((short)14, pHospital->strMedicalClass);


		rs.MoveNext();

		//배열에 스마트 포인터 객체를 추가한다 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}


CHospitalPtr GetHospital(CDatabase& db, CString strEmpNo)
{
	//스마트 포인터를 이용하여 객체생성함
	CHospitalPtr pHospital = make_shared<CHospital>();

	//2. SQL 구문 실행 
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, _T("select \
		a.번호,\
		TO_CHAR(TO_DATE(a.인허가일자, 'YYYYMMDD'), 'DD/MM/YYYY'),\
		b.영업상태명,\
		a.상세영업상태코드,\
		a.상세영업상태명,\
		a.소재지전화,\
		a.도로명전체주소,\
		a.도로명우편번호,\
		a.사업장명,\
		a.업태구분명,\
		a.의료기관종별명,\
		a.의료인수,\
		a.입원실수,\
		a.병상수,\
		a.진료과목내용명\
		from 병원 a, 병원영업상태 b\
		where a.영업상태명 = b.영업상태값 and a.번호 ="+strEmpNo));

	//3. SQL 구문 실행 결과 얻기 
	if (!rs.IsEOF()) {

		rs.GetFieldValue((short)0, pHospital->strNo);
		rs.GetFieldValue((short)1, pHospital->strDate);
		rs.GetFieldValue((short)2, pHospital->strSName);
		rs.GetFieldValue((short)3, pHospital->strDetailCode);
		rs.GetFieldValue((short)4, pHospital->strDetailStatus);
		rs.GetFieldValue((short)5, pHospital->strCallNum);
		rs.GetFieldValue((short)6, pHospital->strAderss);
		rs.GetFieldValue((short)7, pHospital->strZipCode);
		rs.GetFieldValue((short)8, pHospital->strHName);
		rs.GetFieldValue((short)9, pHospital->strCol1);
		rs.GetFieldValue((short)10, pHospital->strCol2);
		rs.GetFieldValue((short)11, pHospital->strDoctorNum);
		rs.GetFieldValue((short)12, pHospital->strRoomNum);
		rs.GetFieldValue((short)13, pHospital->strBedNum);
		rs.GetFieldValue((short)14, pHospital->strMedicalClass);
	}
	rs.Close();

	return pHospital;
}

CString GetHospitalInsertNo(CDatabase& db)
{
	CString strNo;

	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly,
		_T("select max(cast(번호 as int))+1 from 병원;"));

	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, strNo);
	}
	rs.Close();

	return strNo;

}


vector<CHospitalPtr> GetListHospitalFind(CDatabase& db, CString strHName, CString strCallNum)
{
	vector<CHospitalPtr> resultList;

	//1. 검색 SQL 구문 생성
	CString strSQL;

	strSQL.Format(_T("select \
		a.번호,\
		a.인허가일자,\
		b.영업상태명,\
		a.상세영업상태코드,\
		a.상세영업상태명,\
		a.소재지전화,\
		a.도로명전체주소,\
		a.도로명우편번호,\
		a.사업장명,\
		a.업태구분명,\
		a.의료기관종별명,\
		a.의료인수,\
		a.입원실수,\
		a.병상수,\
		a.진료과목내용명\
		from 병원 a, 병원영업상태 b\
		where a.영업상태명 = b.영업상태값\
			and a.사업장명 like '%s%%'\
		    and a.소재지전화 like '%s%%'\
		"), strHName.GetBuffer()
		, strCallNum.GetBuffer());

	CRecordset rs(&db);

	rs.Open(CRecordset::forwardOnly, strSQL.GetBuffer());

	//3. SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체생성함
		CHospitalPtr pHospital = make_shared<CHospital>();

		if (pHospital == nullptr) return vector<CHospitalPtr>();

		rs.GetFieldValue((short)0, pHospital->strNo);
		rs.GetFieldValue((short)1, pHospital->strDate);
		rs.GetFieldValue((short)2, pHospital->strSName);
		rs.GetFieldValue((short)3, pHospital->strDetailCode);
		rs.GetFieldValue((short)4, pHospital->strDetailStatus);
		rs.GetFieldValue((short)5, pHospital->strCallNum);
		rs.GetFieldValue((short)6, pHospital->strAderss);
		rs.GetFieldValue((short)7, pHospital->strZipCode);
		rs.GetFieldValue((short)8, pHospital->strHName);
		rs.GetFieldValue((short)9, pHospital->strCol1);
		rs.GetFieldValue((short)10, pHospital->strCol2);
		rs.GetFieldValue((short)11, pHospital->strDoctorNum);
		rs.GetFieldValue((short)12, pHospital->strRoomNum);
		rs.GetFieldValue((short)13, pHospital->strBedNum);
		rs.GetFieldValue((short)14, pHospital->strMedicalClass);

		rs.MoveNext();

		//배열에 스마트 포인터 객체를 추가한다 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}




BOOL InsertHospital(CDatabase& db, CHospitalPtr pHospital)
{
	//1.  등록할 SQL 구문 만든다
	CString strSQL;
	strSQL.Format(_T("insert into 병원 (\
			번호,\
			인허가일자,\
			영업상태명,\
			상세영업상태코드,\
			상세영업상태명,\
			소재지전화,\
			도로명전체주소,\
			도로명우편번호,\
			사업장명,\
			업태구분명,\
			의료기관종별명,\
			의료인수,\
			입원실수,\
			병상수,\
			진료과목내용명\
			) values ( \
		%s, \
		%s, \
		%s, \
		%s, \
		'%s', \
		'%s', \
		'%s', \
		%s, \
		'%s', \
		'%s', \
		'%s', \
		%s, \
		%s, \
		%s, \
		'%s')"),
		pHospital->strNo.GetBuffer(),
		pHospital->strDate.GetBuffer(),
		pHospital->strSValue.GetBuffer(),
		pHospital->strDetailCode.GetBuffer(),
		pHospital->strDetailStatus.GetBuffer(),
		pHospital->strCallNum.GetBuffer(),
		pHospital->strAderss.GetBuffer(),
		pHospital->strZipCode.GetBuffer(),
		pHospital->strHName.GetBuffer(),
		pHospital->strCol1.GetBuffer(),
		pHospital->strCol2.GetBuffer(),
		pHospital->strDoctorNum.GetBuffer(),
		pHospital->strRoomNum.GetBuffer(),
		pHospital->strBedNum.GetBuffer(),
		pHospital->strMedicalClass.GetBuffer());


	AfxMessageBox(strSQL);

	try {
		db.BeginTrans();
		db.ExecuteSQL(strSQL.GetBuffer());
		db.CommitTrans();
	}
	catch (const CException* pEx) {
		db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}

BOOL UpdateHospital(CDatabase& db, CHospitalPtr pHospital)
{
	//1.  수정할 SQL 구문 만든다
	CString strSQL;
	strSQL.Format(_T("update 병원 set \
			인허가일자=%s, \
			영업상태명=%s, \
			상세영업상태코드=%s, \
			상세영업상태명='%s', \
			소재지전화='%s', \
			도로명전체주소='%s', \
			도로명우편번호=%s, \
			사업장명='%s', \
			업태구분명='%s', \
			의료기관종별명='%s', \
			의료인수=%s, \
			입원실수=%s, \
			병상수=%s, \
			진료과목내용명='%s' \
			where 번호=%s"),
		pHospital->strDate.GetBuffer(),
		pHospital->strSValue.GetBuffer(),
		pHospital->strDetailCode.GetBuffer(),
		pHospital->strDetailStatus.GetBuffer(),
		pHospital->strCallNum.GetBuffer(),
		pHospital->strAderss.GetBuffer(),
		pHospital->strZipCode.GetBuffer(),
		pHospital->strHName.GetBuffer(),
		pHospital->strCol1.GetBuffer(),
		pHospital->strCol2.GetBuffer(),
		pHospital->strDoctorNum.GetBuffer(),
		pHospital->strRoomNum.GetBuffer(),
		pHospital->strBedNum.GetBuffer(),
		pHospital->strMedicalClass.GetBuffer(),
		pHospital->strNo.GetBuffer());


	try {
		db.BeginTrans();
		db.ExecuteSQL(strSQL.GetBuffer());
		db.CommitTrans();
	}
	catch (const CException* pEx) {
		db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}


	return TRUE;
}


vector<CStatePtr> GetListState(CDatabase& db)
{
	vector<CStatePtr> resultList;

	//2. SQL 구문 실행 
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, _T("select * from 병원영업상태"));

	//3. SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체생성함
		CStatePtr pState = make_shared<CState>();
		if (pState == nullptr) return vector<CStatePtr>();

		rs.GetFieldValue((short)0, pState->strSValue);
		rs.GetFieldValue((short)1, pState->strSName);

		rs.MoveNext();

		//배열에 스마트 포인터 객체를 추가한다 
		resultList.push_back(pState);
	}
	rs.Close();

	return resultList;
}


IMPLEMENT_DYNCREATE(CMFCORACLEView, CFormView)

BEGIN_MESSAGE_MAP(CMFCORACLEView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCORACLEView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_REVISE, &CMFCORACLEView::OnBnClickedButtonRevise)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMFCORACLEView::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMFCORACLEView::OnBnClickedButtonSearch)
END_MESSAGE_MAP()

// CMFCORACLEView 생성/소멸

CMFCORACLEView::CMFCORACLEView() noexcept
	: CFormView(IDD_MFC_ORACLE_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BOOL bRet = m_db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (!bRet) {
		AfxMessageBox(_T("DB 연결 실패"));
	}
}

CMFCORACLEView::~CMFCORACLEView()
{
	//DB 연결 종료 
	if (m_db.IsOpen()) {
		m_db.Close();
	}
}

void CMFCORACLEView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listView);
}

BOOL CMFCORACLEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}


void CMFCORACLEView::SetHospitalListView(int nRow, const CHospitalPtr pHospital)
{
	m_listView.SetItemText(nRow, 1, pHospital->strDate);
	m_listView.SetItemText(nRow, 2, pHospital->strSName);
	m_listView.SetItemText(nRow, 3, pHospital->strDetailCode);
	m_listView.SetItemText(nRow, 4, pHospital->strDetailStatus);
	m_listView.SetItemText(nRow, 5, pHospital->strCallNum);
	m_listView.SetItemText(nRow, 6, pHospital->strAderss);
	m_listView.SetItemText(nRow, 7, pHospital->strZipCode);
	m_listView.SetItemText(nRow, 8, pHospital->strHName);
	m_listView.SetItemText(nRow, 9, pHospital->strCol1);
	m_listView.SetItemText(nRow, 10, pHospital->strCol2);
	m_listView.SetItemText(nRow, 11, pHospital->strDoctorNum);
	m_listView.SetItemText(nRow, 12, pHospital->strRoomNum);
	m_listView.SetItemText(nRow, 13, pHospital->strBedNum);
	m_listView.SetItemText(nRow, 14, pHospital->strMedicalClass);

}


void CMFCORACLEView::GetDBAllHospitalListView(vector<CHospitalPtr> hospitalList)
{
	m_listView.DeleteAllItems();

	//사원 전체 목록을 얻는다
	//vector<CHospitalPtr> hospitalList = GetListHospital(m_db);

	//3. SQL 구문 실행 결과 얻기 
	int nRow = 0;
	for (const auto& pHospital : hospitalList) {
		m_listView.InsertItem(nRow, pHospital->strNo, 0);
		SetHospitalListView(nRow, pHospital);

		nRow++;
	}
}




void CMFCORACLEView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_imageList.Create(48, 48, ILC_COLOR32, 5, 5);
	m_imageListSmall.Create(16, 16, ILC_COLOR32, 5, 5);

	m_imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_imageListSmall.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	m_listView.SetImageList(&m_imageList, LVSIL_NORMAL);
	m_listView.SetImageList(&m_imageListSmall, LVSIL_SMALL);

	//컬럼 정보 출력 
	m_listView.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(1, _T("인허가일자"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(2, _T("영업상태명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(3, _T("상세영업상태코드"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(4, _T("상세영업상태명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(5, _T("소재지전화"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(6, _T("도로명전체주소"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(7, _T("도로명우편번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(8, _T("사업장명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(9, _T("업태구분명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(10, _T("의료기관종별명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(11, _T("의료인수"), LVCFMT_LEFT, 40);
	m_listView.InsertColumn(12, _T("입원실수"), LVCFMT_LEFT, 40);
	m_listView.InsertColumn(13, _T("병상수"), LVCFMT_LEFT, 40);
	m_listView.InsertColumn(14, _T("strMedicalClass"), LVCFMT_LEFT, 100);

	DWORD dwExStyle = m_listView.GetExtendedStyle();
	m_listView.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	/*
	1. DB 연결
	2. SQL 실행
	3. SQL 결과 얻기
	4. 연결 종료


	CDatabase 클래스는 DB 연결 관리 하는 클래스
	CRecordSet 클래스는 SQL 구문을 실행하고 결과 집합을 관리하는 클래스

	*/
	GetDBAllHospitalListView(GetListHospital(m_db));

}


// CMFCORACLEView 인쇄

BOOL CMFCORACLEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCORACLEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCORACLEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCORACLEView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CMFCORACLEView 진단

#ifdef _DEBUG
void CMFCORACLEView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCORACLEView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCORACLEDoc* CMFCORACLEView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCORACLEDoc)));
	return (CMFCORACLEDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCORACLEView 메시지 처리기


void CMFCORACLEView::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	const int nCount = m_listView.GetItemCount();
	CString strEmpNo;
	CString strSQL;
	CString strSQL2;

	CString strInParam;
	CArray<int, int> arr;

	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			strEmpNo = m_listView.GetItemText(i, 0);
			strInParam += strEmpNo + _T(",");
			arr.Add(i);
		}
	}

	try {
		if (!strInParam.IsEmpty()) {
			strInParam.Delete(strInParam.GetLength() - 1, 1);

			strSQL = _T("delete from 병원 where 번호 in (") + strInParam + _T(")");
			
			strSQL2 = _T("delete from 병원진료과목목록 where 번호 in (") + strInParam + _T(")");


			//트랜젝션 시작 //DML
			m_db.BeginTrans();

			m_db.ExecuteSQL(strSQL);
			m_db.ExecuteSQL(strSQL2);

			//트랜젝션 완료 //DML
			m_db.CommitTrans();
			//리스트에서 삭제 항목을 제거한다
			for (int i = 0; i < arr.GetSize(); i++) {
				//목록에서 제거한다 
				m_listView.DeleteItem(arr.GetAt(i));
			}
		}
	}
	catch (const CException* p) {
		//트랜젝션 복구 //DML
		m_db.Rollback();
		TCHAR szErr[100];
		p->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
	}
}


void CMFCORACLEView::OnBnClickedButtonRevise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const int nCount = m_listView.GetItemCount();
	CString strHNo;

	//선택된 사번을 얻는다
	int nRow;
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			//선택된 사원 번호를 얻는다
			strHNo = m_listView.GetItemText(i, 0);
			nRow = i;
			break;
		}
	}

	if (strHNo.IsEmpty()) {
		AfxMessageBox(_T("병원을 선택해 주세요"));
		return;
	}

	vector<CStatePtr>	stateList = GetListState(m_db);

	CHospitalPtr pHospital = GetHospital(m_db, strHNo);

	CHospitalDialog dlg(stateList, pHospital);




	if (dlg.DoModal() == IDOK) {
		//수정 

		pHospital->strNo.Format(_T("%d"), dlg.m_strNo);
		pHospital->strDate = dlg.m_date.Format(_T(" %Y%m%d"));
		pHospital->strDetailCode.Format(_T("%d"), dlg.m_nDetailCode);
		pHospital->strDetailStatus = dlg.m_strDetailStatus;
		pHospital->strCallNum = dlg.m_strCallNum;
		pHospital->strAderss = dlg.m_strAderss;
		pHospital->strZipCode.Format(_T("%d"), dlg.m_nZipCode);
		pHospital->strHName = dlg.m_strHName;
		pHospital->strCol1 = dlg.m_strCol1;
		pHospital->strCol2 = dlg.m_strCol2;
		pHospital->strDoctorNum.Format(_T("%d"), dlg.m_nDoctorNum);
		pHospital->strRoomNum.Format(_T("%d"), dlg.m_nRoomNum);
		pHospital->strBedNum.Format(_T("%d"), dlg.m_nBedNum);
		pHospital->strSName = dlg.m_strHState;
		pHospital->strSValue = dlg.m_strSvalue;
		pHospital->strMedicalClass = dlg.m_strMedicalClass;

		if (UpdateHospital(m_db, pHospital)) {
			//리스트 컨트롤 화면 변경 
			//GetDBAllEmpListView();
			SetHospitalListView(nRow, pHospital);
		}
	}

}






void CMFCORACLEView::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vector<CStatePtr>	stateList = GetListState(m_db);

	CHospitalPtr pHospital = make_shared<CHospital>();

	pHospital->strNo = GetHospitalInsertNo(m_db);
	pHospital->strDate = "10/05/2022";

	CHospitalDialog dlg(stateList, pHospital);

	if (dlg.DoModal() == IDOK) {
		//수정 

		pHospital->strDate = dlg.m_date.Format(_T(" %Y%M%d"));
		pHospital->strDetailCode.Format(_T("%d"), dlg.m_nDetailCode);
		pHospital->strDetailStatus = dlg.m_strDetailStatus;
		pHospital->strCallNum = dlg.m_strCallNum;
		pHospital->strAderss = dlg.m_strAderss;
		pHospital->strZipCode.Format(_T("%d"), dlg.m_nZipCode);
		pHospital->strHName = dlg.m_strHName;
		pHospital->strCol1 = dlg.m_strCol1;
		pHospital->strCol2 = dlg.m_strCol2;
		pHospital->strDoctorNum.Format(_T("%d"), dlg.m_nDoctorNum);
		pHospital->strRoomNum.Format(_T("%d"), dlg.m_nRoomNum);
		pHospital->strBedNum.Format(_T("%d"), dlg.m_nBedNum);
		pHospital->strSName = dlg.m_strHState;
		pHospital->strSValue = dlg.m_strSvalue;
		pHospital->strMedicalClass = dlg.m_strMedicalClass;

		if (InsertHospital(m_db, pHospital)) {
			int nRow = m_listView.GetItemCount();
			m_listView.InsertItem(nRow, pHospital->strNo, 0);
			SetHospitalListView(nRow, pHospital);
		}

	}

}


void CMFCORACLEView::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CHospitalFindDlg dlg;
	if (dlg.DoModal() == IDOK) {
		GetDBAllHospitalListView(GetListHospitalFind(m_db, dlg.m_strHName, dlg.m_strCallNum));
	}
}
