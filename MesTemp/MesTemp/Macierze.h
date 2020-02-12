#pragma once
#include "pch.h"
#include "fstream"
#include "string.h"
//zapis macierzy metod¹ SRF (3 tablic. No, tutaj to w³aœciwie wektorów)
class Macierze
{

public:
	// indeksy pierwszych elementów kolejnych wierszy. ¯eby algorytm dzia³a³ dobrze na koñcu trzeba dodaæ indeks nieistniej¹cego wiersza n+1
	std::vector<int> prow;
	// numer kolumny ka¿dego zapisanego elementu
	std::vector<int> coln;
	// wartoœci zappisanych elementów macierzy
	std::vector<float> A;

	//konstruktor, na razie nie wiem, jak go zrobiæ
	Macierze(std::vector<float>& danea, std::vector<int>& danep, std::vector<int>& danec);

	//funkcja rozwi¹zuj¹ca uk³ad równañ iteracyjn¹ metod¹ Gaussa-Siedla
	void licz(Macierze K, std::vector<float>& Q, std::vector<float>& wynik);
	// funkcja dodaj¹ca macierz lokaln¹ albo wskazan¹ wartoœæ do globalnej
	void do_globalnej2(Macierze& globalna, float lokalna[][4], float lokp [4], std::vector <float>& P, int wspolrzedne[4]);
	void do_globalnej(Macierze& globalna, float co, int gdziex, int gdziey);
	void pisz(std::string nazwa, Macierze M2, int ile);	//do prób
	// funkcja dodaj¹ca warunki brzegowe (I rodzaju)
	void brzegowe(Macierze& M, Siatka S, std::vector <float>& P, std::vector <class WarunkiBrzegowe> brzeg);
};

