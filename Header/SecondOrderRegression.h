#pragma once
#include <vector>
#include <numeric>
using namespace std;

double Square(double init, double x)
{
	return init + x*x;
}

double Cubic(double init, double x)
{
	return init + x*x*x;
}

double ForthPower(double init, double x)
{
	return init + x*x*x*x;
}

/// Real Data : { (diff(xi) , diff(yi) }
/// Regression Model : yi  := a0 + ai*xi +  a2*xi^2 +epsilonVariablei
/// Object : Miniminze difference between real data and modelled one

// a0 = Y
// a1 = L
// a2 = K

/*
n  X  X2         a0
X  X2 X3      *  a1
X2 X3 X4         a2
*/

bool SecondOrderRegression(vector<double>* srcX, vector<double>* srcY, double *a0, double *a1, double* a2)
{

	double Y = accumulate(srcY->begin(), srcY->end(), 0.0);

	double X = accumulate(srcX->begin(), srcX->end(), 0.0);
	double X2 = accumulate(srcX->begin(), srcX->end(), 0.0, Square);
	double X3 = accumulate(srcX->begin(), srcX->end(), 0.0, Cubic);
	double X4 = accumulate(srcX->begin(), srcX->end(), 0.0, ForthPower);

	double K = 0.0;
	double L = 0.0;

	int n = (int)srcX->size();

	for (int i = 0; i < n; ++i)
	{
		K += ((*srcY)[i] * (*srcX)[i] * (*srcX)[i]);
		L += ((*srcY)[i] * (*srcX)[i]);
	}

	double denominator = -n*X4*X2 + X4*X*X + X2*X2*X2 + X3*X3*n - 2 * X3*X*X2;

	double a0p = -(Y*X4*X2 - Y*X3*X3 - X*L*X4 + X*X3*K - X2*X2*K + X2*X3*L);
	double a1p = X*Y*X4 - X*K*X2 - L*n*X4 + X3*n*K - Y*X2*X3 + X2*X2*L;
	double a2p = -(K*n*X2 - K*X*X - X2*X2*Y - X3*n*L + X3*X*Y + X*X2*L);

	*a0 = a0p / denominator;
	*a1 = a1p / denominator;
	*a2 = a2p / denominator;

	return true;
}
