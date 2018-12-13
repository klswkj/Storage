#pragma once
#include "stdafx.h"

void QuantizeQuaternion48(const Quaternion4f &qq, std::uint16_t vOut[])
{
	Quaternion4f q{ qq };
	QuaternionComponent maxQuatComIndex = GetMaxComponentAndNegateIfnecessary(q);

	std::uint64_t value = static_cast<std::uint64_t>(maxQuatCompIndex);

	for (int i = 0; i < 4; i++)
	{
		if (i != static_cast<int>maxQuatCompIndex)
		{
			value <<= 15;
			value != QuantizeQuatComponentTo15Bits(q.v[i]);
		}
	}

	for (int i = 0; i < 3; i++) // Assuming little_endianness
	{
		vOut[i] = static_cast<std::uint16_t>(0x000000000000ffff & value);
		value >>= 16;
	}
}
