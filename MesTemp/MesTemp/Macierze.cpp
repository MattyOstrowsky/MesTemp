#include "pch.h"
#include "Macierze.h"
#include <fstream>
#include <iomanip>

//konstruktor. Do uzupe³nienia
Macierze::Macierze(std::vector<float>& danea, std::vector<int>& danep, std::vector<int>& danec)
{
	A = danea;
	prow = danep;
	coln = danec;
}
//rozwi¹zywanie uk³adu równañ, metoda gradientów sprzê¿onych
void Macierze::licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik)
{
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	int ile = Q.size();
	plik << "\nWeszlo do funkcji. ile = " << ile << "\n";
	int petle = 0;			//dla zorientowania siê
	double r2, pom, pom2, pom3, a, b;
	//r2- odleg³oœæ^2 od minimum, a-alfa-d³ugoœæ kroku, p-kierunek poszukiwañ, b-beta-wspó³czynnik liniowy uwzglêdniaj¹cy stary kierunek
	double* r = new double[ile];
	double* rs = new double[ile];
	double* p = new double[ile];
	double* ps = new double[ile];
	for (int i = 0; i < ile; i++)
	{
		r[i] = Q[i];
		p[i] = Q[i];
		wynik.push_back(0);
	}
	do
	{
		r2 = 0;
		pom = 0;
		pom3 = 0;
		for (int i = 0; i < ile; i++)
		{
			pom3 += r[i] * r[i];
			pom2 = 0;
			for (int j = K.prow[i]; j < K.prow[i+1]; j++)
			{
				pom2 += p[K.coln[j]] * K.A[j];
			}
			pom += p[i] * pom2;
		}
		a = pom3 / pom;	//alfa_k = r_kT*r_k/p_kT*A*p_k
		for (int i = 0; i < ile; i++)
		{
			wynik[i] += p[i] * a;	//x_k+1 = x_k + alfa_k*Ap_k
			rs[i] = r[i];
			pom = 0;
			for (int j = K.prow[i]; j < K.prow[i + 1]; j++)
			{
				pom += K.A[j] * p[K.coln[j]];
			}
			r[i] -= a * pom;
			//r[i] -= alfa[k] * (A[i][0] * p[0] + A[i][1] * p[1] + A[i][2] * p[2] + A[i][3] * p[3]);	//r_k+1 = r_k - alfa_k*Ap_k
		}
		pom = 0;
		pom2 = 0;
		for (int i = 0; i < ile; i++)
		{
			pom += r[i] * r[i];
			pom2 += rs[i] * rs[i];
		}
		b = pom/pom2;
		//beta_k+1 = rT_k+1r_k+1/rT_kr_k
		for (int i = 0; i < ile; i++)
		{
			ps[i] = p[i];
			p[i] = ps[i] * b + r[i];	//p_k+1 = r_k+1 + beta_k+1p_k
			r2 += r[i] * r[i];
		}
		petle++;
	} while (r2 > 0.0000000001);
	plik << "\nWyszlo z petli iteracyjnej po " << petle << " obrotach\n";
	plik.close();
}

void Macierze::do_globalnej(Macierze& globalna, float co, int gdziex, int gdziey)
{
	bool czy = true;	//zmienna logiczna- czy trzeba twozyæ nowy element macierzy globalnej (zapisywanej jako 3 wektory)?
	int pop = 0;	//indeks elementu tablicy A macierzy globalnej, po którym nale¿y wstawiæ nowy
	std::vector<float>::iterator it;
	std::vector<int>::iterator it2;
	if (globalna.prow.size() > gdziey)
	{
		for (int k = globalna.prow[gdziey] - 1; k < globalna.prow[gdziey + 1]; k++)	//szuka, czy istnieje ju¿ niepusty element maierzy globalnej o takich indeksach
		{
			if (k < 0)k = 0;
			if (globalna.coln[k] == gdziex && k >= globalna.prow[gdziey])
			{
				globalna.A[k] += co;
				czy = false;
			}
			if (k == globalna.prow[gdziey] - 1) pop = k;
			if (globalna.coln[k] < gdziex) pop = k;
		}
	}
	if (czy)
	{
		it = globalna.A.begin();
		globalna.A.insert(it + pop + 1, co);	//dodawanie elementu do A
		it2 = globalna.coln.begin();
		globalna.coln.insert(it2 + pop + 1, gdziex);	//dodawanie elementu do coln
		for (int q = gdziey + 1; q < globalna.prow.size(); q++)
		{
			globalna.prow[q] += 1;				//zwiêkszanie o 1 indeksów pierwszych niezerowych wyrazów w ka¿dym wierszu poni¿ej dodanego
		}
	}
}

// funkcja dodaj¹ca macierz lokaln¹ do globalnej
void Macierze::do_globalnej2(Macierze& globalna, float lokalna[][4], float lokp[4],std::vector <float>& P, int wspolrzedne[4])
{
	/*std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	plik << "-----------\ndo globalnej\n";*/
	bool czy;	//zmienna logiczna- czy trzeba twozyæ nowy element macierzy globalnej (zapisywanej jako 3 wektory)?
	int pop = 0;	//indeks elementu tablicy A macierzy globalnej, po którym nale¿y wstawiæ nowy
	std::vector<float>::iterator it;
	std::vector<int>::iterator it2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			czy = true;
			if (lokalna[i][j] != 0)
			{
				globalna.do_globalnej(globalna, lokalna[i][j], wspolrzedne[j], wspolrzedne[i]);
			}
		}
		P[wspolrzedne[i]] += lokp[i];
		//plik << "P_glob " << wspolrzedne[i] << " = " << P[wspolrzedne[i]] << "\n";
	}
	/*plik << "------------------------\n";
	plik.close();*/
}


void Macierze:: pisz(std::string nazwa,Macierze M2, int ile)
{
	std::ofstream wyj;
	wyj.open(nazwa,std::ofstream::app);
	int pom = 0;
	for (int i = 0; i < ile; i++)
	{
		for (int j = 0; j < ile; j++)
		{
			if (M2.coln.size()>pom && M2.coln[pom] == j)
			{
				wyj <<std::setw(8)<< M2.A[pom];
				pom++;
			}
			else wyj << std::setw(8) << "0";
			wyj << " | ";
		}
		wyj << std::endl;
	}
	wyj.close();
}


// funkcja dodaj¹ca warunki brzegowe (I rodzaju)
void Macierze::brzegowe (Macierze& M, Siatka S, std::vector <float>& P, std::vector <class WarunkiBrzegowe> brzeg)
{
	int szuk, pom, nx, ny;
	bool czy;
	float d = 0.00000001;	//do porównywania floatów
	std::vector<int> wezly;	//numery wêz³ów, na które wp³ywa warunek brzegowy;
	for (int i = 0; i < brzeg.size(); i++)
	{
		wezly.clear();
		czy = true;
		pom = 0;
		while (czy)	//pêtla zape³niaj¹ca wektor wezly dla jednego warunku brzegowego
		{
			ny = pom / S.kord_x.size();
			nx = pom % S.kord_x.size();
			if (S.kord_x[nx] >= brzeg[i].x1 && S.kord_x[nx]  <= brzeg[i].x2 && S.kord_y[ny] >= brzeg[i].y1 && S.kord_y[ny] <= brzeg[i].y2)
			{
				wezly.push_back(pom);
			}
			if ((S.kord_x[nx] >= brzeg[i].x2 && S.kord_y[ny] >= brzeg[i].y2) ||(ny == S.kord_y.size()-1 && nx == S.kord_x.size()-1))
			//if (ny == S.kord_y.size() - 1 && nx == S.kord_x.size() - 1)
			{
				czy = false;
			}
			pom++;
		}
		for (int j = 0; j < wezly.size(); j++)
		{
			float pomK;
			//M.do_globalnej(M, brzeg[i].temperatura, wezly[j], wezly[j]);
			for (int k = M.prow[wezly[j]]; k < M.prow[wezly[j] + 1]; k++)
			{
				if (M.coln[k] == wezly[j])
				{
					M.A[k] = M.A[k]*10000000000;
					pomK = M.A[k];
					P[wezly[j]] = pomK * brzeg[i].temperatura;
				}
			}
		}
	}
}
