#include "pch.h"
#include "licz.h"


// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
void licz::rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary)
{
	//lx i ly powinny by� sk�d� brane- siatka? prostok�t? input???
	int ilex = S.kord_x.size();
	int iley = S.kord_y.size();
	int ile = dane.size();
	int nx, ny;		//ilo�� element�w w szeregu i kolumnie siatki
	std::vector<float>x1 = {};
	std::vector<float>x2 = {};
	std::vector<int>x3 = {};
	std::vector<float> Qg (ile, 0);	//na razie pusty wektor globalny Q
	Macierze M(x1, x2, x3);	//na razie pusta macierz globalna
	float lok[16];
	float Q[4];
	int wsp[4];	//tablic wsp�rz�dnych w�z��w aktualnego elementu
	float pom[4][4];
	float lx, ly;	//wsp�czynniki przewodno�ci termicznej
	float dx, dy;		//szeroko�� i wysoko�� elementu
	//jaka� zewn�trzna p�tla do latania po r�nych obszarach?

	for (int i = 0; i < ile; i++)
	{
		ny = i / ilex;
		nx = i % ilex;
		dx = S.kord_x[nx + 1] - S.kord_x[nx];
		dy = S.kord_y[ny + 1] - S.kord_y[ny];
		lx = obszary[dane[i].obszar].przewodnosc_x;
		ly = obszary[dane[i].obszar].przewodnosc_y;
		dane[i].lokalna(lx, ly, lok, Q, dx, dy);
		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				pom[k][l] = lok[k + 4 * l];
			}
		}
		wsp[0] = dane[i].n1;
		wsp[1] = dane[i].n1+1;
		wsp[2] = dane[i].n1+ilex;
		wsp[3] = dane[i].n1+ilex+1;
		M.do_globalnej(M, pom, Q, Qg, wsp);
	}
	M.licz(M, Qg, wyniki);
}


// funkcja podaj�ca temperatur� w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
float licz::temp(float x, float y, int& ost, std::vector<float> T, std::vector<Prostokat>E, Siatka S)
{
	int n1;
	float nx, ny, kx, ky, lokx, loky, w;
	bool czy = true;	//czy kontynuowa� poszukiwania elementu
	//zamiast zwyk�ego fora p�tla zaczyna poszukiwania od sprawdzenia ostatnio u�ytego elementu. Nie doda�em obs�ugi b��d�w, wi�c
	//JE�LI PROGRAM WIESZA SI� NA TEJ P�TLI TO ZNACZY, �E WSKAZANY PUNKT JEST POZA GRANICAMI SIATKI
	while (czy)
	{
		ny = ost / S.kord_y.size();
		nx = ost % S.kord_x.size();
		if (x >= S.kord_x[nx] && x <= S.kord_x[nx + 1] && y >= S.kord_y[ny] && y <= S.kord_y[ny + 1])
		{
			czy = false;
		}
		else
		{
			if(ost == E.size())
			{
				ost = 0;
			}
			else
			{
				ost++;
			}
		}
	}
	//Po powy�szej p�tli wiadomo ju�, w kt�rym elemencie znajduje si� punkt
	kx = (S.kord_x[nx + 1] - S.kord_x[nx]) * 0.5;
	ky = (S.kord_y[ny + 1] - S.kord_y[ny]) * 0.5;		//wsp�czynniki proporcjonalno�ci
	lokx = (x - S.kord_x[nx])/kx -1;
	loky = (y - S.kord_y[ny])/ky -1;		//lokalne wsp�z�dne (-1;1)
	n1 = nx + ny * S.kord_x.size();			//numer lewego dolnego w�z�a
	w = T[n1] * (1 - lokx) * (1 - loky);
	w += T[n1 + 1] * (1 + lokx) * (1 - loky);
	w += T[n1 + S.kord_x.size()] * (1 - lokx) * (1 + loky);
	w += T[n1 + S.kord_x.size() + 1] * (1 + lokx) * (1 + loky);
	w *= 0.25;
	return w;
}