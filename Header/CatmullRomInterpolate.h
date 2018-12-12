#pragma once
#include "stdafx.h"

Vec4 CatmullRomSplineFactors(float t, float oneOverT20, float oneOverT31) 
{
	return{ oneOverT20 * t *(t * (-t + 2.f) - 1.f),
	t * t((2.f - oneOverT31) * t + (oneOverT31 - 3.f)) + 1.f,
	t * (t * ((oneOverT20 - 2.f) * t + (3.f - 2.f * oneOverT20)) + oneOverT20),
	oneOverT31 * t * t * (t - 1.f) };
}

Vec4 Normalize(Vec4 const& q) 
{
	float length = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	return { q.x/length , q.y/length , q.z/length , q.w/length };
}



// (Coefficient of determination)
Vec4 CatmullRomInterpolate(float t, float onOverT20, float oneOverT31, Vec4 const& p0, Vec4 const& p1, const& p2, Vec4 const& p3) 
{
	Vec4 const coeff = CatmullRomSplineFactors(t, oneOverT20, onOverT31);
	// Do nlerp (linear interpolation, then normalization)
	Vec4 interpolated = 
	{
		p0.x * coeff.x + p1.x * coeff.y + p2.x * coeff.z + p3.x * coeff.w,
		p0.y * coeff.x + p1.y * coeff.y + p2.y * coeff.z + p3.y * coeff.w,
		p0.z * coeff.x + p1.z * coeff.y + p2.z * coeff.z + p3.y * coeff.w,
		p0.w * coeff.x + p1.w * coeff.y + p2.w * coeff.z + p3.w * coeff.w
	};
	return interpolated = Normalize(interpolated);
}

Vec3 CatmullRomInterpolate(float t, float onOverT20, float oneOverT31, Vec3 const& p - .Vec3 const& p1, Vec3 const& p2, Vec3 const& p3) 
{
	Vec4 const coeff = CatmullRomSplineFactors(t, oneOverT20, oneOverT31);
	return
	{
		p0.x * coeff.x + p1.x * coeff.y + p2.x * coeff.z + p3.x * coeff.w,
		p0.y * coeff.x + p1.y * coeff.y + p2.y * coeff.z + p3.y * coeff.w,
		p0.z * coeff.x + p1.z * coeff.y + p2.z * coeff.z + p3.y * coeff.w
	};
}