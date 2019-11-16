#pragma once
#include "Element.h"

class Siatka
{
private:
	std::vector <Element> element; //wektor elementów z klasy Element
public:
	std::vector <float> kord_x;
	std::vector <float> kord_y;

	Siatka::Siatka(std::vector <Element>); //konstruktor, argument jest obiektem klasy element

	void zageszczenie_prostokatow(int, std::vector <float>&); //zageszczenie prostokatow: 
															  //1. ilosc elementow w poziomie lub w pionie,
															  //2. kord_x lub kord_y

};

