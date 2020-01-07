#include "pch.h"
#include "Macierze.h"

//konstruktor. Do uzupe³nienia
Macierze::Macierze(std::vector<float>& danea, std::vector<float>& danep, std::vector<int>& danec)
{
	A = danea;
	prow = danep;
	coln = danec;
}
//rozwi¹zywanie uk³adu równañ, metoda iteracyjna
void Macierze::licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik)
{
	int ile = Q.size();
	float pom;
	std::vector<int> ii;	//indeksy elementów na g³ównej przek¹tnej
	float* stare = new float[ile];	//poprzednie wyniki, potrzebne by sprawdziæ kiedy skoñczyæ iteracjê
	bool czy;
	int pom2;
	for (int i = 0; i < ile; i++)	//wype³niamiy ii
	{
		pom2 = K.prow[i];
		while (i != K.coln[pom2])pom2++;
		ii.push_back(pom2);
	}
	do
	{
		czy = false;
		for (int i = 0; i < ile; i++)
		{
			stare[i] = wynik[i];	//przepisuje poprzednie wyniki do tablicy pomocniczej
		}
		for (int i = 0; i < ile; i++)
		{
			pom = Q[i];
			for (int j = K.prow[i]; j < K.prow[i + 1]; j++)	//mno¿enie macierzy przez wektor tylko dla niezerowych elementów
			{
				pom -= K.A[j] * stare[K.coln[j]];
			}
			pom += K.A[ii[i]] * stare[i];
			wynik[i] = pom / K.A[ii[i]];
			if (abs((wynik[i] - stare[i]) / wynik[i]) > 0.001) czy = true;	//przyrównanie wzglêdnej zmiany wyniku do zadanej dok³adnoœci
		}
	} while (czy);
}

void Macierze::do_globalnej(Macierze& globalna, float co, int gdziex, int gdziey)
{
	bool czy = true;	//zmienna logiczna- czy trzeba twozyæ nowy element macierzy globalnej (zapisywanej jako 3 wektory)?
	int pop = 0;	//indeks elementu tablicy A macierzy globalnej, po którym nale¿y wstawiæ nowy
	std::vector<float>::iterator it;
	std::vector<int>::iterator it2;
	for (int k = globalna.prow[gdziey] - 1; k < globalna.prow[gdziey + 1]; k++)	//szuka, czy istnieje ju¿ niepusty element maierzy globalnej o takich indeksach
	{
		if (globalna.coln[k] == gdziex && k == globalna.prow[gdziey])
		{
			globalna.A[k] += co;
			czy = false;
		}
		if (k == globalna.prow[gdziey] - 1) pop = k;
		if (globalna.coln[k] < gdziex) pop = k;
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
	}
}
