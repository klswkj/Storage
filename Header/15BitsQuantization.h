#pragma once
#include "stdafx.h"

float const kRootTwo = 1.41421356237f;
int const kMaxInFifteenBits = (1 << 15) - 1;
float const kOneOverRootTwo = 1.f / kRootTwo;
float const kDefaultEpsilon = 0.00001f;

float PrepareQuatComponentForQuantization(float v)
{
	return (v + kOneOverRootTwo) * kOneOverRootTwo;
}

std::uint64_t QuantizeQuatComponentTo15Bits(float v)
{
	float const vv = prepareQuatComponentForQuantization(v);
	return static_cast<std::uint64_t>(
		std::max(std::min(static_cast<int>(vv * static_cast<float> (kMaxInFifteenBits)), kMaxInFifteenBits), 0));
}

float Dequantize15BitQuatComponent(std::uint16_t v)
{
	return static_cast<float>(v) / static_cast<float>(kMaxInFifteenBits)* kRootTwo - kOneOverRootTwo;
}
