#pragma once
#include "stdafx.h"

struct CompressedFrame 
{
	//Normalized key time(0(0.0) - 65535(1.0))
	uint16_t keyTime = 0;
	uint16_t jointIndex = 0;
	// Payload, which can be a quatized 3d vector or a quantized quaternion
	// depending on what type of channel this data belongs to
	uint16_t v[3];

	ChannelType GetChannelType() const 
	{
		// Most significant two bits of this 16bit index contains channel type info.
		return static_cast<ChannelType>((jointIndex & (0xc000)) >> 14); //bitmask
	    // Using bit-shift to determine ChannelType

	void SetChannelType(ChannelType type) 
	{
		jointIndex |= (static_cast<uint16_t>(type) << 14);
	}

	std::uint16_t GetJointIndex() const 
	{
		return jointIndex & 0x3fff;m // 0x3fff ""
	}
};