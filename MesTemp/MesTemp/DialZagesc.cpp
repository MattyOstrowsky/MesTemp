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
{

}

DialZagesc::~DialZagesc()
{
}

void DialZagesc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialZagesc, CDialogEx)
END_MESSAGE_MAP()


// Procedury obsługi komunikatów DialZagesc
