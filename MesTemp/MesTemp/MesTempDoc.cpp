
// MesTempDoc.cpp : implementation of the CMesTempDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MesTemp.h"
#endif

#include "MesTempDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMesTempDoc

IMPLEMENT_DYNCREATE(CMesTempDoc, CDocument)

BEGIN_MESSAGE_MAP(CMesTempDoc, CDocument)
END_MESSAGE_MAP()


// CMesTempDoc construction/destruction

CMesTempDoc::CMesTempDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMesTempDoc::~CMesTempDoc()
{
}

BOOL CMesTempDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMesTempDoc serialization

void CMesTempDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMesTempDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMesTempDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMesTempDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMesTempDoc diagnostics

#ifdef _DEBUG
void CMesTempDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMesTempDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMesTempDoc commands

//funkcja podaj¹ca wspó³rzêdne globalne na podstawie wspó³rzêdnych lokalnych w danym elemencie
//Xp,Yp- wspó³rzêdne podstawowe; Xw, Yw- wynik (wspó³rzêdne globalne)
void CMesTempDoc::z_podstawowego(Element e, float Xp, float Yp, float* Xw, float* Yw)
{
	float N1, N2, N3, N4;
	N1 = 0.25 * (1 - Xp) * (1 - Yp);
	N2 = 0.25 * (1 + Xp) * (1 - Yp);
	N3 = 0.25 * (1 + Xp) * (1 + Yp);
	N4 = 0.25 * (1 - Xp) * (1 + Yp);
	*Xw = N1 * e.x1 + N2 * e.x2 + N3 * e.x3 + N4 * e.x4;
	*Yw = N1 * e.y1 + N2 * e.y2 + N3 * e.y3 + N4 * e.y4;
}
