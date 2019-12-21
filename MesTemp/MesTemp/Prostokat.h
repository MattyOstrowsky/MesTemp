#pragma once
#include "pch.h"
//element prostok�tny
class Prostokat
{
public:
	//numer elementu i lewego dolnego elementu(na podstawie w�a�ciwo�ci siatki mo�na wyliczy� numery wszystkich w�z��w)
	int nr, n1;
	//numer obszaru materia�owego, w kt�rym znajduje si� prostok�tny element
	int obszar;
	//ciep�o
	float Q;
	//konstruktor
	Prostokat(int n, int n_1, int o, float q);
	//funkcja tworz�ca macierz lokaln� prostok�tnego elementu
	void lokalna(float lamx, float lamy, float (&macierz)[16], float (&P)[4], float wys, float szer);

};

