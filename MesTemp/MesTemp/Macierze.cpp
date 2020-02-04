#include "pch.h"
#include "Macierze.h"
#include <fstream>
#include <iomanip>

//konstruktor. Do uzupe�nienia
Macierze::Macierze(std::vector<float>& danea, std::vector<int>& danep, std::vector<int>& danec)
{
	A = danea;
	prow = danep;
	coln = danec;
}
//rozwi�zywanie uk�adu r�wna�, metoda iteracyjna
void Macierze::licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik)
{
	/*std::vector<int>brzegowe;	//wektor indeks�w warunk�w brzegowych (coby ich nie zmienia�)
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	int ile = Q.size();
	plik << "\nWeszlo do funkcji. ile = " << ile << "\n";
	//plik.close();
	int petle = 0;			//dla zorientowania si�
	//plik.open("Testy.txt", std::ofstream::app);
	float pom;
	std::vector<int> ii;	//indeksy element�w na g��wnej przek�tnej
	float* stare = new float[ile];	//poprzednie wyniki, potrzebne by sprawdzi� kiedy sko�czy� iteracj�
	bool czy;
	int pom2;
	bool czy2;
	for (int i = 0; i < ile; i++)
	{
		if (wynik[i] != 0)brzegowe.push_back(i);
	}
	//plik << "\n\nkolejne elementy wektora ii:\n";
	//plik.close();
	//plik.open("Testy.txt", std::ofstream::app);
	for (int i = 0; i < ile; i++)	//wype�niamiy ii
	{
		//wynik[i] = Q[i];
		pom2 = K.prow[i];
		while (i != K.coln[pom2])pom2++;
		ii.push_back(pom2);
		//plik << ii[i] << " ; ";
		//plik.close();
		//plik.open("Testy.txt", std::ofstream::app);
	}
	//plik << "\nprzeszlo, wchodzi do petli 'do'\n";
	//plik.close();
	//plik.open("Testy.txt", std::ofstream::app);
	do
	{
		petle++;
		//plik << "kolejny obrot do\n";
		//plik.close();
		//plik.open("Testy.txt", std::ofstream::app);
		czy = false;
		for (int i = 0; i < ile; i++)
		{
			stare[i] = wynik[i];	//przepisuje poprzednie wyniki do tablicy pomocniczej
		}
		//plik << "przepislo stare wyniki:\n";
		//plik.close();
		//plik.open("Testy.txt", std::ofstream::app);
		for (int i = 0; i < ile; i++)
		{
			czy2 = true;
			/*for (int j = 0; j < brzegowe.size(); j++)
			{
				if (i == brzegowe[j]) czy2 = false;
			}
			//plik << "stary: " << stare[i];
			//plik.close();
			//plik.open("Testy.txt", std::ofstream::app);
			if (czy2)
			{
				pom = Q[i];
				for (int j = K.prow[i]; j < K.prow[i + 1]; j++)	//mno�enie macierzy przez wektor tylko dla niezerowych element�w
				{
					pom -= K.A[j] * stare[K.coln[j]];
				}
				pom += K.A[ii[i]] * stare[i];
				//plik << "pom = " << pom;
				wynik[i] = pom / K.A[ii[i]];
				//plik << " ; nowy: " << wynik[i] << "\n";
				//plik.close();
				//plik.open("Testy.txt", std::ofstream::app);
				if ((fabs((wynik[i] - stare[i]) / stare[i])) > 0.05) czy = true;	//przyr�wnanie wzgl�dnej zmiany wyniku do zadanej dok�adno�ci
			}
		}
	} while (czy);*/
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	int ile = Q.size();
	plik << "\nWeszlo do funkcji. ile = " << ile << "\n";
	int petle = 0;			//dla zorientowania si�
	double r2, pom, pom2, pom3, a, b;
	double* r = new double[ile];
	double* rs = new double[ile];
	double* p = new double[ile];
	double* ps = new double[ile];
	for (int i = 0; i < ile; i++)
	{
		r[i] = Q[i];
		p[i] = Q[i];
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
	} while (r2 > 0.00000001);
	plik << "\nWyszlo z petli iteracyjnej po " << petle << " obrotach\n";
	plik.close();
}

void Macierze::do_globalnej(Macierze& globalna, float co, int gdziex, int gdziey)
{
	bool czy = true;	//zmienna logiczna- czy trzeba twozy� nowy element macierzy globalnej (zapisywanej jako 3 wektory)?
	int pop = 0;	//indeks elementu tablicy A macierzy globalnej, po kt�rym nale�y wstawi� nowy
	std::vector<float>::iterator it;
	std::vector<int>::iterator it2;
	if (globalna.prow.size() > gdziey)
	{
		for (int k = globalna.prow[gdziey] - 1; k < globalna.prow[gdziey + 1]; k++)	//szuka, czy istnieje ju� niepusty element maierzy globalnej o takich indeksach
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
			globalna.prow[q] += 1;				//zwi�kszanie o 1 indeks�w pierwszych niezerowych wyraz�w w ka�dym wierszu poni�ej dodanego
		}
	}
}

// funkcja dodaj�ca macierz lokaln� do globalnej
void Macierze::do_globalnej(Macierze& globalna, float lokalna[][4], float lokp[4],std::vector <float>& P, int wspolrzedne[4])
{
	std::ofstream plik;
	//plik.open("Testy.txt", std::ofstream::app);
	//plik << "-----------\ndo globalnej\n";
	bool czy;	//zmienna logiczna- czy trzeba twozy� nowy element macierzy globalnej (zapisywanej jako 3 wektory)?
	int pop = 0;	//indeks elementu tablicy A macierzy globalnej, po kt�rym nale�y wstawi� nowy
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
	//plik << "------------------------\n";
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


// funkcja dodaj�ca warunki brzegowe (I rodzaju)
void Macierze::brzegowe (Macierze& M, Siatka S, std::vector <float>& P, std::vector <class WarunkiBrzegowe> brzeg)
{
	int szuk, pom, nx, ny;
	bool czy;
	std::vector<int> wezly;	//numery w�z��w, na kt�re wp�ywa warunek brzegowy;
	for (int i = 0; i < brzeg.size(); i++)
	{
		wezly.clear();
		czy = true;
		pom = 0;
		while (czy)	//p�tla zape�niaj�ca wektor wezly dla jednego warunku brzegowego
		{
			ny = pom / S.kord_x.size();
			nx = pom % S.kord_x.size();
			if (S.kord_x[nx] >= brzeg[i].x1 && S.kord_x[nx] <= brzeg[i].x2 && S.kord_y[ny] >= brzeg[i].y1 && S.kord_y[ny] <= brzeg[i].y2)
			{
				wezly.push_back(pom);
			}
			if ((S.kord_x[nx] >= brzeg[i].x2 && S.kord_y[ny] >= brzeg[i].y2) ||(ny == S.kord_y.size()-1 && nx == S.kord_x.size()-1))
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
					M.A[k] *= 100000000;
					pomK = M.A[k];
				}
			}
			P[wezly[j]] =+ pomK*brzeg[i].temperatura;
		}
	}
}
