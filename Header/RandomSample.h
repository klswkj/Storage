#pragma once

#include <cstdlib> // For rand

/**
 * Function: RandomSample(InputIterator inBegin, InputIterator inEnd,
 *                        RandomIterator outBegin, RandomIterator outEnd);
 * ------------------------------------------------------------------------
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
	RandomIterator itr = outBegin;
	for (; itr != outEnd && inBegin != inEnd; ++itr, ++inBegin) { *itr = *inBegin; }

	if (itr != outEnd) { return itr; }

	const size_t numOutputSlots = outEnd - outBegin;

	for (size_t count = numOutputSlots; inBegin != inEnd; ++inBegin, ++count) {
		size_t index = rng() % (count + 1);
		if (index < numOutputSlots) { outBegin[index] = *inBegin; }
	}

	return outEnd;
}

/* Non-generator version just passes in rand to the generator version. */
template <typename InputIterator, typename RandomIterator>
RandomIterator RandomSample(InputIterator inBegin, InputIterator inEnd,
	RandomIterator outBegin, RandomIterator outEnd) 
{
	return RandomSample(inBegin, inEnd, outBegin, outEnd, std::rand);
}
