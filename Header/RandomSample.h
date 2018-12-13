#pragma once
#ifndef RandomSample_Included
#define RandomSample_Included

#include <cstdlib> // For rand

/**
 * Function: RandomSample(InputIterator inBegin, InputIterator inEnd,
 *                        RandomIterator outBegin, RandomIterator outEnd);
 * -------------------------------------------------------------------------
 * Populates the output range [outBegin, outEnd) with a uniform random
 * sample of the elements in the range [inBegin, inEnd).  Internally, this
 * function uses rand to generate random numbers.  If the input range does
 * not contain enough elements, then only some of the values will be filled
 * in and the algorithm will return an iterator to the last element written.
 * If at least outEnd - outBegin elements were written, the return value
 * is outEnd.
 */
template <typename InputIterator, typename RandomIterator>
RandomIterator RandomSample(InputIterator inBegin, InputIterator inEnd,
	RandomIterator outBegin, RandomIterator outEnd);

template <typename InputIterator, typename RandomIterator, typename RandomGenerator>
RandomIterator RandomSample(InputIterator inBegin, InputIterator inEnd,
	RandomIterator outBegin, RandomIterator outEnd,
	RandomGenerator rng);


/* Main implementation uses the parameterized generator. */
template <typename InputIterator, typename RandomIterator, typename RandomGenerator>
RandomIterator RandomSample(InputIterator inBegin, InputIterator inEnd,
	RandomIterator outBegin, RandomIterator outEnd,
	RandomGenerator rng) 
{
	/* Try reading in outEnd - outBegin elements, 
	 * aborting early if they can't be read.
	 */
	RandomIterator itr = outBegin;
	for (; itr != outEnd && inBegin != inEnd; ++itr, ++inBegin) { *itr = *inBegin; }

	/* If we ran out of elements early, report that.  We can detect this by
	* checking whether our advancing iterator hit the end of the output
	* range.
	*/
	if (itr != outEnd) { return itr; }

	/* For simplicity, cache the number of elements in the output range. */
	const size_t numOutputSlots = outEnd - outBegin;

	/* Now apply the main algorithm by reading elements and deciding whether to
	* randomly evict an element or to skip it.
	*/
	for (size_t count = numOutputSlots; inBegin != inEnd; ++inBegin, ++count) {
		size_t index = rng() % (count + 1);
		if (index < numOutputSlots) { outBegin[index] = *inBegin; }
	}

	/* Report that we read everything in by handing back the end of the output
	* range.
	*/
	return outEnd;
}

/* Non-generator version just passes in rand to the generator version. */
template <typename InputIterator, typename RandomIterator>
RandomIterator RandomSample(InputIterator inBegin, InputIterator inEnd,
	RandomIterator outBegin, RandomIterator outEnd) 
{
	return RandomSample(inBegin, inEnd, outBegin, outEnd, std::rand);
}
#endif