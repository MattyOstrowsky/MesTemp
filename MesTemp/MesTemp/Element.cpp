#include "pch.h"
#include "Element.h"

//pusty konstruktor
Element::Element()
{
}
//pe³niejszy konstruktor
Element::Element(int numer, int N1, int N2, int N3, int N4, float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
{
	nr = numer;
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
	x3 = X3;
	y3 = Y3;
	x4 = X4;
	y4 = Y4;
	nr1 = N1;
	nr2 = N2;
	nr3 = N3;
	nr4 = N4;
}

void Element::ust_wsp(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
{
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
	x3 = X3;
	y3 = Y3;
	x4 = X4;
	y4 = Y4;
}

void Element::numeruj(int numer, int N1, int N2, int N3, int N4)
{
	nr = numer;
	nr1 = N1;
	nr2 = N2;
	nr3 = N3;
	nr4 = N4;
}

// funkcja ustawiaj¹ca temperatury w wêz³ach
void Element::ust_temp(float T1, float T2, float T3, float T4)
{
	t1 = T1;
	t2 = T2;
	t3 = T3;
	t4 = T4;
}


// funkcja tworz¹ca element podstawowy (kwadrat o rogach w 1 i -1) z temperaturami jak w elemencie Ÿród³owym
Element Element::el_podstawowy(Element zrodlo)
{
	Element wynik;
	wynik.ust_wsp(-1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0);
	wynik.ust_temp(zrodlo.t1, zrodlo.t2, zrodlo.t3, zrodlo.t4);
	return wynik;
}
