
// MesTempView.cpp : implementation of the CMesTempView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MesTemp.h"
#endif

#include "MesTempDoc.h"
#include "MesTempView.h"
#include "DialZagesc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMesTempView

IMPLEMENT_DYNCREATE(CMesTempView, CView)

BEGIN_MESSAGE_MAP(CMesTempView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_START_ZAG32772, &CMesTempView::OnStartZag)
	ON_COMMAND(ID_FILE_OPEN, &CMesTempView::OnFileOpen)
END_MESSAGE_MAP()

// CMesTempView construction/destruction

CMesTempView::CMesTempView() noexcept
{
	// TODO: add construction code here

}

CMesTempView::~CMesTempView()
{
}

BOOL CMesTempView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMesTempView drawing

void CMesTempView::OnDraw(CDC * pDC)
{

	
	CMesTempDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (Rysuj) {
		pDC->MoveTo(20, 20);
		pDC->LineTo(10, 20);
		pDC->LineTo(15, 15);
		pDC->LineTo(20, 20);
		pDC->MoveTo(15, 20);
		pDC->LineTo(xos0,yos0);
		pDC->LineTo(400, 550);
		pDC->MoveTo(400, 555);
		pDC->LineTo(400, 545);
		pDC->LineTo(405, 550);
		pDC->LineTo(400, 555);


		for (int i = 0; i < liczba_obszarow; i++)
		{
			if (wektor_obszarow[i].czy_prostokat) // dla prostokatow
			{
				pDC->MoveTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
				pDC->LineTo(xos0 + wektor_obszarow[i].x4, yos0 - wektor_obszarow[i].y1);
				pDC->LineTo(xos0 + wektor_obszarow[i].x4, yos0 - wektor_obszarow[i].y4);
				pDC->LineTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y4);
				pDC->LineTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
			}
			else //dla nieprostokatow
			{
				pDC->MoveTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
				pDC->LineTo(xos0 + wektor_obszarow[i].x2, yos0 - wektor_obszarow[i].y2);
				pDC->LineTo(xos0 + wektor_obszarow[i].x3, yos0 - wektor_obszarow[i].y3);
				pDC->LineTo(xos0 + wektor_obszarow[i].x4, yos0 - wektor_obszarow[i].y4);
				pDC->LineTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
			}
			
			
		}
		
	};
	// TODO: add draw code for native data here
	
}


// CMesTempView printing

BOOL CMesTempView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMesTempView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMesTempView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMesTempView diagnostics

#ifdef _DEBUG
void CMesTempView::AssertValid() const
{
	CView::AssertValid();
}

void CMesTempView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMesTempDoc* CMesTempView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMesTempDoc)));
	return (CMesTempDoc*)m_pDocument;
}
#endif //_DEBUG


// CMesTempView message handlers


void CMesTempView::OnStartZag()
{
	//DialZagesc dlgDialZagesc;
	//dlgDialZagesc.DoModal();
	ZagRysuj = true;
	Invalidate(TRUE);
	UpdateWindow();

}


void CMesTempView::OnFileOpen()
{
	// TODO: Dodaj tutaj swój kod procedury obs³ugi polecenia
	CFile newfile;
	TCHAR szFilters[] = _T("txt Type Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilters);
	if (fileDlg.DoModal() == IDOK)
	{
		CFile oldFile;
		ASSERT(oldFile != NULL);
		oldFile.Open(fileDlg.GetPathName(), CFile::modeRead | CFile::shareExclusive);
		FilePathName = fileDlg.GetPathName();
		CArchive loadArchive(&oldFile, CArchive::load | CArchive::bNoFlushOnDelete); // Create the archive to load data, the archive must be closed manually after the loading process      
		Serialize(loadArchive);
		loadArchive.Close();
		oldFile.Close();


		

		std::ifstream plik(FilePathName); //otworzenie pliku o danej nazwie

		if (!plik)
		{
			std::cout << "Plik nie moze byc otwarty.\n";
		}
		else
		{

			plik >> liczba_obszarow;
			plik >> skala;

			for (int i = 0; i < liczba_obszarow; i++)
			{
				Input obszar; //utworzenie obiektu obszar
				obszar.czytaj(plik);
				wektor_obszarow.push_back(obszar);
			}

			plik.close();
		}

		Rysuj = true;
		Invalidate(TRUE);
		UpdateWindow();
	}
}
