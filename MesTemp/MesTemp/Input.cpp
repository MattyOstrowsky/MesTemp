#include "pch.h"
#include "Input.h"


Input::Input() {}; //pusty konstruktor aby utworzyc wstepny obiekt

//czytanie pliku i ustalanie atrybutow oraz pakowanie obiektow do wektora
void Input::czytaj(std::ifstream& plik)
{

	plik >> czy_prostokat;

	if (czy_prostokat) // dla prostokatow
		plik >> nr >> x1 >> y1 >> x4 >> y4;
	else //dla nieprostokatow
		plik >> pion >> nr >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

	plik >> czy_zrodlo >> moc_zrodla >> przewodnosc >> material;
};
