#include "pch.h"
#include "licz.h"


// funkcja zarz�dzaj�ca tworzeniem macierzy globalnej i rozwi�zywaniem uk�adu r�wna�
void licz::rozw(std::vector<Prostokat> dane, std::vector<float>& wyniki, float lx, float ly, Siatka S)
{
	//lx i ly powinny by� sk�d� brane- siatka? prostok�t? input???
	int ilex = S.kord_x.size();
	int iley = S.kord_y.size();
	int ile = dane.size();
	int nx, ny;
	std::vector<float>x1 = {};
	std::vector<float>x2 = {};
	std::vector<int>x3 = {};
	std::vector<float> Qg (ile, 0);	//na razie pusty wektor globalny Q
	Macierze M(x1, x2, x3);	//na razie pusta macierz globalna
	float lok[16];
	float Q[4];
	int wsp[4];	//tablic wsp�rz�dnych w�z��w aktualnego elementu
	float pom[4][4];
	
	//jaka� zewn�trzna p�tla do latania po r�nych obszarach?

	for (int i = 0; i < ile; i++)
	{
		ny = i / ilex;
		nx = i % ilex;
		dane[i].lokalna(lx, ly, lok, Q, nx, ny);
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
