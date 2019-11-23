#include "pch.h"
#include "Siatka.h"


Siatka::Siatka(std::vector <Element> E) 
{

	//wczytanie danych
	element = E;
	int ilosc_elementow = element.size();

	//dodawanie kord�w x i y na podstawie wprowadzonych obszar�w do siatki prostokatnej
	for (int i = 0; i < ilosc_elementow; i++)
	{
		if (element[i].czy_prostokat)
		{
			kord_x.push_back(element[i].x1);
			kord_x.push_back(element[i].x2);
			kord_y.push_back(element[i].y1);
			kord_y.push_back(element[i].y2);
		}
	}

	//dodawanie w�z��w na podstawie obszar�w do siatki nieregularnej
	for (int i = 0; i < ilosc_elementow; i++)
	{
		if (!element[i].czy_prostokat)
		{
			nwezel.push_back({ element[i].x1, element[i].y1 });
			nwezel.push_back({ element[i].x2, element[i].y2 });
			nwezel.push_back({ element[i].x3, element[i].y3 });
			nwezel.push_back({ element[i].x4, element[i].y4 });
		}
	}


	//kordy x
	std::sort(kord_x.begin(), kord_x.end()); //sortowanie elementow
	kord_x.erase(std::unique(kord_x.begin(), kord_x.end()), kord_x.end()); //usuwanie duplikatow
	//kordy y
	std::sort(kord_y.begin(), kord_y.end()); //sortowanie elementow
	kord_y.erase(std::unique(kord_y.begin(), kord_y.end()), kord_y.end()); //usuwanie duplikatow
	//wezly siatki nieregularnej
	std::sort(nwezel.begin(), nwezel.end()); //sortowanie elementow
	nwezel.erase(std::unique(nwezel.begin(), nwezel.end()), nwezel .end()); //usuwanie duplikatow

}


void Siatka::zageszczenie_prostokatow(int gestosc, std::vector<float>& kord)
{
	//wektory tymczasowych kordow
	std::vector <float> temp;
	std::vector <float> temp2;
	temp.clear();
	temp2.clear();

	//polowienie kordow
	for (int i = 0; i < kord.size() - 1; i++)
	{
		for (int j = 0; j < gestosc - 1; j++)
		{
			if (temp2.empty())
				temp2.push_back(kord[i] + 1.0 / gestosc * (kord[i + 1] - kord[i]));
			else
				temp2.push_back(temp2[j - 1] + 1.0 / gestosc * (kord[i + 1] - kord[i]));
			temp.push_back(temp2[j]);
		}
		temp2.clear();
	}

	//dodanie tymczasowych kordow do kord_x lub kord_y
	for (int i = 0; i < temp.size(); i++)
	{
		kord.push_back(temp[i]);
	}

	//porzadkowanie kordow
	std::sort(kord.begin(), kord.end()); //sortowanie elementow
	kord.erase(std::unique(kord.begin(), kord.end()), kord.end()); //usuwanie duplikatow
	temp.clear(); //czyszczenie tymczasowych kordow
}


void Siatka::zageszczenie_nieregularne(int gestosc)
{
	//sprawdzanie ka�dego obszaru
	for (int i = 0; i < element.size(); i++)
	{
		//sprawdzanie czy obszar jest prostok�tem
		if (!element[i].czy_prostokat)
		{
			//sprawdzenie czy element jest pionowy
			if (element[i].pion)
			{
				//dodawanie par w�z��w w zale�no�ci od kszta�tu elementu

				if (element[i].y1 < element[i].y3)
					nwezel.push_back({ element[i].x1 + 1.0 / gestosc * (element[i].x3 - element[i].x1),
										element[i].y1 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1) });
				else
					nwezel.push_back({ element[i].x1 + 1.0 / gestosc * (element[i].x3 - element[i].x1),
										element[i].y3 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1) });
				if (element[i].y2 < element[i].y4)
					nwezel.push_back({ element[i].x2 + 1.0 / gestosc * (element[i].x4 - element[i].x2),
										element[i].y2 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2) });
				else
					nwezel.push_back({ element[i].x2 + 1.0 / gestosc * (element[i].x2 - element[i].x4),
										element[i].y4 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2) });
			}
			//dla element�w poziomych
			else
			{
				//dodawanie par w�z��w w zale�no�ci od kszta�t�w element�w

				if (element[i].x1 < element[i].x3)
					nwezel.push_back({ element[i].x1 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1), 
										element[i].y1 + 1.0 / gestosc * (element[i].y3 - element[i].y1) });
				else 
					nwezel.push_back({ element[i].x3 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1),
										element[i].y1 + 1.0 / gestosc * (element[i].y3 - element[i].y1) });
				if (element[i].x2 < element[i].x4)
					nwezel.push_back({ element[i].x2 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1),
										element[i].y2 + 1.0 / gestosc * (element[i].y4 - element[i].y2) });
				else
					nwezel.push_back({ element[i].x4 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1),
										element[i].y2 + 1.0 / gestosc * (element[i].y4 - element[i].y2) });
				
			}
		}
	}

	//sortowanie i usuwanie duplikat�w siatki nieprostok�tnej
	std::sort(nwezel.begin(), nwezel.end()); //sortowanie elementow
	nwezel.erase(std::unique(nwezel.begin(), nwezel.end()), nwezel.end()); //usuwanie duplikatow

	element.clear(); // czyszczenie pami�ci

}






