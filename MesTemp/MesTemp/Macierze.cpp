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
