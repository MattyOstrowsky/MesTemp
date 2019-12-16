//klasa ³¹cz¹ca pozosta³e i podaj¹ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{
	
public:
	// funkcja zarz¹dzaj¹ca tworzeniem macierzy globalnej i rozwi¹zywaniem uk³adu równañ
	void rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, float lx, float ly, Siatka S);
};

