
//Jędrzej Graczykowski 15.11.2019
//Program do zagęszczania wektorów współrzędnych siatki.

#include <iostream>
#include <vector>
#include <algorithm>


void zageszczenie_prostokatow(int gestosc, std::vector <float> &kord);
void wypelnienie(int ilosc, float krok, std::vector <float>& kord);
void pokaz(std::vector<float>& kord);


int main()
{
	std::vector <float> kord_x;
	std::vector <float> kord_y;

	std::cout << "\n\n***Program zageszczajacy kordy_x i kordy_y***\n\n";
	wypelnienie(6, 2, kord_x);
	wypelnienie(3, 1, kord_y);
	std::cout << "\nKord_x:\n";
	pokaz(kord_x);
	std::cout << "\nKord_y:\n";
	pokaz(kord_y);
	std::cout << "\ntemp_x:\n";
	zageszczenie_prostokatow(3, kord_x);
	std::cout << "\ntemp_y:\n";
	zageszczenie_prostokatow(2, kord_y);
	std::cout << "\nKord_x:\n";
	pokaz(kord_x);
	std::cout << "\nKord_y:\n";
	pokaz(kord_y);
	std::cout << "\n\n\n";
}


void wypelnienie(int ilosc, float krok, std::vector <float>& kord)
{
	/*
	Funkcja wypelnia wektor kordów_x lub kordów_y liczbami.
	Należy podać:
	1. ilość współrzędnych 
	2. odstęp między nimi
	3. wektor kordów_x lub kordów_y
	*/

	for (int i = 0; i < ilosc; i++)
	{
		kord.push_back(i*krok);
	}
}


void zageszczenie_prostokatow(int gestosc, std::vector <float> &kord)
{
	/*
	Funkcja zagęszcza współrzędne. Należy podać:
	1. ile nowych współrzędnych ma przypaść między danymi dwiema (gęstość)
	2. wektor kordów_x lub kordów_y
	*/

	std::vector <float> temp;
	std::vector <float> temp2;
	temp.clear();
	temp2.clear();
	//polowienie kordow
	for (int i = 0; i < kord.size()-1; i++)
	{
		for (int j = 0; j < gestosc - 1; j++)
		{	
			if (temp2.empty())
				temp2.push_back(kord[i] + 1.0 / gestosc * (kord[i+1] - kord[i]));
			else
				temp2.push_back(temp2[j-1] + 1.0 / gestosc * (kord[i+1] - kord[i]));
			temp.push_back(temp2[j]);
		}
		temp2.clear();
	}

	//dodanie tymczasowych kordow do kord i wypisanie ich dla testów
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp[i] << "  ";
		kord.push_back(temp[i]);
	}

	//porządkowanie kordów_x lub kordów_y
	std::sort(kord.begin(), kord.end()); //sortowanie elementow
	kord.erase(std::unique(kord.begin(), kord.end()), kord.end()); //usuwanie duplikatow
	temp.clear(); //czyszczenie tymczasowych kordow
}


void pokaz(std::vector<float> &kord)
{
	/*
	Funkcja wypisuje współrzędne. Należy podać:
	1. wektor kordów_x lub kordów_y
	*/
	for (int i = 0; i < kord.size(); i++)
		std::cout << kord[i] << "  ";

}


