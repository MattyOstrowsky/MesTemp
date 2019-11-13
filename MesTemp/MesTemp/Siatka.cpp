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
