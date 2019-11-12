#pragma once
#include "pch.h"
class Element
{
public:
	// numer elementu
	int nr;
	//numery wêz³ów
	int nr1;
	int nr2;
	int nr3;
	int nr4;
	//wspó³rzêdne wêz³ów (wierzcho³ków)
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
	//numery s¹siadów dook³a ka¿dego wêz³a
	std::vector<int> s1;
	std::vector<int> s2;
	std::vector<int> s3;
	std::vector<int> s4;
	//temperatury w wêz³ach
	float t1;
	float t2;
	float t3;
	float t4;

	//konstruktor pusty (jakby by³ potrzebny)
	Element();
	//konstruktor ze wspó³rzêdnymi i numerem (do pe³nej konstrukcji przy tworzeniu)
	Element(int numer, int N1, int N2, int N3, int N4, float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4);

	//funkcja ustawiaj¹ca (zmieniaj¹ca) wspó³rzêdne
	void ust_wsp(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4);
	//funkcja ustawiaj¹ca (zmieniaj¹ca) numery elementu i wêz³ów
	void numeruj(int numer, int N1, int N2, int N3, int N4);

	// funkcja ustawiaj¹ca (zmieniaj¹ca) temperatury w wêz³ach
	void ust_temp(float T1, float T2, float T3, float T4);
	// funkcja tworz¹ca element podstawowy (kwadrat o rogach w 1 i -1) z temperaturami jak w elemencie Ÿród³owym
	Element el_podstawowy(Element zrodlo);
};

