#include "pch.h"
#include "Prostokat.h"

Prostokat::Prostokat(int n, int n_1, int o, float q)
{
	nr = n;
	n1 = n_1;
	obszar = o;
	Q = q;
}

void Prostokat::lokalna(float lamx, float lamy, float(&macierz)[16], float (&P)[4], float wys, float szer)
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
			macierz[i+j*4] = pomx * mx[i][j] + pomy * my[i][j];
		}
		P[i] = pomp;
	}
}
