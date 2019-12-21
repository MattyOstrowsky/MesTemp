
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
	bool ZagRysuj= false;
	bool Rysuj = false;
	CString FilePathName;
	int liczba_obszarow;
	float skala=1;
	int zag_y, zag_x;
	float yos0 = 590;
	float xos0 = 15;
	bool czy_pokrywa = false;
	bool RysSiatka = false;
	float x_max = 0;
	float y_max = 0;



	
// Operations
public:
	std::vector <Input> wektor_obszarow;
	

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

};

#ifndef _DEBUG  // debug version in MesTempView.cpp
inline CMesTempDoc* CMesTempView::GetDocument() const
   { return reinterpret_cast<CMesTempDoc*>(m_pDocument); }
#endif

