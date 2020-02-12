#pragma once
#include "pch.h"
#include "fstream"
#include "string.h"
//zapis macierzy metod� SRF (3 tablic. No, tutaj to w�a�ciwie wektor�w)
class Macierze
{

public:
	// indeksy pierwszych element�w kolejnych wierszy. �eby algorytm dzia�a� dobrze na ko�cu trzeba doda� indeks nieistniej�cego wiersza n+1
	std::vector<int> prow;
	// numer kolumny ka�dego zapisanego elementu
	std::vector<int> coln;
	// warto�ci zappisanych element�w macierzy
	std::vector<float> A;

	//konstruktor, na razie nie wiem, jak go zrobi�
	Macierze(std::vector<float>& danea, std::vector<int>& danep, std::vector<int>& danec);

	//funkcja rozwi�zuj�ca uk�ad r�wna� iteracyjn� metod� Gaussa-Siedla
	void licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik);
	// funkcja dodaj�ca macierz lokaln� albo wskazan� warto�� do globalnej
	void do_globalnej2(Macierze& globalna, float lokalna[][4], float lokp [4], std::vector <float>& P, int wspolrzedne[4]);
	void do_globalnej(Macierze& globalna, float co, int gdziex, int gdziey);
	void pisz(std::string nazwa, Macierze M2, int ile);	//do pr�b
	// funkcja dodaj�ca warunki brzegowe (I rodzaju)
	void brzegowe(Macierze& M, Siatka S, std::vector <float>& P, std::vector <class WarunkiBrzegowe> brzeg);
};

