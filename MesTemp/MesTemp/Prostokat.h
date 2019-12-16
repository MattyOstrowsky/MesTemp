#pragma once
#include "pch.h"
//element prostok¹tny
class Prostokat
{
public:
	//numer elementu i lewego dolnego elementu(na podstawie w³aœciwoœci siatki mo¿na wyliczyæ numery wszystkich wêz³ów)
	int nr, n1;
	//Temperatury na wêz³ach
	float Q, T1, T2, T3, T4;
	//konstruktor
	Prostokat(int n, float t1, float t2, float t3, float t4);
	//funkcja renumeruj¹ca element
	void numeruj(int n);
	//funkcja zmieniaj¹ca temperatury na wêz³ach
	void ust_temp(float t1, float t2, float t3, float t4);
	//funkcja tworz¹ca macierz lokaln¹ prostok¹tnego elementu
	void lokalna(float lamx, float lamy, float (&macierz)[16], float (&P)[4], float wys, float szer);

};

