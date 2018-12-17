// Compute a length of a spline segment by using 5-point Legendre-Gauss quadrature
// https://en.wikipedia.org/wiki/Gaussian_quadrature
#include "stdafx.h"

float compute_spline_length(vector3f const& start, vector3f const& start_tangent,
                            vector3f const& end, vector3f const& end_tangent)
{
       // Cubic Hermite spline derivative coeffcients
       vector3f const c0 = start_tangent;
       vector3f const c1 = 6.f * (end - start) - 4.f * start_tangent - 2.f * end_tangent;
       vector3f const c2 = 6.f * (start - end) + 3.f * (start_tangent + end_tangent);
       auto const evaluate_derivative = [c0, c1, c2](float t) -> vector3f { return c0 + t * (c1 + t * c2); };
       
       struct GaussLengendreCoefficient
       {
              float abscissa; // xi
              float weight;   // wi
       };
       static constexpr GaussLengendreCoefficient gauss_lengendre_coefficients[] =
       {
              { 0.0f, 0.5688889f },
              { -0.5384693f, 0.47862867f },
              { 0.5384693f, 0.47862867f },
              { -0.90617985f, 0.23692688f },
              { 0.90617985f, 0.23692688f }
       };
       
       float length = 0.f;
       for (auto coefficient : gauss_lengendre_coefficients)
       {
              float const t = 0.5f * (1.f + coefficient.abscissa); // This and the final (0.5 *) below are needed for a change of interval to [0, 1] from [-1, 1]
              length += evaluate_derivative(t).Size() * coefficient.weight;
       }
       return 0.5f * length;
}
