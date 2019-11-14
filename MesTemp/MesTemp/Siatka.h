#pragma once
#include "Element.h"
#include <vector>

class Siatka
{
private:
	std::vector <Element> element; //wektor elementów z klasy Element
public:
	std::vector <float> kord_x;
	std::vector <float> kord_y;

	Siatka::Siatka(std::vector <Element>); //konstruktor, argument jest obiektem klasy element

	void ustaw_kordy(); //ustawianie kordow x i y na podstawie wczytanych elemntow

	void zageszczenie_prostokatow(int);

	Siatka::~Siatka(); //destruktor

};

