#pragma once
/*Implementation of the DC3 algorithm.
https://en.wikipedia.org/wiki/Interpolation_search
*/

#include <iterator> // For iterator_traits

/**
 * Function: InterpolationSearch(RandomIterator begin, RandomIterator end,
 *                               Element elem);
 * ------------------------------------------------------------------------
 * Performs interpolation search on the sorted range [begin, end).  It is
 * assumed that this range consists of finite integral values and that the
 * input is sorted in ascending order.  Returns whether the element was
 * located.
 */
template <typename RandomIterator, typename Element>
bool InterpolationSearch(RandomIterator begin, 
	RandomIterator end,
	Element elem)
{
	/* Get a type holding the distance between iterators in the range. */
	typedef typename std::iterator_traits<RandomIterator>::difference_type diffT;

	/* Exception case */
	if (begin == end) { return false; }

	/* Continue loop.
	 */
	while (*begin <= elem && elem <= *(end - 1) && begin != end) 
	{
		/* Interpolate between the endpoints to guess where the element should lie.
		 */
		const double interpolation = (double(elem) - *begin) / (double(*(end - 1)) - double(*begin));

		/* Scale this position to an index by multiplying by the number of elements
		 * in the range by the fraction up to search.
		 */
		RandomIterator mid = begin + diffT(interpolation * (double(end - begin) - 1));

		/* Apply standard binary search logic */
		if (*mid == elem) { return true; }
		else if (*mid < elem) { begin = mid + 1; }
		else { end = mid; }
	}
	/* Fail this question. */
	return false;
}
