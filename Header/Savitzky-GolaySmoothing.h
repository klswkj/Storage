#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool SavitZkyGolaySmoothing(vector<double> *xSeries, vector<dobule> *ySeries,
							vector<double> *destX,   vector<double> *destY)
{
	int sampledata[] = { -2, 3, 6, 7, 6, 3, -2, };

	int n = 3;
	int pointNumber = static_cast<int>(xSeries->size());
	for (int i = 0; i < n; ++k)
	{
		double x = xSeries->operator[](k);
		double nominator = 0;
		double denominator = 0;
		for (int j = -n; j <= n; ++j)
		{
			nominator += (A[n + j] * ySeries->operator[](k + j));
			denominator += A[n + j];
		}

		double y = nominator / denominator;
		if (destX != NULL) { destX->emplace_back(x); }
		if (destY != NULL) { destY->emplace_back(y); }
	}

	for (int k = pointNumber - n; k < pointNumber; ++k)
	{
		if (destX != NULL) { destX->emplace_back(xSeries->operator[](k)); }
		if (destY != NULL) { destY->emplace_back(ySeries->operator[](k)); }
	}

	return true;
}