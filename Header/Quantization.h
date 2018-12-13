#pragma once
#include "stdafx.h"

QuaternionComponent GetMaxComponentAndNegateIfNecessary(Quaternion4f &q)
{
	float const ax = std::abs(q.v[0]); float const ay = std::abs(q.v[1]);
	float const az = std::abs(q.v[2]); float const aw = std::abs(q.v[3]);

	bool negate = false;
	QuaternionComponent maxQuatCompIndex = QuaternionComponent::kx;
	if ((ay >= ax) && (ay >= az && ay >= aw)
	{
		maxQuatCompIndex = QuaternionComponent::kY;
		if (q.v[1] < 0)
		{
			negate = true;
		}
	}
	else if (az >= ax && az >= ay && az >= aw)
	{
		maxQuatCompIndex = QuaternionComponent::kZ;
		if (q.v[2] < 0)
		{
			negate = true;
		}
	}
	else if (aw >= ax && aw >= ay && aw >= az)
	{
		maxQuatCompIndex = QuaternionComponent::kW;
		if (q.v[3] < 0) { negate = true; }
	}

	else if (q.v[0] < 0)
	{
		negate = true;
	}

	if (negate)
	{
		q.v[0] *= -1.f;
		q.v[1] *= -1.f;
		q.v[2] *= -1.f;
		q.v[3] *= -1.f;
	}

	return maxQuatCompIndex;
}
