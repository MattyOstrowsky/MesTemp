
// MesTempView.cpp : implementation of the CMesTempView class
//

#define NOMINMAX

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
#include "licz.h"
#include "sstream"
#include "limits"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "error.h"


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
	ON_UPDATE_COMMAND_UI(ID_START_GENERUJSIATK32773, &CMesTempView::OnUpdateStartGeneruj)
	ON_UPDATE_COMMAND_UI(ID_START_ZAG32777, &CMesTempView::OnUpdateStartZag32777)
	ON_UPDATE_COMMAND_UI(ID_START_RYSUJTEMPERATURY, &CMesTempView::OnUpdateStartRysujtemperatury)
	ON_UPDATE_COMMAND_UI(ID_START_ROZK32784, &CMesTempView::OnUpdateStartRozk32784)
	ON_COMMAND(ID_START_RYSUJTEMPERATURY, &CMesTempView::OnStartRysujtemperatury)
	ON_COMMAND(ID_START_ZAPISZ32783, &CMesTempView::OnStartZapisz)
	ON_UPDATE_COMMAND_UI(ID_START_ZAPISZ32783, &CMesTempView::OnUpdateStartZapisz)
END_MESSAGE_MAP()

// CMesTempView construction/destruction

CMesTempView::CMesTempView() noexcept
{
	
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
		
	CString str;

	str = "";

	
	pDoc->SetTitle(str);
		
	
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
	pDC->LineTo(15, 590);
	pDC->LineTo(790, 590);
	pDC->MoveTo(790, 595);
	pDC->LineTo(790, 585);
	pDC->LineTo(795, 590);
	pDC->LineTo(790, 595);

	CString floatString;

	
	if (err == true)
	{
		error error;
		error.DoModal();
		err = false;
	}

	
	if (Rysuj) {
		
		 RysujObszary(pDC);
		 floatString = "skala:";
		 pDC->TextOutW(980, 50, floatString);
		 floatString = "liczba elementow:";
		 pDC->TextOutW(980, 70, floatString);
		 floatString.Format(_T("%.0f"), liczba_obszarow);
		 pDC->TextOutW(1170, 70, floatString);
		 floatString.Format(_T("%.1f"), skala);
		 pDC->TextOutW(1170, 50, floatString);
		 floatString.Format(_T(" Y [mm]:%.1f"), yPos);
		 pDC->TextOutW(1120, 20, floatString);
		 floatString.Format(_T(" X [mm]:%.1f"), xPos);
		 pDC->TextOutW(1020, 20, floatString);
		 for (float j = 0; j < liczba_obszarow; j++)
		 {
			 if ((xxpos-xos0 )<( skala * wektor_obszarow[j].x4) && ( skala * wektor_obszarow[j].x1) < (xxpos-xos0))
			 {
				 if ((yos0 -yypos) <( skala * wektor_obszarow[j].y4)  && ( skala * wektor_obszarow[j].y1)<(yos0- yypos))
				 {
				
					 floatString = "numer obszaru:";
					 pDC->TextOutW(980, 120, floatString);
					 floatString = "gestosc mocy [W/m^2]:";
					 pDC->TextOutW(980, 140, floatString);
					 floatString = "przewodnosc x [W/(m * K)]:";
					 pDC->TextOutW(980, 160, floatString);
					 floatString = "przewodnosc y [W/(m* K):";
					 pDC->TextOutW(980, 180, floatString);
					 floatString = "material:";
					 pDC->TextOutW(980, 200, floatString);

					 floatString.Format(_T("%.0f"), wektor_obszarow[j].nr);
					 pDC->TextOutW(1170, 120, floatString);
					 floatString.Format(_T("%.0f"), wektor_obszarow[j].moc_zrodla * pow(10, 6));
					 pDC->TextOutW(1170, 140, floatString);
					 floatString.Format(_T("%.0f"), wektor_obszarow[j].przewodnosc_x * 1000);
					 pDC->TextOutW(1170, 160, floatString);
					 floatString.Format(_T("%.0f"), wektor_obszarow[j].przewodnosc_y * 1000);
					 pDC->TextOutW(1170, 180, floatString);

					 pDC->TextOutW(1170, 200, CString(wektor_obszarow[j].material));
				 }
			 }
		 }

	};

	if (RysSiatka)
	{
		
		CPen pen1(PS_SOLID, 1, RGB(50, 205, 50));
		CPen* oldpen = pDC->SelectObject(&pen1);

		Siatka siatka(wektor_obszarow);
		siatka.utworz_siatke(wektor_obszarow);
		siatka.zageszczenie_prostokatow(zag_y, siatka.kord_y);
		siatka.zageszczenie_prostokatow(zag_x, siatka.kord_x);
		wsp_x.clear();
		wsp_y.clear();
		for (int i = 0; i < siatka.kord_x.size(); i++)
		{
			if (fabs(siatka.kord_x[i]) > 0.0000000001)wsp_x.push_back(siatka.kord_x[i]);
			else wsp_x.push_back(0);
		}
		for (int i = 0; i < siatka.kord_y.size(); i++)
		{
			if (fabs(siatka.kord_y[i]) > 0.0000000001)wsp_y.push_back(siatka.kord_y[i]);
			else wsp_y.push_back(0);
		}
		RozRysujU = true;
		
		for (int j = 0; j < liczba_obszarow; j++)
		{

				

			for (int k = 0; k < siatka.kord_y.size(); k++)
			{
				if (( siatka.kord_y[k]) >= ( wektor_obszarow[j].y1) &&(  siatka.kord_y[k]) <= ( wektor_obszarow[j].y4))
				{
					if ((yos0 - skala * siatka.kord_y[k])>8&&(yos0 - skala * siatka.kord_y[k])<590)
					{
						if ((xos0 + skala * wektor_obszarow[j].x1) < 15)
						{
							pDC->MoveTo(15, yos0 - skala * siatka.kord_y[k]);
							if ((xos0 + skala * wektor_obszarow[j].x4) < 800 &&(xos0 + skala * wektor_obszarow[j].x4) > 15)
							{
								pDC->LineTo(xos0 + skala * wektor_obszarow[j].x4, yos0 - skala * siatka.kord_y[k]);
							}
							else if ((xos0 + skala * wektor_obszarow[j].x4) > 800)
							{
								pDC->LineTo(800, yos0 - skala * siatka.kord_y[k]);
							}
						}
						else if ((xos0 + skala * wektor_obszarow[j].x1) > 8 && (xos0 + skala * wektor_obszarow[j].x1) <800)
						{
							pDC->MoveTo(xos0 + skala * wektor_obszarow[j].x1, yos0 - skala * siatka.kord_y[k]);
							if ((xos0 + skala * wektor_obszarow[j].x4) < 800)
							{
								pDC->LineTo(xos0 + skala * wektor_obszarow[j].x4, yos0 - skala * siatka.kord_y[k]);
							}
							else if ((xos0 + skala * wektor_obszarow[j].x4) > 800)
							{
								pDC->LineTo(800, yos0 - skala * siatka.kord_y[k]);
							}
						}
					}
				}
			}
			for (int k = 0; k < siatka.kord_x.size(); k++)
			{
				if (( siatka.kord_x[k]) >= ( wektor_obszarow[j].x1) && ( siatka.kord_x[k]) <= ( wektor_obszarow[j].x4))
				{
					if ((xos0 + skala * siatka.kord_x[k]) > 10 && (xos0 + skala * siatka.kord_x[k]) < 800)
					{
						if ((yos0 - skala * wektor_obszarow[j].y4) < 10)
						{
							pDC->MoveTo(xos0 + skala * siatka.kord_x[k], 10);
							if ((yos0 - skala * wektor_obszarow[j].y1) < 600&& (yos0 - skala * wektor_obszarow[j].y1) >10)
							{
								pDC->LineTo(xos0 + skala * siatka.kord_x[k], yos0 - skala * wektor_obszarow[j].y1);
							}
							else if ((yos0 - skala * wektor_obszarow[j].y1) > 600)
							{
								pDC->LineTo(xos0 + skala * siatka.kord_x[k], 590);
							}
						}
						else if ((yos0 - skala * wektor_obszarow[j].y4) > 10&&(yos0 - skala * wektor_obszarow[j].y4) < 600)
						{
							pDC->MoveTo(xos0 + skala * siatka.kord_x[k], yos0 - skala * wektor_obszarow[j].y4);
							if ((yos0 - skala * wektor_obszarow[j].y1) < 600)
							{
								pDC->LineTo(xos0 + skala * siatka.kord_x[k], yos0 - skala * wektor_obszarow[j].y1);
							}
							else if ((yos0 - skala * wektor_obszarow[j].y1) > 600)
							{
								pDC->LineTo(xos0 + skala * siatka.kord_x[k], 590);
							}
						}
					}
				}
			}		
		}
		
		if (RozRysuj)
		{
			TempRysujU = true;
			std::ofstream plik;
			plik.open("Testy.txt");
			plik << "Zaczynamy\n";
			licz licz;
			plik.close();
			licz.rozw(wynikRozw, siatka, wektor_obszarow, wektor_warunkow_brzegowych);
			int nr = 0;
			tempmax = wynikRozw[0];
			tempmin = wynikRozw[0];

			tablica = new float* [x_max];
			for (int i = 0; i < x_max; i++)
			{
				tablica[i] = new float[y_max];
			}


			for (int x = 0; x < x_max; x++)
			{
				for (int y = 0; y < y_max; y++)
				{
					tablica[x][y] = licz.temp(x, y, nr, wynikRozw, siatka);

					if (tablica[x][y] > tempmax)
						tempmax = tablica[x][y];
					if (tablica[x][y] < tempmin && tablica[x][y] > -300)
						tempmin = tablica[x][y];
				}
			}
			plik.open("Testy.txt", std::ofstream::app);
			plik << "\nTmax = " << tempmax << "  ;  Tmin = " << tempmin << "\n";
			RozRysuj = false;
		}
		if (TempRysuj)
		{
			//skala
			double jedn = (tempmax - tempmin) / 500.0;
			int tmp;
			floatString.Format(_T("%.2f"), tempmax);
			pDC->TextOutW(910, 50, floatString);
			floatString.Format(_T("%.2f"), tempmin);
			pDC->TextOutW(910, 550, floatString);
			for (int xx = 850; xx < 900; xx++)
			{
				double temper = tempmax;

				for (int yy = 50; yy < 550; yy++)
				{

					tmp = 255 * (temper - tempmin) / (tempmax - tempmin);
					int tt = tmp / 25;
					pDC->SetPixel(xx, yy, RGB(25 * tt, 20, 255 - 25 * tt));
					temper -= jedn;

				}
			}

			//rysowanie
			int nr = 0;
			float tempa;
			licz licz;
			int pomt=0;
			
			
			for (int i = 0; i < liczba_obszarow; i++)
			{
				
				for (int x =skala * wektor_obszarow[i].x1; x < skala * wektor_obszarow[i].x4; x++)
				{
					

					for (int y = skala * wektor_obszarow[i].y1; y <  skala * wektor_obszarow[i].y4; y++)
					{
						pomt=licz.temp(x/skala, y/skala, nr, wynikRozw, siatka);
						
						if (pomt > -300)
						{
							
							pomt = 255 * (pomt - tempmin) / (tempmax - tempmin);
							int tt = pomt / 25;
							if ((xos0 + x) < 800 &&( xos0 + x )> 15)
							{
								if ((yos0 - y) < 590 && (yos0 - y )>8)
									pDC->SetPixel(xos0+x, yos0-y, RGB(25 * tt, 20, 255 - 25 * tt));

							}
						}
						
					}
				}
			}

			
			RysujObszary(pDC);
		}
		
		
			
			
			
		
		
		
		

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
	TCHAR szFilters[] = _T("txt Type Files (*.txt)|*.txt||");
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
			
			std::string ignorowanalinia; //linia - smietnik
			getline(plik, ignorowanalinia); //ignorowanie linii z oznaczeniami. Dalej tez tak samo

			plik >> liczba_obszarow;

			getline(plik, ignorowanalinia);
			getline(plik, ignorowanalinia);

			plik >> skala;

			getline(plik, ignorowanalinia);
			getline(plik, ignorowanalinia);

			for (int i = 0; i < liczba_obszarow; i++)
			{	
				Input obszar; //utworzenie obiektu obszar
				obszar.czytaj(plik); //uzupelnienie wlasciwosci obszaru
				obszar.liczba_obszarow = liczba_obszarow;
				obszar.skala = skala;
				if (obszar.x4 > x_max) //znalezienie max i min wspolrzednych obszarow
					x_max = obszar.x4;
				if (obszar.y4 > y_max)
					y_max = obszar.y4;
				obszar.moc_zrodla *= pow(10, -6);
				obszar.przewodnosc_x *= pow(10, -3);
				obszar.przewodnosc_y *= pow(10, -3);
				wektor_obszarow.push_back(obszar); //dodanie obszaru do wektora obszarow
				
			}
			getline(plik, ignorowanalinia);
			getline(plik, ignorowanalinia);

			int ile_warunkow_brzegowych;

			plik >> ile_warunkow_brzegowych;

			getline(plik, ignorowanalinia);
			getline(plik, ignorowanalinia);

			for (int i = 0; i < ile_warunkow_brzegowych; i++)
			{
				WarunkiBrzegowe warunek; //utworzenie obiektu - warunek brzegowy
				warunek.czytaj(plik);
				wektor_warunkow_brzegowych.push_back(warunek);
			}
			
		}
		while ((skala * x_max) > 800 || (skala * y_max) > 600) {
			skala -= 0.1;
		}
		skalaTrue = skala;

		//obszar.test(liczba_obszarow,wektor_obszarow,czy_pokrywa);
		Rysuj = true;
		RysSiatka = false;
		RysSiatkaU = true;
		zag_x = 1;
		zag_y = 1;
		//sprawdzanie opszarów
		for (int i = 0; i < liczba_obszarow; i++)
		{
			for (int j = 0; j < liczba_obszarow; j++)
			{
				if (wektor_obszarow[i].x1 < wektor_obszarow[j].x1 && wektor_obszarow[i].x4 > wektor_obszarow[j].x1)
				{
					if (wektor_obszarow[i].y1 < wektor_obszarow[j].y1 && wektor_obszarow[i].y4 > wektor_obszarow[j].y1) {
						err = true;
						Rysuj = false;
					}
					
				}
				else if (wektor_obszarow[i].x1 < wektor_obszarow[j].x4 && wektor_obszarow[i].x4 > wektor_obszarow[j].x4 )
				{
					if (wektor_obszarow[i].y1 < wektor_obszarow[j].y1 && wektor_obszarow[i].y4 > wektor_obszarow[j].y1) {
						err = true;
						Rysuj = false;
					}
				}
				else if (wektor_obszarow[i].x1 < wektor_obszarow[j].x1 && wektor_obszarow[i].x4 > wektor_obszarow[j].x1 )
				{
					if (wektor_obszarow[i].y4 < wektor_obszarow[j].y1 && wektor_obszarow[i].y4 > wektor_obszarow[j].y4) {
						err = true;
						Rysuj = false;
					}
				}
				else if (wektor_obszarow[i].x1 < wektor_obszarow[j].x4 && wektor_obszarow[i].x4 > wektor_obszarow[j].x4 )
				{
					if (wektor_obszarow[i].y4 < wektor_obszarow[j].y1 && wektor_obszarow[i].y4 > wektor_obszarow[j].y4) {
						err = true;
						Rysuj = false;
					}
				}
				
			}


		}
		Invalidate(TRUE);
		UpdateWindow();
		
	}
}


void CMesTempView::OnStartGeneruj()
{
	Rysuj = true;
	RysSiatka = true;
	RozRysuj = false;
	Invalidate(TRUE);
	UpdateWindow();
}




void CMesTempView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Dodaj tutaj sw�j kod procedury obs�ugi komunikat�w i/lub wywo�aj domy�lny

	CView::OnLButtonUp(nFlags, point);
	yypos = (int)point.y;
	xxpos = (int)point.x;
	yPos = yos00 - (int)point.y;
	xPos = (int)point.x - xos00;
	//yPos = (int)point.y;
	//xPos = (int)point.x ;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnMenuPrzybli()
{
	yos0 +=yPos -120;
	xos0 -=xPos -160;
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
	Rysuj = true;
	RysSiatka = true;
	RozRysuj = false;
	Invalidate(TRUE);
	UpdateWindow();
}


void CMesTempView::OnStartRozk()
{
	Rysuj = true;
	RozRysuj = true;
	RysSiatka = true;
	Invalidate(TRUE);
	UpdateWindow();
}
void CMesTempView::RysujObszary(CDC* pDC)
{
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
				if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 > (xos0 + skala * wektor_obszarow[i].x4) && (xos0 + skala * wektor_obszarow[i].x4) > 8)
				{
					pDC->MoveTo(15, (yos0 - skala * wektor_obszarow[i].y1));
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
				}
				else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 < (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->MoveTo(15, (yos0 - skala * wektor_obszarow[i].y1));
					pDC->LineTo(800, (yos0 - skala * wektor_obszarow[i].y1));
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));

				}
				else if (8 < (xos0 + skala * wektor_obszarow[i].x1) && (xos0 + skala * wektor_obszarow[i].x1) < 800 && 800 > (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
				}
				else if (8 < (xos0 + skala * wektor_obszarow[i].x1) && (xos0 + skala * wektor_obszarow[i].x1) < 800 && 800 < (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
					pDC->LineTo(800, (yos0 - skala * wektor_obszarow[i].y1));
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));

				}
			}
			else
			{
				pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y1));
			}

			//pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));

			if (8 < (xos0 + skala * wektor_obszarow[i].x4) && 800 > (xos0 + skala * wektor_obszarow[i].x4))
			{
				if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y4) && (yos0 - skala * wektor_obszarow[i].y4) < 600)
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), 590);
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));
				}
				else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 > (yos0 - skala * wektor_obszarow[i].y4))
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), 590);
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), 10);
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));

				}
				else if (600 > (yos0 - skala * wektor_obszarow[i].y1) && (yos0 - skala * wektor_obszarow[i].y1) > 10 && 10 > (yos0 - skala * wektor_obszarow[i].y4))
				{
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x4), 10);
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x4), (yos0 - skala * wektor_obszarow[i].y4));
				}
				else if (600 > (yos0 - skala * wektor_obszarow[i].y1) && (yos0 - skala * wektor_obszarow[i].y1) > 10 && 10 < (yos0 - skala * wektor_obszarow[i].y4))
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
				if (8 < (xos0 + skala * wektor_obszarow[i].x1) && (xos0 + skala * wektor_obszarow[i].x1) < 800 && 800 < (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->MoveTo(800, (yos0 - skala * wektor_obszarow[i].y4));
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));
				}
				else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 < (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->MoveTo(800, (yos0 - skala * wektor_obszarow[i].y4));
					pDC->LineTo(15, (yos0 - skala * wektor_obszarow[i].y4));
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));

				}
				else if (8 < (xos0 + skala * wektor_obszarow[i].x1) && 800 > (xos0 + skala * wektor_obszarow[i].x4))
				{
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y4));
				}
				else if (8 > (xos0 + skala * wektor_obszarow[i].x1) && 800 > (xos0 + skala * wektor_obszarow[i].x4) && (xos0 + skala * wektor_obszarow[i].x4) > 8)
				{

					pDC->LineTo(15, (yos0 - skala * wektor_obszarow[i].y4));
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
				if (600 > (xos0 + skala * wektor_obszarow[i].x1) && (xos0 + skala * wektor_obszarow[i].x1) > 10 && 10 > (yos0 - skala * wektor_obszarow[i].y4))
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), 10);
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
				}
				else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 > (yos0 - skala * wektor_obszarow[i].y4))
				{
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), 8);
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), 590);
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));

				}
				else if (600 > (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y4))
				{
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
				}
				else if (600 < (yos0 - skala * wektor_obszarow[i].y1) && 10 < (yos0 - skala * wektor_obszarow[i].y4) && (yos0 - skala * wektor_obszarow[i].y4) < 600)
				{
					pDC->LineTo((xos0 + skala * wektor_obszarow[i].x1), 590);
					pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));

				}
			}
			else
			{
				pDC->MoveTo((xos0 + skala * wektor_obszarow[i].x1), (yos0 - skala * wektor_obszarow[i].y1));
			}
		}
	

	}
}


void CMesTempView::OnUpdateStartGeneruj(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(RysSiatkaU);
}


void CMesTempView::OnUpdateStartZag32777(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(RysSiatkaU);
}


void CMesTempView::OnUpdateStartRysujtemperatury(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TempRysujU);
}


void CMesTempView::OnUpdateStartRozk32784(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(RozRysujU);

}


void CMesTempView::OnStartRysujtemperatury()
{
	RysSiatka = true;
	RozRysuj = false;
	TempRysuj = true;
	Invalidate(TRUE);
	UpdateWindow();
	ZapiszU = true;
}

void CMesTempView::OnUpdateStartZapisz(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(ZapiszU);
}


void CMesTempView::OnStartZapisz()
{
	CFile newfile;
	TCHAR szFilters[] = _T("txt Type Files (*.txt)|*.txt||");
	CFileDialog fileDlg(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY , szFilters);
	if (fileDlg.DoModal() == IDOK)
	{
		
		FilePathName = fileDlg.GetPathName();

		std::ofstream plik; //otworzenie pliku o danej nazwie
		licz pom1;
		int ob=0;
		bool b = true;
		std::vector<int>max;
		std::vector<int> min;	//numery węzłów zawierających skrajne temperatury
		//plik.open(FilePathName, std::ios::in);
		plik.open(FilePathName);
		plik << "Wyniki dla " << liczba_obszarow << " obszarów materiałowych, podzielonych na siatkę o " << wynikRozw.size();
		plik << " węzłach ( " <<wsp_x.size() << " w osi X i " << wsp_y.size() << " w osi Y):\n";
		tempmin = wynikRozw[0];
		tempmax = wynikRozw[0];
		for (int i = 1; i < wynikRozw.size(); i++)
		{
			if (wynikRozw[i] < tempmin)tempmin = wynikRozw[i];
			if (wynikRozw[i] > tempmax)tempmax = wynikRozw[i];
		}
		for (int i = 0; i < wynikRozw.size(); i++)
		{
			pom1.ktory_obszar(wsp_x[i%wsp_x.size()], wsp_y[i/wsp_x.size()], ob, b, wektor_obszarow);
			plik << std::setw(8) << "\nNr węzła" << "|" << std::setw(10) << "X[mm]" << "|" << std::setw(10) << "Y[mm]" << "|";
			plik << std::setw(14) << "Temperatura[K]" << "|" << std::setw(10) << "Nr obszaru" << "|" << std::setw(22) << "Przewodność X[W/(m*K)]" << "|" << std::setw(22) << "Przewodność Y[W/(m*K)]" << "|" << std::setw(17) << "Moc źródła[W/m^2]\n";
			plik << std::setw(8) << i << "|" << std::setw(10) << wsp_x[i% wsp_x.size()] << "|" << std::setw(10) << wsp_y[i/ wsp_x.size()] << "|";
			plik << std::setw(14) << wynikRozw[i] << "|" << std::setw(10) << ob << "|" << std::setw(22) << wektor_obszarow[ob].przewodnosc_x * 1000 << "|" << std::setw(22) << wektor_obszarow[ob].przewodnosc_y * 1000 << "|" << std::setw(17) << wektor_obszarow[ob].moc_zrodla * pow(10, 6) << "\n";
			if (fabs(wynikRozw[i] - tempmax)<0.0000001)max.push_back(i);
			if (fabs(wynikRozw[i] - tempmin)<0.0000001)min.push_back(i);
		}
		plik << "\nTemperatura maksymalna [K]: " << tempmax << ". Wystąpiła dla węzłów nr: ";
		if (max.size() > 0)
		{
			for (int i = 0; i < max.size() - 1; i++)
			{
				plik << max[i] << ", ";
			}
			plik << max[max.size() - 1] << ".";
		}
		plik << "\nTemperatura minimalna [K]: " << tempmin << ". Wystąpiła dla węzłów nr: ";
		if (min.size() > 0)
		{
			for (int i = 0; i < min.size() - 1; i++)
			{
				plik << min[i] << ", ";
			}
			plik << min[min.size() - 1] << ".";
		}
		plik.close();
	}
}


