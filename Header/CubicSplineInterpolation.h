#pragma once
#include <vector>
#include <algorithm>
using namespace std;

double Square(double x)
{
	return x*x;
}

double Cubic(double x)
{
	return x*x;
}

bool CubicSpline(vector<double> *xSeries, vector<double> *ySeries,
	vector <double> *destX, vector<double> *destY)
{
	int n = min((int)xSeries->size(), (int)ySeries->size()) - 1;

	double *h = new double[n + 1];
	double *alpha = new double[n + 1];

	for (int i = 0; i <= n - 1; ++i)
	{
		h[i] = (*xSeries)[i + 1] - (*xSeries)[i];
	}

	for (int i = 1; i <= n - 1; ++i)
	{
		alpha[i] = 3 * ((*ySeries)[i + 1] - (*ySeries)[i]) / h[i] - 3 * ((*ySeries)[i] - (*ySeries)[i - 1]) / h[i - 1];
	}

	double *l = new double[n + 1];
	double *u = new double[n + 1];
	double *z = new double[n + 1];
	double *b = new double[n + 1];
	double *c = new double[n + 1];
	double *d = new double[n + 1];

	l[0] = 1;	u[0] = 0; z[0] = 0;

	for (int i = 1; i <= n - 1; ++i)
	{
		l[i] = 2 * ((*xSeries)[i + 1] - (*xSeries)[i - 1]) - h[i - 1] * u[i - 1];
		u[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}

	l[n] = 1;	z[n] = 0; c[n] = 0;

	for (int i = n - 1; i >= 0; --i )
	{
		c[i] = z[i] - u[i] * c[i + 1];
		b[i] = ((*ySeries)[i + 1] - (*ySeries)[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
	}

	for (int i = 0; i <= n - 2; ++i)
	{
		double x = (*xSeries)[i];
		double inc = ((*xSeries)[i + 1] - (*xSeries)[i]) * 0.1;

		for (; x < (*xSeries)[i + 1]; x += inc)
		{
			double xOffset = x - (*xSeries)[i];
			double sX = (*ySeries)[i] + b[i] * xOffset + c[i] * Square(xOffset) + d[i] * Cubic(xOffset);

			if (destX != NULL)
			{
				destX->push_back(x);
			}

			if (destY != NULL)
			{
				destY->push_back(sX);
			}
		}
	}

	delete[] h;
	delete[] alpha;
	delete[] l;
	delete[] u;
	delete[] z;
	delete[] b;
	delete[] c;
	delete[] d;

	return true;
}
