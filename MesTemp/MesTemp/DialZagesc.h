#pragma once


// Okno dialogowe DialZagesc

class DialZagesc : public CDialogEx
{
	DECLARE_DYNAMIC(DialZagesc)

public:
	DialZagesc(CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~DialZagesc();
	

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int zag_x;
	CSpinButtonCtrl spin_x;
	int zag_y;
	CSpinButtonCtrl spin_y;
	
	BOOL Bzag_x;
	afx_msg void OnBnClickedCheck1();
	BOOL Bzag_y;
	afx_msg void OnBnClickedCheck2();
};
