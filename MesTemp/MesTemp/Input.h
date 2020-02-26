#pragma once
#include "pch.h"
#include <iostream>

class Input
{

	//atrybuty musza byc publiczne, bo odwolujemy sie do nich w innej klasie

public:

	int liczba_obszarow;
	float skala;
	float nr; //nr porzadkowy
	bool czy_prostokat; //okresla czy obszar jest prostokatem
	bool pion; //jesli obszar nie jest prostokatem to atrybut okresla czy obszar jest pionowy (1) czy poziomy (0)
	
	//zestaw wspolrzednych (prostokaty tylko x1 y1 i x4 y4)
	float x1; 
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
	bool czy_zrodlo; //okresla czy w obszarze jest zrodlo
	float moc_zrodla; //okresla moc zrodla
	float przewodnosc_x; //okresla przewodnosc obszaru
	float przewodnosc_y;
	char material[15]; //nazwa materialu
	
	Input::Input(); //pusty konstruktor aby utworzyc wstepny obiekt
	void czytaj(std::fstream& plik); //czytanie pliku i ustawianie atrybutow
	void test(int, std::vector <Input> wektor, bool & czy_pokrywa);
};

