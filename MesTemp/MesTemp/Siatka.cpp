#include "pch.h"
#include "Siatka.h"
#include "Element.h"
#include <vector>
#include <algorithm> //od sortowania

Siatka::Siatka(std::vector <Element> E) 
{
	element = E;
}

void Siatka::ustaw_kordy()
{
	int ilosc_elementow = element.size();

	//dodawanie kordów na podstawie wprowadzonych elementów
	for (int i = 0; i < ilosc_elementow; i++)
	{
		kord_x.push_back(element[i].x1);
		kord_x.push_back(element[i].x2);
		kord_y.push_back(element[i].y1);
		kord_y.push_back(element[i].y2);

	}

	//kordy x
	std::sort(kord_x.begin(), kord_y.end()); //sortowanie elementow
	kord_x.erase(std::unique(kord_x.begin(), kord_x.end()), kord_x.end()); //usuwanie duplikatow
	//kordy y
	std::sort(kord_y.begin(), kord_y.end()); //sortowanie elementow
	kord_y.erase(std::unique(kord_y.begin(), kord_y.end()), kord_y.end()); //usuwanie duplikatow
	
}

void Siatka::zageszczenie_prostokatow(int gestosc)
{
	std::vector <float> temp; // tymczasowe kordy

	//Zageszczenie pierwszego elementu przez polowienie w strone drugiego elementu
	temp.push_back(0.5 * (kord_x[1] - kord_x[0]));
	for (int j = 0; j < gestosc - 2; j++)
		temp.push_back(0.5 * (kord_x[1] - temp[j]));
	//Zageszczenie ostatniego elementu przez polowienie w strone przedostatniego elementu
	temp.push_back(0.5 * (kord_x[-1] - kord_x[-2]));
	for (int k = 0; k < gestosc - 2; k++)
		temp.push_back(0.5 * (temp[k + gestosc - 1] - kord_x[-2]));

	//Dodanie elementów do 
	for (int jk = 0; jk < temp.size(); jk++)
		kord_x.push_back(temp[jk]);

	temp.clear();

	//Zageszczenie pierwszego elementu x przez polowienie w strone drugiego elementu
	temp.push_back(0.5 * (kord_y[1] - kord_y[0]));
	for (int j = 0; j < gestosc - 2; j++)
		temp.push_back(0.5 * (kord_y[1] - temp[j]));
	//Zageszczenie ostatniego elementu x przez polowienie w strone przedostatniego elementu
	temp.push_back(0.5 * (kord_y[-1] - kord_y[-2]));
	for (int k = 0; k < gestosc - 2; k++)
		temp.push_back(0.5 * (temp[k + gestosc - 1] - kord_y[-2]));

	//Dodanie temp do kordow 
	for (int jk = 0; jk < temp.size(); jk++)
		kord_y.push_back(temp[jk]);

	temp.clear();


}

