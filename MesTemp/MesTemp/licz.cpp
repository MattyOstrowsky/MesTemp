#include "pch.h"
#include "licz.h"


void licz::lokalna(float lamx, float lamy, float(&macierz)[16], float(&P)[4], float wys, float szer, float Q)
{
	int mx[4][4] = { {2,-2,-1,1},{-2,2,1,-1},{-1,1,2,-2},{1,-1,-2,2} };
	int my[4][4] = { {2,1,-1,-2},{1,2,-2,-1},{-1,-2,2,1},{-2,-1,1,2} };
	float pomx = (lamx * wys) / (12 * szer);
	float pomy = (lamy * wys) / (12 * szer);
	float pomp = Q * szer * wys / 4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			macierz[i + j * 4] = pomx * mx[i][j] + pomy * my[i][j];
		}
		P[i] = pomp;
	}
}

// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
void licz::rozw(std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary)
{
	licz R;
	//vector<flloat> wyniki (ile_wezlow, 0);
	//lx i ly powinny by� sk�d� brane- siatka? prostok�t? input???
	int ilex = S.kord_x.size();
	int iley = S.kord_y.size();
	int ile = (ilex - 1) * (iley - 1);
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
	int o = 0;
	bool B = false;
	//jaka� zewn�trzna p�tla do latania po r�nych obszarach?

	for (int x = 0; x < ilex-1; x++)
	{
		for (int y = 0; y < iley-1; y++)
		{
			dx = S.kord_x[x + 1] - S.kord_x[x];
			dy = S.kord_y[y + 1] - S.kord_y[y];
			R.ktory_obszar((S.kord_x[x] + 0.5 * dx), (S.kord_y[y] + 0.5 * dy), o, S, B, obszary);
			lx = obszary[o].przewodnosc_x;
			ly = obszary[o].przewodnosc_y;
			R.lokalna(lx, ly, lok, Q, dx, dy, obszary[o].moc_zrodla);
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					pom[k][l] = lok[k + 4 * l];
				}
			}
			wsp[0] = y*ilex + x;
			wsp[1] = y*ilex  + x + 1;
			wsp[2] = (y+1) * ilex + x;
			wsp[3] = (y + 1) * ilex + x + 1;
			M.do_globalnej(M, pom, Q, Qg, wsp);
		}
	}
	M.licz(M, Qg, wyniki);
}


// funkcja podaj�ca temperatur� w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
float licz::temp(float x, float y, int& ost, std::vector<float> T, Siatka S)
{
	licz L;
	int n1;
	float nx, ny, kx, ky, lokx, loky, w;
	bool czy = true;	//czy kontynuowa� poszukiwania elementu
	bool X = false;		//zmienna awaryjna, bada prawid�owy przebieg p�tli
	//zamiast zwyk�ego fora p�tla zaczyna poszukiwania od sprawdzenia ostatnio u�ytego elementu. Nie doda�em obs�ugi b��d�w, wi�c
	//JE�LI PROGRAM WIESZA SI� NA TEJ P�TLI TO ZNACZY, �E WSKAZANY PUNKT JEST POZA GRANICAMI SIATKI
	L.ktory_el (x, y, ost, S, X);
	//Po powy�szej p�tli wiadomo ju�, w kt�rym elemencie znajduje si� punkt
	ny = ost / S.kord_y.size();
	nx = ost % S.kord_x.size();
	if (X) return -300;
	else
	{
		kx = (S.kord_x[nx + 1] - S.kord_x[nx]) * 0.5;
		ky = (S.kord_y[ny + 1] - S.kord_y[ny]) * 0.5;		//wsp�czynniki proporcjonalno�ci
		lokx = (x - S.kord_x[nx]) / kx - 1;
		loky = (y - S.kord_y[ny]) / ky - 1;		//lokalne wsp�z�dne (-1;1)
		n1 = nx + ny * S.kord_x.size();			//numer lewego dolnego w�z�a
		w = T[n1] * (1 - lokx) * (1 - loky);
		w += T[n1 + 1] * (1 + lokx) * (1 - loky);
		w += T[n1 + S.kord_x.size()] * (1 - lokx) * (1 + loky);
		w += T[n1 + S.kord_x.size() + 1] * (1 + lokx) * (1 + loky);
		w *= 0.25;
		return w;
	}
}

// funkcja zwracaj�ca numer obszaru pod wskazanymi wsp�rz�dnymi
void licz:: ktory_obszar(float x, float y, int& ost, Siatka S, bool& X, std::vector <Input> obszary)
{
	bool czy = true;	//czy kontynuowa� poszukiwania elementu
	X = false;		//zmienna awaryjna, bada prawid�owy przebieg p�tli
	//zamiast zwyk�ego fora p�tla zaczyna poszukiwania od sprawdzenia ostatnio u�ytego elementu.
	//JE�LI PUNKT NIE NALE�Y DY �ADNEGO OBSZARU, TO X =  TRUE 
	while (czy)
	{
		if (x >= obszary[ost].x1 && x <= obszary[ost].x4 && y >= obszary[ost].y1 && obszary[ost].y4)
		{
			czy = false;
		}
		else
		{
			if (ost == obszary.size()-1)
			{
				ost = 0;
				if (X)
				{
					czy = false;
				}
				else
				{
					X = true;
				}
			}
			else
			{
				ost++;
			}
		}
	}
}
// funkcja zwracaj�ca numer elementu pod wskazanymi wsp�rz�dnymi
void licz::ktory_el(float x, float y, int& ost, Siatka S, bool& X)
{
	float nx, ny;
	bool czy = true;	//czy kontynuowa� poszukiwania elementu
	X = false;		//zmienna awaryjna, bada prawid�owy przebieg p�tli
	//zamiast zwyk�ego fora p�tla zaczyna poszukiwania od sprawdzenia ostatnio u�ytego elementu.
	//JE�LI PUNKT NIE NALE�Y DY �ADNEGO ELEMENTU, TO X = TRUE
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
			if (ost == (S.kord_x.size()-1)*(S.kord_y.size()-1)-1)
			{
				ost = 0;
				if (X)
				{
					czy = false;
				}
				else
				{
					X = true;
				}
			}
			else
			{
				ost++;
			}
		}
	}
}
