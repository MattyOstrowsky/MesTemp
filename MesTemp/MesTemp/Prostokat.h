#pragma once
#include "pch.h"
//element prostok�tny
class Prostokat
{
public:
	//numer elementu i lewego dolnego elementu(na podstawie w�a�ciwo�ci siatki mo�na wyliczy� numery wszystkich w�z��w)
	int nr, n1;
	//Temperatury na w�z�ach
	float Q, T1, T2, T3, T4;
	//konstruktor
	Prostokat(int n, float t1, float t2, float t3, float t4);
	//funkcja renumeruj�ca element
	void numeruj(int n);
	//funkcja zmieniaj�ca temperatury na w�z�ach
	void ust_temp(float t1, float t2, float t3, float t4);
	//funkcja tworz�ca macierz lokaln� prostok�tnego elementu
	void lokalna(float lamx, float lamy, float (&macierz)[16], float (&P)[4], float wys, float szer);

};

