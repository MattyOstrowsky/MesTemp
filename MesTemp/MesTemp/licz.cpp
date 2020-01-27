#include "pch.h"
#include "licz.h"
#include <fstream>


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

// funkcja zarz¹dzaj¹ca tworzeniem macierzy globalnej i rozwi¹zywaniem uk³adu równañ
void licz::rozw(std::vector<float>& wyniki, Siatka S, std::vector<Input> obszary, std::vector<WarunkiBrzegowe>wb)
{
	std::ofstream plik;
	plik.open("Testy.txt", std::ofstream::app);
	plik << "###########################\nWielki test wszystkiego. Zaczynamy!\n\n";
	licz R;
	//vector<flloat> wyniki (ile_wezlow, 0); ????/
	//lx i ly powinny byæ sk¹dœ brane- siatka? prostok¹t? input???
	int ilex = S.kord_x.size();
	int iley = S.kord_y.size();
	int ile = (ilex) * (iley);
	plik << "ilex = " << ilex << "; iley = " << iley<<"\nile = " << ile << "\n";
	int nx, ny;		//iloœæ elementów w szeregu i kolumnie siatki
	std::vector<float>x1 (ile, 0);
	std::vector<int>x2;
	std::vector<int>x3;
	for (int i = 0; i < ile; i++)
	{
		x2.push_back(i);
		x3.push_back(i);
	}
	x2.push_back(ile);
	std::vector<float> Qg (ile, 0);	//na razie pusty wektor globalny Q
	Macierze M(x1, x2, x3);	//na razie pusta macierz globalna
	//plik << "pusta macierz globalna:\n";
	//plik.close();
	//M.pisz("Testy.txt", M, ile);
	//plik.open("Testy.txt", std::ofstream::app);
	float lok[16];
	float Q[4];
	int wsp[4];	//tablic wspó³rzêdnych wêz³ów aktualnego elementu
	float pom[4][4];
	float lx, ly;	//wspó³czynniki przewodnoœci termicznej
	float dx, dy;		//szerokoœæ i wysokoœæ elementu
	int o = 0;
	bool B = false;

	//jakaœ zewnêtrzna pêtla do latania po ró¿nych obszarach?
	plik << "Jedziemy!\n";
	//plik << "Jedziemy!\nx   ;   y   ;   dx   ;   dy   ;   obszar\n\n";
	for (int y = 0; y < iley-1; y++)
	{
		for (int x = 0; x < ilex-1; x++)
		{
			o = 0;
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
			M.do_globalnej(M, pom, Q, Qg, wsp);	//dodawanie macierzy lokalnej do globalnej
		}
	}
	plik << "\nDodalo wszystko, co mialo dodac\n";
	plik << "\nQg = : ";
	for (int i = 0; i < ile; i++)
	{
		plik << Qg[i] << " ; ";
	}
	M.brzegowe(M, S, Qg, wb);		//wprowadzanie warunków brzegowych (ustalonej temperatury)
	plik << "\nDodalo warunki brzegowe\n";
	plik.close();
	M.licz(M, Qg, wyniki);		//rozwi¹zywanie uk³adu równañ
	plik.open("Testy.txt", std::ofstream::app);
	plik << "\n\n\nPOLICZYLO!!!!\n\n\nwyniki=\n\n";
	for (int i = 0; i < ile;  i++)plik << wyniki[i] << " ; ";
	plik.close();
}


// funkcja podaj¹ca temperaturê w danym punkcie. ost-numer elementu w ostatnio wyszukiwanym punkcie
float licz::temp(float x, float y, int& ost, std::vector<float> T, Siatka S)
{
	licz L;
	int n1;
	float nx, ny, kx, ky, lokx, loky, w, nex, ney;
	bool czy = true;	//czy kontynuowaæ poszukiwania elementu
	bool X = false;		//zmienna awaryjna, bada prawid³owy przebieg pêtli
	//zamiast zwyk³ego fora pêtla zaczyna poszukiwania od sprawdzenia ostatnio u¿ytego elementu. Nie doda³em obs³ugi b³êdów, wiêc
	//JEŒLI PROGRAM WIESZA SIÊ NA TEJ PÊTLI TO ZNACZY, ¯E WSKAZANY PUNKT JEST POZA GRANICAMI SIATKI
	L.ktory_el (x, y, ost, S, X);
	//Po powy¿szej funkcji wiadomo ju¿, w którym elemencie znajduje siê punkt
	if (X) return -300;
	else
	{
		//ney = ost / (S.kord_x.size() - 1);			//wspó³rzêdne elementu
		//nex = ost % (S.kord_x.size() - 1);
		//1n1 = nex + ney * S.kord_x.size();			//numer lewego dolnego wêz³a
		//n1 = ost + (ost / (S.kord_x.size() - 1));
		ny = ost / S.kord_x.size();					//wspó³rzêdne lewego dolnego wêz³a
		nx = ost % S.kord_x.size();
		kx = (S.kord_x[nx + 1] - S.kord_x[nx]) * 0.5;
		ky = (S.kord_y[ny + 1] - S.kord_y[ny]) * 0.5;		//wspó³czynniki proporcjonalnoœci
		lokx = (x - S.kord_x[nx]) / kx - 1;
		loky = (y - S.kord_y[ny]) / ky - 1;		//lokalne wspó³zêdne (-1;1)
		w = T[ost] * (1 - lokx) * (1 - loky);
		w += T[ost + 1] * (1 + lokx) * (1 - loky);
		w += T[ost + S.kord_x.size()] * (1 - lokx) * (1 + loky);
		w += T[ost + S.kord_x.size() + 1] * (1 + lokx) * (1 + loky);
		w *= 0.25;
		return w;
	}
}

// funkcja zwracaj¹ca numer obszaru pod wskazanymi wspó³rzêdnymi
void licz:: ktory_obszar(float x, float y, int& ost, Siatka S, bool& X, std::vector <Input> obszary)
{
	bool czy = true;	//czy kontynuowaæ poszukiwania elementu
	X = false;		//zmienna awaryjna, bada prawid³owy przebieg pêtli
	//zamiast zwyk³ego fora pêtla zaczyna poszukiwania od sprawdzenia ostatnio u¿ytego elementu.
	//JEŒLI PUNKT NIE NALE¯Y DY ¯ADNEGO OBSZARU, TO X =  TRUE 
	while (czy)
	{
		if (x >= obszary[ost].x1 && x <= obszary[ost].x4 && y >= obszary[ost].y1 && y <= obszary[ost].y4)
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
// funkcja zwracaj¹ca numer lewego dolnego wêz³a elementu pod wskazanymi wspó³rzêdnymi
void licz::ktory_el(float x, float y, int& ost, Siatka S, bool& X)
{
	float nx, ny;
	bool czy = true;	//czy kontynuowaæ poszukiwania elementu
	X = false;		//zmienna awaryjna, bada prawid³owy przebieg pêtli
	//zamiast zwyk³ego fora pêtla zaczyna poszukiwania od sprawdzenia ostatnio u¿ytego elementu.
	//JEŒLI PUNKT NIE NALE¯Y DY ¯ADNEGO ELEMENTU, TO X = TRUE
	while (czy)
	{
		ny = ost / S.kord_x.size();
		nx = ost % S.kord_x.size();
		if (x >= S.kord_x[nx] && x <= S.kord_x[nx + 1] && y >= S.kord_y[ny] && y <= S.kord_y[ny + 1])
		{
			czy = false;
		}
		else
		{
			if (ost == (S.kord_x.size())*(S.kord_y.size())-1)
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
