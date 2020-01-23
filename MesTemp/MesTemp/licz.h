//klasa ��cz�ca pozosta�e i podaj�ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{

public:
	//funkcja tworz�ca macierz lokaln�
	void licz::lokalna(float lamx, float lamy, float(&macierz)[16], float(&P)[4], float wys, float szer, float Q);
	// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
	void licz::rozw(std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary, std::vector<WarunkiBrzegowe>wb);
	// funkcja podaj�ca temperatur� w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
	float licz::temp(float x, float y, int& ost, std::vector<float> T, Siatka S);
	// funkcja zwracaj�ca numer obszaru pod wskazanymi wsp�rz�dnymi
	void ktory_el(float x, float y, int& ost, Siatka S, bool& X);
	void ktory_obszar(float x, float y, int& ost, Siatka S, bool& X, std::vector <Input> obszary);
};

