#include "pch.h"
#include "Input.h"


Input::Input() {}; //pusty konstruktor aby utworzyc wstepny obiekt

//czytanie pliku i ustalanie atrybutow oraz pakowanie obiektow do wektora
void Input::czytaj(CString nazwa)
{
	int liczba_obszarow;
	float skala;

	std::ifstream plik(nazwa); //otworzenie pliku o danej nazwie

	if (!plik) 
	{
		std::cout << "Plik nie moze byc otwarty.\n"; 
	}
	else 
	{

		plik >> liczba_obszarow;
		plik >> skala;

		for (int i = 0; i < liczba_obszarow; i++)
		{
			Input obszar; //utworzenie obiektu obszar
			plik >> czy_prostokat; 
			
			if (czy_prostokat) // dla prostokatow
				plik >> nr >> x1 >> y1 >> x4 >> y4;
			else //dla nieprostokatow
				plik >> pion >> nr >> x1 >> y1 >> x2>> y2 >> x3 >> y3 >> x4 >> y4;
			
			plik >> czy_zrodlo >> moc_zrodla >> przewodnosc >> material;

			dane.push_back(obszar); //dodanie obiektu do wektora
		}

		plik.close();
	}


};