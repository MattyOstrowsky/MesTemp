#pragma once
#include "pch.h"
#include "iostream"

class WarunkiBrzegowe
{
public:
	float x1;
	float x2;
	float y1;
	float y2;
	float temperatura;

	WarunkiBrzegowe::WarunkiBrzegowe();
	void czytaj(std::fstream& plik);
};

