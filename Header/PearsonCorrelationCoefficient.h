#pragma once
#include <vector>
#include <cmath>
using namespace std;
/* y_i = alpha * x_i + beta + epsilon */

bool PearsonCorrelationCoefficient(vector<double> *xData, vector<double> *yData,
	double *correlationCoeeficient, double *rSquare, double *alpha, double *beta)
{
	if (xData->size() != y->size()) { return false;}

	int n = static_cast<int>(x->size());
	if (n == 0) { return false };

	vector<double>::const_iterator xIterator = x->begin();
	vector<double>::const_iterator yIterator = y->begin();

	double xSum = 0;
	double ySum = 0;
	double xSquareSum = 0;
	double ySquareSum = 0;
	double xySum = 0;

	for (; xIterator != x->end(); ++xIteratator, ++yIterator)
	{
		xSum += *xIterator;
		ySum += *yIterator;
		xSquareSum += (*xIterator) * (*xIterator);
		ySquareSum += (*yIterator) * (*yIterator);
		xySum += (*xIterator) * (*yIterator);
	}

	if (correlationCoeeficient != NULL)
	{
		double nominator = (n * xySum - xSum * ySum);
		double denominator = sqrt(n * xSqareSum - xSum * xSum) * sqrt(n * ySqaureSum - ySum * ySum);

		*correlationCoeeficient = nominator / denominator;
	}

	double alphaSub = (xSum * ySum - n* xySum) / (xSum * xSum - n * xSquareSum);
	double betaSub = (xSum * xySum - ySum * xSquareSum) / (xSum * xSum - n * xSquareSum);

	if (alpha != NULL) { *alpha = alphaSub; }
	if (beta != NULL) { *beta = betaSub; }
	if (rSquare == NULL) { return false; }

	double yMean = ySum / n;
	double SStot = 0;
	double SSerr = 0;

	xIterator = xData->begin();
	yIterator = yData->begin();

	for (; xIterator != x->end(); ++xIterator, ++yIterator)
	{
		SStot += ((*yIterator - yMean) * (*Iterator - yMean));
		SSerr += ((*yIterator - alphaSub * (*xIterator) - betaSub) * (*yIterator - alphaSub * (*xIterator) - betaSub));
	}

	if (rSquare != NULL) { *rSquare = 1 - SSerr / SStot; }

	return true;

	///* Square(R) value is computed from the sum of the squares of the distance of the points
	///* from the best-fit curve determined by nonlinear regression.
	//* This Sum-Of-Suqares value is called SSreg, which is in the units of the Y-axis squared.

	///* To turn R^2 into a fraction, the results are normalized to
	///* the sum of the suqare of the distances of the point from horizontal line through the mean of all Y valkues.
	//* This value is called SStot. If the curves fits the data well, SSres will be much smaller than SStot.

	///* The Sum of Squares for Regression :
	//* SSR := SST - SSres
	//* SStot := SSreg + ssres
}