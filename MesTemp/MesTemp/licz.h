//klasa ³¹cz¹ca pozosta³e i podaj¹ca ostateczny wynik
#pragma once
#include "pch.h"
class licz
{

public:
	//funkcja tworz¹ca macierz lokaln¹
	void licz::lokalna(float lamx, float lamy, float(&macierz)[16], float(&P)[4], float wys, float szer, float Q);
	// funkcja zarz¹dzaj¹ca tworzeniem macierzy globalnej i rozwi¹zywaniem uk³adu równañ
	void licz::rozw(std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary, std::vector<WarunkiBrzegowe>wb);
	// funkcja podaj¹ca temperaturê w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
	float licz::temp(float x, float y, int& ost, std::vector<float> T, Siatka S);
	// funkcja zwracaj¹ca numer obszaru pod wskazanymi wspó³rzêdnymi
	void ktory_el(float x, float y, int& ost, Siatka S, bool& X);
	void ktory_obszar(float x, float y, int& ost, Siatka S, bool& X, std::vector <Input> obszary);
};

