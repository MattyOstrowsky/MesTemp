#pragma once


// Okno dialogowe error

class error : public CDialogEx
{
	DECLARE_DYNAMIC(error)

public:
	error(CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~error();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP()
};
