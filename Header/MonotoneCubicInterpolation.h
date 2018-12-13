#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

double ReturnH00(double t)
{
	return (2 * t*t*t) - (3 * t*t) + 1;
}

double ReturnH10(double t)
{
	return t * (1 - t) * (1 - t);
}

double ReturnH01(double t)
{
	return t * t * (3 - 2 * t);
}

double ReturnH11(double t)
{
	return t * t * (t - 1);
}

bool MonotoneCubicHermiteSpline(int timeLimit, const vector<double> xSrc, const vector<double> ySrc,
	vector<double> *destX, vector<double> *destY)
{
	constexpr double epsilon = numeric_limits<double>::epsilon();
	int n = static_cast<int>(xSrc.size());

	double *m = new double[n];
	m[0] = (ySrc[1] - ySrc[0]) / (xSrc[1] - xSrc[0]);
	m[n - 1] = (ySrc[n - 1] - ySrc[n - 2]) / (xSrc[n - 1] - xSrc[n - 2]);
	for (int k = 1; k < n - 1; ++k)
	{
		m[k] = (ySrc[k] - ySrc[k - 1]) / (2 * (xSrc[k] - xSrc[k - 1])) +
			(ySrc[k + 1] - ySrc[k]) / (2 * (xSrc[k + 1] - xSrc[k]));
	}

	for (int k = 0; k < n - 1; ++k)
	{
		double deltaK = (ySrc[k + 1] - ySrc[k]) / (xSrc[k + 1] - xSrc[k]);
		if (std::abs(deltaK) <= epsilon)
		{
			m[k] = 0;
			m[k + 1] = 0;
		}
		else
		{
			double ak = m[k] / deltaK;
			double bk = m[k + 1] / deltaK;
			if (ak*bk + bk*bk > 9) /// a circle of radius 3
			{
				m[k] = 3 / (sqrt((ak*ak) + (bk * bk))) * ak * deltaK;
				m[k + 1] = 3 / (sqrt((ak*ak) + (bk * bk))) * bk * deltaK;
			}
		}
	}

	for (int k = 0; k < n - 1; ++k)
	{
		double curX = static_cast<double>((static_cast<int>(floor(0.5 + xSrc[k])))); /// rounding off xSrc[k] ( using floor in cmath)
		double nextX = static_cast<double>((static_cast<int>(floor(xSrc[k + 1])))); /// only rounding down
		double curY = ySrc[k];
		double nextY = ySrc[k + 1];
		double h = nextX - curX;
		double x{ 0 };
		double inc = (nextX - curX) * 0.1;

		for (x = curX; x < nextX; x += inc)
		{
			if (x > timeLimit) { break; }
			double t = (x - curX) / h;
			if (destX != NULL)
			{
				destX->push_back(x);
			}

			double y = curY * ReturnH00(t) +
				h * m[k] * ReturnH10(t) +
				nextY * ReturnH01(t) +
				h * m[k + 1] * ReturnH11(t);

			destY->push_back(y);
		}
	}

	delete m;

	return true;
}
