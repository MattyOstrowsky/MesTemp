#include "pch.h"
#include "Macierze.h"

//konstruktor. Do uzupe�nienia
Macierze::Macierze(std::vector<float>& danea, std::vector<float>& danep, std::vector<int>& danec)
{
	A = danea;
	prow = danep;
	coln = danec;
}
//rozwi�zywanie uk�adu r�wna�, metoda iteracyjna
void Macierze::licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik)
{
	int ile = Q.size();
	float pom;
	std::vector<int> ii;	//indeksy element�w na g��wnej przek�tnej
	float* stare = new float[ile];	//poprzednie wyniki, potrzebne by sprawdzi� kiedy sko�czy� iteracj�
	bool czy;
	int pom2;
	for (int i = 0; i < ile; i++)	//wype�niamiy ii
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
			for (int j = K.prow[i]; j < K.prow[i + 1]; j++)	//mno�enie macierzy przez wektor tylko dla niezerowych element�w
			{
				pom -= K.A[j] * stare[K.coln[j]];
			}
			pom += K.A[ii[i]] * stare[i];
			wynik[i] = pom / K.A[ii[i]];
			if (abs((wynik[i] - stare[i]) / wynik[i]) > 0.001) czy = true;	//przyr�wnanie wzgl�dnej zmiany wyniku do zadanej dok�adno�ci
		}
	} while (czy);
}
