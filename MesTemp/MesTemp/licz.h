//klasa ��cz�ca pozosta�e i podaj�ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{
	
public:
	// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
	void rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, float lx, float ly, Siatka S);
};

