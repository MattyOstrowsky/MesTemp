#include "pch.h"
#include "Prostokat.h"

void Prostokat::numeruj (int n)
{
	nr = n;
}

void Prostokat::ust_temp(float t1, float t2, float t3, float t4)
{
	T1 = t1;
	T2 = t2;
	T3 = t3;
	T4 = t4;
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
