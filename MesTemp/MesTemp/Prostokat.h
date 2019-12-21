#pragma once
#include "pch.h"
//element prostok¹tny
class Prostokat
{
public:
	//numer elementu i lewego dolnego elementu(na podstawie w³aœciwoœci siatki mo¿na wyliczyæ numery wszystkich wêz³ów)
	int nr, n1;
	//numer obszaru materia³owego, w którym znajduje siê prostok¹tny element
	int obszar;
	//ciep³o
	float Q;
	//konstruktor
	Prostokat(int n, int n_1, int o, float q);
	//funkcja tworz¹ca macierz lokaln¹ prostok¹tnego elementu
	void lokalna(float lamx, float lamy, float (&macierz)[16], float (&P)[4], float wys, float szer);

};

