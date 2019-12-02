#include "pch.h"
#include "Siatka.h"

Siatka::Siatka(std::vector <Input>& dane)
{
	element = dane;
}

void Siatka::utworz_siatke(std::vector <Input> &element) 
{

	//wczytanie danych
	int ilosc_elementow = element.size();

	//dodawanie kordów x i y na podstawie wprowadzonych obszarów do siatki prostokatnej
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

	//dodawanie wêz³ów na podstawie obszarów do siatki nieregularnej
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
				temp2.push_back(kord[i] + 1.0 / gestosc * abs(kord[i + 1] - kord[i]));
			else
				temp2.push_back(temp2[j - 1] + 1.0 / gestosc * abs(kord[i + 1] - kord[i]));
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

	std::vector <float> temp;
	
	//sprawdzanie ka¿dego obszaru
	for (int i = 0; i < element.size(); i++)
	{
		//sprawdzanie czy obszar jest prostok¹tem
		if (!element[i].czy_prostokat)
		{
			//sprawdzenie czy element jest pionowy
			if (element[i].pion)
			{
				//dodawanie par wêz³ów w zale¿noœci od kszta³tu elementu

				//pierwsza œcianka
				if (element[i].y1 < element[i].y3)
				{
					temp.push_back(element[i].x1 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1));
					temp.push_back(element[i].y1 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					nwezel.push_back(temp);
					temp.clear();
				}
				else
				{
					temp.push_back(element[i].x1 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1));
					temp.push_back(element[i].y3 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					nwezel.push_back(temp);
					temp.clear();
				}

				//druga œcianka
				if (element[i].y2 < element[i].y4)
				{
					temp.push_back(element[i].x2 + 1.0 / gestosc * abs(element[i].x4 - element[i].x2));
					temp.push_back(element[i].y2 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2));
					nwezel.push_back(temp);
					temp.clear();
				}
				else
				{
					temp.push_back(element[i].x2 + 1.0 / gestosc * abs(element[i].x2 - element[i].x4));
					temp.push_back(element[i].y4 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2));
					nwezel.push_back(temp);
					temp.clear();
				}
			}
			//dla elementów poziomych
			else
			{
				//dodawanie par wêz³ów w zale¿noœci od kszta³tów elementów

				//pierwsza œcianka
				if (element[i].x1 < element[i].x3)
				{
					temp.push_back(element[i].x1 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1));
					temp.push_back(element[i].y1 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					nwezel.push_back(temp);
					temp.clear();
				}
				else
				{
					temp.push_back(element[i].x3 + 1.0 / gestosc * abs(element[i].x3 - element[i].x1));
					temp.push_back(element[i].y1 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					nwezel.push_back(temp);
					temp.clear();
				}

				//druga œcianka
				if (element[i].x2 < element[i].x4)
				{
					temp.push_back(element[i].x2 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					temp.push_back(element[i].y2 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2));
					nwezel.push_back(temp);
					temp.clear();
				}
				else
				{
					temp.push_back(element[i].x4 + 1.0 / gestosc * abs(element[i].y3 - element[i].y1));
					temp.push_back(element[i].y2 + 1.0 / gestosc * abs(element[i].y4 - element[i].y2));
					nwezel.push_back(temp);
					temp.clear();
				}
			}
		}
	}

	//sortowanie i usuwanie duplikatów siatki nieprostok¹tnej
	std::sort(nwezel.begin(), nwezel.end()); //sortowanie elementow
	nwezel.erase(std::unique(nwezel.begin(), nwezel.end()), nwezel.end()); //usuwanie duplikatow

	element.clear(); // czyszczenie pamiêci
	
}








