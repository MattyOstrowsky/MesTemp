// error.cpp: plik implementacji
//

#include "pch.h"
#include "MesTemp.h"
#include "error.h"
#include "afxdialogex.h"


// Okno dialogowe error

IMPLEMENT_DYNAMIC(error, CDialogEx)

error::error(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

error::~error()
{
}

void error::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(error, CDialogEx)
END_MESSAGE_MAP()


// Procedury obsługi komunikatów error
