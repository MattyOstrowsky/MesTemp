#include "pch.h"
#include "Input.h"
#include "MesTempView.h"

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
void Input::test(int liczba_obszarow, std::vector <Input> wektor, bool & czy_pokrywa)
{
	czy_pokrywa = true;
	for (int i = 0; i < liczba_obszarow; i++)
	{
		for (int j = 0; j < liczba_obszarow; j++)
		{
			if(wektor[i].czy_prostokat)
			{
				if (wektor[i].x1 > wektor[j].x1 && wektor[i].x1 < wektor[j].x2 && wektor[i].y1 > wektor[j].y1 && wektor[i].y1 < wektor[j].y2)
				{
					czy_pokrywa = true;
				}
				if (wektor[i].x2 > wektor[j].x1&& wektor[i].x2 < wektor[j].x2 && wektor[i].y1 > wektor[j].y1&& wektor[i].y1 < wektor[j].y2)
				{
					czy_pokrywa = true;
				}
				if (wektor[i].x2 > wektor[j].x1&& wektor[i].x2 < wektor[j].x2 && wektor[i].y2 > wektor[j].y1&& wektor[i].y2 < wektor[j].y2)
				{
					czy_pokrywa = true;
				}
				if (wektor[i].x1 > wektor[j].x1&& wektor[i].x1 < wektor[j].x2 && wektor[i].y2 > wektor[j].y1&& wektor[i].y2 < wektor[j].y2)
				{
					czy_pokrywa = true;
				}
			}
			else
			{
				czy_pokrywa = true;
			}
		}
	}
};