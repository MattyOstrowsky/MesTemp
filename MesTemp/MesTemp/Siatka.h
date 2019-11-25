#pragma once
#include "Input.h"

class Siatka
{
private:
	std::vector <Input> element; //wektor element�w z klasy od wczytania danych
public:
	std::vector <float> kord_x; // kordy x siatki prostokatnej
	std::vector <float> kord_y; // kordy y siatki prostokatnej
	std::vector <std::vector <float>> nwezel; // wektor wezlow siatki nieregularnej

	Siatka::Siatka(std::vector <Input>&);

	void utworz_siatke(std::vector <Input>&); //utworzenie wstepnej siatki, argument jest wektorem obiektow klasy od wczytania danych

	void zageszczenie_prostokatow(int, std::vector <float>&); //zageszczenie prostokatow: 
															  //1. ilosc elementow w poziomie lub w pionie,
															  //2. kord_x lub kord_y

	void zageszczenie_nieregularne(int); //zageszczenie nieregularnej siatki:
										//  tworzenie w�z��w na podstawie zadanej g�sto�ci (takiej samej jak przy prostok�tach)
										   // na przeciwleg�ych �cianach w zale�no�ci czy element jest pionowy czy poziomy 
										//	(NIE DZIELIMY PIONOWYCH ELEMENT�W POZIOMO!!!

};

