#pragma once
//element prostok¹tny
class Prostokat
{
	//numer elementu i lewego dolnego elementu(na podstawie w³aœciwoœci siatki mo¿na wyliczyæ numery wszystkich wêz³ów)
	int nr;
	//Temperatury na wêz³ach
	float T1, T2, T3, T4;
	//konstruktor
	Prostokat(int n, float t1, float t2, float t3, float t4);
	//funkcja renumeruj¹ca element
	void numeruj(int n);
	//funkcja zmieniaj¹ca temperatury na wêz³ach
	void ust_temp(float t1, float t2, float t3, float t4);

};

