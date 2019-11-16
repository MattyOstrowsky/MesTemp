#pragma once
#include "pch.h"
//zapis macierzy metod� SRF (3 tablic. No, tutaj to w�a�ciwie wektor�w)
class Macierze
{

public:
	// indeksy pierwszych element�w kolejnych wierszy. �eby algorytm dzia�a� dobrze na ko�cu trzeba doda� indeks nieistniej�cego woersza n+1
	std::vector<float> prow;
	// numer kolumny ka�dego zapisanego elementu
	std::vector<int> coln;
	// warto�ci zappisanych element�w macierzy
	std::vector<float> A;

	//konstruktor, na razie nie wiem, jak go zrobi�
	Macierze(std::vector<float>& danea, std::vector<float>& danep, std::vector<int>& danec);

	//funkcja rozwi�zuj�ca uk�ad r�wna�
	void licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik);
};
