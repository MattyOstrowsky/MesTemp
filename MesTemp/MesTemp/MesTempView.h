
// MesTempView.h : interface of the CMesTempView class
//

#pragma once


class CMesTempView : public CView
{
protected: // create from serialization only
	CMesTempView() noexcept;
	DECLARE_DYNCREATE(CMesTempView)

// Attributes
public:
	CMesTempDoc* GetDocument() const;
	bool StRysuj= false;
	CString FilePathName;

	
// Operations
public:
	Input* x = new Input();
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
};

#ifndef _DEBUG  // debug version in MesTempView.cpp
inline CMesTempDoc* CMesTempView::GetDocument() const
   { return reinterpret_cast<CMesTempDoc*>(m_pDocument); }
#endif

