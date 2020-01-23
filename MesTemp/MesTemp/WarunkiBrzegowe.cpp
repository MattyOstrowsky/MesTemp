#include "pch.h"
#include "WarunkiBrzegowe.h"
#include "iostream"

WarunkiBrzegowe::WarunkiBrzegowe()
{};

void WarunkiBrzegowe::czytaj(std::fstream& plik)
{
	plik >> x1 >> y1 >> x2 >> y2 >> temperatura;
};
