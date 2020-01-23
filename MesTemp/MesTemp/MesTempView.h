
// MesTempView.h : interface of the CMesTempView class
//

#pragma once
#include "MesTempDoc.h"
#include "Siatka.h"
#include "DialZagesc.h"

class CMesTempView : public CView
{
protected: // create from serialization only
	CMesTempView() noexcept;
	DECLARE_DYNCREATE(CMesTempView)

// Attributes
public:
	
	CMesTempDoc* GetDocument() const;
	bool Rysuj = false;
	CString FilePathName;
	float liczba_obszarow;
	float skala=1;
	int zag_y = 0;
	int zag_x = 0;
	float yos0 = 590;
	float xos0 = 15;
	float yos00 = 590;
	float xos00 = 15;
	bool czy_pokrywa = false;
	bool RysSiatka = false;
	float x_max = 0;
	float y_max = 0;
	float xPos;
	float yPos;
	float skalaTrue;
	bool TempRysuj = false;
	bool RozRysuj = false;
	bool RysSiatkaU = false;
	bool RozRysujU = false;
	bool TempRysujU = false;

	//std::vector<float> wynikRozw;
	
	
// Operations
public:
	std::vector <Input> wektor_obszarow;
	std::vector <WarunkiBrzegowe> wektor_warunkow_brzegowych;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMesTempView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStartZag();
	afx_msg void OnFileOpen();
	afx_msg void OnStartGeneruj();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuPrzybli();
	afx_msg void OnMenuOddal();
	afx_msg void OnStartZag32777();
	afx_msg void OnStartRozk();
	void RysujObszary(CDC* pDC);
	
	
	afx_msg void OnUpdateStartGeneruj(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStartZag32777(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStartRysujtemperatury(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStartRozk32784(CCmdUI* pCmdUI);
	afx_msg void OnStartRysujtemperatury();
};

#ifndef _DEBUG  // debug version in MesTempView.cpp
inline CMesTempDoc* CMesTempView::GetDocument() const
   { return reinterpret_cast<CMesTempDoc*>(m_pDocument); }
#endif

