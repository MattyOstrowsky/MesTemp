
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
#include "Siatka.h"

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
	ON_COMMAND(ID_START_GENERUJSIATK32773, &CMesTempView::OnStartGeneruj)

	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_PRZYBLI32781, &CMesTempView::OnMenuPrzybli)
	ON_COMMAND(ID_MENU_ODDAL, &CMesTempView::OnMenuOddal)
	ON_COMMAND(ID_START_ZAG32777, &CMesTempView::OnStartZag32777)
	ON_COMMAND(ID_START_ROZK32784, &CMesTempView::OnStartRozk)
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
		CPen pen1(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* oldpen1 = pDC->SelectObject(&pen1);
		pDC->Rectangle(8, 10, 800, 600);
		CPen pen2(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* oldpen2 = pDC->SelectObject(&pen2);
		pDC->MoveTo(20, 20);
		pDC->LineTo(10, 20);
		pDC->LineTo(15, 15);
		pDC->LineTo(20, 20);
		pDC->MoveTo(15, 20);
		pDC->LineTo(15,590);
		pDC->LineTo(790, 590);
		pDC->MoveTo(790, 595);
		pDC->LineTo(790, 585);
		pDC->LineTo(795, 590);
		pDC->LineTo(790, 595);
		
		CString floatString;
		
		floatString = "skala:";
		pDC->TextOutW(960, 50, floatString);
		floatString = "liczba element�w:";
		pDC->TextOutW(960, 70, floatString);
		floatString.Format(_T("%f"), liczba_obszarow);
		pDC->TextOutW(1170, 70, floatString);
		floatString.Format(_T("%f"), skala);
		pDC->TextOutW(1170,50, floatString);
		floatString.Format(_T("%f"), yPos);
		pDC->TextOutW(1120, 20, floatString);
		floatString.Format(_T("%f"), xPos);
		pDC->TextOutW(1020, 20, floatString);
		

		CPen pen3(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* oldpen3 = pDC->SelectObject(&pen3);

		for (int i = 0; i < liczba_obszarow; i++)
		{
			if (wektor_obszarow[i].czy_prostokat) // dla prostokatow
			{
				//pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
				//pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
				if (600 > (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y1))
				{
					if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800>(xos0 + skala * wektor_obszarow[i].x4)&& (xos0 + skala * wektor_obszarow[i].x4) >8)
					{
						pDC->MoveTo(8, (yos0 - skala * wektor_obszarow[i].y1));
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
					}
					else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 < (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->MoveTo(8, (yos0 - skala * wektor_obszarow[i].y1));
						pDC->LineTo(800, (yos0 - skala * wektor_obszarow[i].y1));
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));

					}
					else if (8 < (xos0 + skala * wektor_obszarow[i].x1)&&(xos0 + skala * wektor_obszarow[i].x1)<800 && 800 > (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
					}
					else if (8 < (xos0 + skala * wektor_obszarow[i].x1)&& (xos0 + skala * wektor_obszarow[i].x1)<800 && 800 < (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
						pDC->LineTo(800, (yos0 - skala * wektor_obszarow[i].y1));
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));

					}
				}else
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
				}

				//pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));

				if (8 < (xos0 + skala * wektor_obszarow[i].x4) && 800 > (xos0 + skala * wektor_obszarow[i].x4))
				{
					if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10< (yos0 - skala * wektor_obszarow[i].y4)&& (yos0 - skala * wektor_obszarow[i].y4)<600)
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), 600);
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));
					}
					else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 > (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), 600);
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), 10);
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));

					}
					else if (600 > (yos0 - skala * wektor_obszarow[i].y1)&& (yos0 - skala * wektor_obszarow[i].y1)>10 && 10 > (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), 10);
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));
					}
					else if (600 > (yos0 - skala * wektor_obszarow[i].y1)&& (yos0 - skala * wektor_obszarow[i].y1) >10&& 10 < (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));

					}
				}
				else
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));
				}

				
				//pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1),  (yos0 - skala * wektor_obszarow[i].y4));
				if (600 > (yos0 - skala * wektor_obszarow[i].y4) && 10 < (yos0 - skala * wektor_obszarow[i].y4))
				{
					if (8 < (xos0 + skala * wektor_obszarow[i].x1)&&(xos0 + skala * wektor_obszarow[i].x1)<800 && 800 < (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->MoveTo(800, (yos0 - skala * wektor_obszarow[i].y4));
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));
					}
					else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 < (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->MoveTo(800, (yos0 - skala * wektor_obszarow[i].y4));
						pDC->LineTo(8, (yos0 - skala * wektor_obszarow[i].y4));
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));

					}
					else if (8 < (xos0 + skala * wektor_obszarow[i].x1) && 800 > (xos0 + skala * wektor_obszarow[i].x4))
					{
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));
					}
					else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 > (xos0 + skala * wektor_obszarow[i].x1)&& (xos0 + skala * wektor_obszarow[i].x1) >8)
					{
						
						pDC->LineTo(8, (yos0 - skala * wektor_obszarow[i].y4));
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));

					}
				}
				else
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));
				}
				
				//pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1),  (yos0 - skala * wektor_obszarow[i].y1));
				if (8 < (xos0 + skala * wektor_obszarow[i].x4) && 800 > (xos0 + skala * wektor_obszarow[i].x4))
				{
					if (600 > (xos0 + skala * wektor_obszarow[i].x1)&& (xos0 + skala * wektor_obszarow[i].x1)>10 && 10 > (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), 8);
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
					}
					else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 > (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), 10);
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), 600);
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));

					}
					else if (600 > (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y4))
					{
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
					}
					else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y4)&& (yos0 - skala * wektor_obszarow[i].y4)<600)
					{
						pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), 600);
						pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));

					}
				}
				else
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
				}
			}
			//else //dla nieprostokatow
			//{
			//	pDC->MoveTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
			//	pDC->LineTo(xos0 + wektor_obszarow[i].x2, yos0 - wektor_obszarow[i].y2);
			//	pDC->LineTo(xos0 + wektor_obszarow[i].x3, yos0 - wektor_obszarow[i].y3);
			//	pDC->LineTo(xos0 + wektor_obszarow[i].x4, yos0 - wektor_obszarow[i].y4);
			//	pDC->LineTo(xos0 + wektor_obszarow[i].x1, yos0 - wektor_obszarow[i].y1);
			//}
			
			
		}
		
	};

	if (RysSiatka)
	{
		CPen pen1(PS_SOLID, 1, RGB(50, 205, 50));
		CPen* oldpen = pDC->SelectObject(&pen1);

		Siatka siatka(wektor_obszarow);
		siatka.utworz_siatke(wektor_obszarow);
		
		for (int i = 0; i < siatka.kord_x.size(); i++)
		{
			pDC->MoveTo(xos0 + skala * siatka.kord_x[i], 10);
			pDC->LineTo(xos0 + skala * siatka.kord_x[i], 600);

		}
		for (int i = 0; i < siatka.kord_y.size() ; i++)
		{
			pDC->MoveTo(8,  yos0 - skala * siatka.kord_y[i]);
			pDC->LineTo(800,  yos0 - skala * siatka.kord_y[i]);
		}
		RysSiatka = false;
			if (ZagRysuj)
			{
				siatka.zageszczenie_prostokatow(zag_y, siatka.kord_y);
				siatka.zageszczenie_prostokatow(zag_x, siatka.kord_x);
				for (int i = 0; i < siatka.kord_x.size() ; i++)
				{
					pDC->MoveTo(xos0 + skala * siatka.kord_x[i], 10);
					pDC->LineTo(xos0 + skala * siatka.kord_x[i], 600);
					
				}
				
				for (int i = 0; i < siatka.kord_y.size(); i++)
				{
					pDC->MoveTo(8, yos0 - skala * siatka.kord_y[i]);
					pDC->LineTo( 800, yos0 - skala * siatka.kord_y[i] );
					
				}
				
			}
		

	}
	if (RozRysuj)
	{
		for (int i = 8; i < 800; i++)
		{
			for (int j = 10; j < 600; j++) 
			{
			
			}
		}
		pDC->SetPixel(900, 555, RGB(150, 105, 200));
	}
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
	

}


void CMesTempView::OnFileOpen()
{
	// TODO: Dodaj tutaj sw�j kod procedury obs�ugi polecenia
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


		std::fstream plik; //otworzenie pliku o danej nazwie
		plik.open(FilePathName, std::ios::in);

		if (plik.good())
		{

			plik >> liczba_obszarow;
			plik >> skala;

			for (int i = 0; i < liczba_obszarow; i++)
			{	
				Input obszar; //utworzenie obiektu obszar
				obszar.czytaj(plik);
				obszar.liczba_obszarow = liczba_obszarow;
				obszar.skala = skala;
				if (obszar.x4 > x_max)
					x_max = obszar.x4;
				if (obszar.y4 > y_max)
					y_max = obszar.y4;
				wektor_obszarow.push_back(obszar);
				
			}
			
		}
		while ((skala * x_max) > 800 || (skala * y_max) > 600) {
			skala -= 0.1;
		}
		skalaTrue = skala;

		//obszar.test(liczba_obszarow,wektor_obszarow,czy_pokrywa);
		Rysuj = true;
		Invalidate(TRUE);
		UpdateWindow();
		
	}
}


void CMesTempView::OnStartGeneruj()
{
	RysSiatka = true;
	Invalidate(TRUE);
	UpdateWindow();
}




void CMesTempView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Dodaj tutaj sw�j kod procedury obs�ugi komunikat�w i/lub wywo�aj domy�lny

	CView::OnLButtonUp(nFlags, point);
	
	yPos = yos00 - (int)point.y;
	xPos = (int)point.x - xos00;
	//yPos = (int)point.y;
	//xPos = (int)point.x ;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnMenuPrzybli()
{
	yos0 +=yPos -225;
	xos0 -=xPos -300;
	skala = skala * 1.25;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnMenuOddal()
{
	yos0 = 590;
	xos0 = 15;
	skala = skalaTrue;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnStartZag32777()
{
	DialZagesc dlgDialZagesc;
	dlgDialZagesc.DoModal();
	zag_x = dlgDialZagesc.zag_x;
	zag_y = dlgDialZagesc.zag_y;
	RysSiatka = true;
	ZagRysuj = true;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnStartRozk()
{
	RozRysuj = true;
	RysSiatka = true;
	Invalidate(TRUE);
	UpdateWindow();
}
