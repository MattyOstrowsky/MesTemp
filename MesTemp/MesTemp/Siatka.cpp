#include "pch.h"
#include "Siatka.h"


Siatka::Siatka(std::vector <Element> E) 
{

	//wczytanie danych
	element = E;
	int ilosc_obszarow = element.size();

	//dodawanie kordów x i y na podstawie wprowadzonych obszarów
	for (int i = 0; i < ilosc_obszarow; i++)
	{
		kord_x.push_back(element[i].x1);
		kord_x.push_back(element[i].x2);
		kord_y.push_back(element[i].y1);
		kord_y.push_back(element[i].y2);
	}

	element.clear(); //wyczyszczenie pamieci

	//kordy x
	std::sort(kord_x.begin(), kord_x.end()); //sortowanie elementow
	kord_x.erase(std::unique(kord_x.begin(), kord_x.end()), kord_x.end()); //usuwanie duplikatow
	//kordy y
	std::sort(kord_y.begin(), kord_y.end()); //sortowanie elementow
	kord_y.erase(std::unique(kord_y.begin(), kord_y.end()), kord_y.end()); //usuwanie duplikatow

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






