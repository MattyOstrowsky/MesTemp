
// MesTempDoc.h : interface of the CMesTempDoc class
//

#pragma once
#include "Element.h"

class CMesTempDoc : public CDocument
{
protected: // create from serialization only
	CMesTempDoc() noexcept;
	DECLARE_DYNCREATE(CMesTempDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMesTempDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void z_podstawowego(Element e, float Xp, float Yp, float* Xw, float* Yw);
};
