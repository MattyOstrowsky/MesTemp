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
//rozwi¹zywanie uk³adu równañ, metoda iteracyjna
void Macierze::licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik)
{
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	int ile = Q.size();
	plik << "\nWeszlo do funkcji. ile = " << ile << "\n";
	plik.close();
	plik.open("Testy.txt", std::ofstream::app);
	float pom;
	std::vector<int> ii;	//indeksy elementów na g³ównej przek¹tnej
	float* stare = new float[ile];	//poprzednie wyniki, potrzebne by sprawdziæ kiedy skoñczyæ iteracjê
	bool czy;
	int pom2;
	plik << "\n\nkolejne elementy wektora ii:\n";
	plik.close();
	plik.open("Testy.txt", std::ofstream::app);
	for (int i = 0; i < ile; i++)	//wype³niamiy ii
	{
		pom2 = K.prow[i];
		while (i != K.coln[pom2])pom2++;
		ii.push_back(pom2);
		plik << ii[i] << " ; ";
		plik.close();
		plik.open("Testy.txt", std::ofstream::app);
	}
	plik << "\nprzeszlo, wchodzi do petli 'do'\n";
	plik.close();
	plik.open("Testy.txt", std::ofstream::app);
	do
	{
		plik << "kolejny obrot do\n";
		plik.close();
		plik.open("Testy.txt", std::ofstream::app);
		czy = false;
		for (int i = 0; i < ile; i++)
		{
			stare[i] = wynik[i];	//przepisuje poprzednie wyniki do tablicy pomocniczej
		}
		plik << "przepislo stare wyniki:\n";
		plik.close();
		plik.open("Testy.txt", std::ofstream::app);
		for (int i = 0; i < ile; i++)
		{
			plik << "stary: " << stare[i];
			plik.close();
			plik.open("Testy.txt", std::ofstream::app);
			pom = Q[i];
			for (int j = K.prow[i]; j < K.prow[i + 1]; j++)	//mno¿enie macierzy przez wektor tylko dla niezerowych elementów
			{
				pom -= K.A[j] * stare[K.coln[j]];
			}
			pom += K.A[ii[i]] * stare[i];
			plik << "pom = " << pom;
			wynik[i] = pom / K.A[ii[i]];
			plik << "\nnowy: " << wynik[i] << "\n";
			plik.close();
			plik.open("Testy.txt", std::ofstream::app);
			if ((abs((wynik[i] - stare[i]) / wynik[i])) > 0.1) czy = true;	//przyrównanie wzglêdnej zmiany wyniku do zadanej dok³adnoœci
		}
	} while (czy);
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
void Macierze::do_globalnej(Macierze& globalna, float lokalna[][4], float lokp[4],std::vector <float>& P, int wspolrzedne[4])
{
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	plik << "-----------\ndo globalnej\n";
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
		plik << "P_glob " << wspolrzedne[i] << " = " << P[wspolrzedne[i]] << "\n";
	}
	plik << "------------------------\n";
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
