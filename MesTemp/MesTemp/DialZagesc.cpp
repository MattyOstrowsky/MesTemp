// DialZagesc.cpp: plik implementacji
//

#include "pch.h"
#include "MesTemp.h"
#include "DialZagesc.h"
#include "afxdialogex.h"


// Okno dialogowe DialZagesc

IMPLEMENT_DYNAMIC(DialZagesc, CDialogEx)

DialZagesc::DialZagesc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, zag_x(1)
	, zag_y(1)

	, Bzag_x(FALSE)
	, Bzag_y(FALSE)
{

}

DialZagesc::~DialZagesc()
{
}

void DialZagesc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Text(pDX, IDC_EDIT2, zag_x);
	DDV_MinMaxInt(pDX, zag_x, 1, 255);
	DDX_Control(pDX, IDC_SPIN2, spin_x);
	DDX_Text(pDX, IDC_EDIT5, zag_y);
	DDV_MinMaxInt(pDX, zag_y, 1, 255);
	DDX_Control(pDX, IDC_SPIN3, spin_y);



	DDX_Check(pDX, IDC_CHECK1, Bzag_x);
	DDX_Check(pDX, IDC_CHECK2, Bzag_y);
}


BEGIN_MESSAGE_MAP(DialZagesc, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &DialZagesc::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &DialZagesc::OnBnClickedCheck2)
END_MESSAGE_MAP()


// Procedury obsługi komunikatów DialZagesc


void DialZagesc::OnBnClickedCheck1()
{
	//SetDlgItemText(IDC_EDIT2, TEXT("2"));
	GetDlgItem(IDC_EDIT2)->EnableWindow(!Bzag_x);
	GetDlgItem(IDC_SPIN2)->EnableWindow(!Bzag_x);
	UpdateData(TRUE);
}


void DialZagesc::OnBnClickedCheck2()
{
	GetDlgItem(IDC_EDIT5)->EnableWindow(!Bzag_y);
	GetDlgItem(IDC_SPIN3)->EnableWindow(!Bzag_y);
	UpdateData(TRUE);
}
