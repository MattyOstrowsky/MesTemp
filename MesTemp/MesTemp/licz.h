//klasa ��cz�ca pozosta�e i podaj�ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{

public:
	// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
	void rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary);
	// funkcja podaj�ca temperatur� w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
	float licz::temp(float x, float y, int& ost, std::vector<float> T, std::vector<Prostokat>E, Siatka S);
};

