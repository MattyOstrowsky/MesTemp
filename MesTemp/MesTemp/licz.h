//klasa ³¹cz¹ca pozosta³e i podaj¹ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{

public:
	// funkcja zarz¹dzaj¹ca tworzeniem macierzy globalnej i rozwi¹zywaniem uk³adu równañ
	void rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary);
	// funkcja podaj¹ca temperaturê w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
	float licz::temp(float x, float y, int& ost, std::vector<float> T, std::vector<Prostokat>E, Siatka S);
};

