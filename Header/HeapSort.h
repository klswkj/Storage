#pragma once
#ifndef Heapsort_Included
#define Heapsort_Included

#include <iterator>
#include <functional>
#include <algorithm>

/**
 * Function: Heapsort(RandomIterator begin, RandomIterator end);
 * Usage: HeapSort(v.begin(), v.end());
 * -------------------------------------------------------------
 *  Sorts the elements in the range [begin, end) into ascending
 *  order using the heapsort algorithm.
 */
template <typename RandomIterator>
void Heapsort(RandomIterator begin, RandomIterator end);

/**
 * Function: Heapsort(RandomIterator begin, RandomIterator end,
 *                    Comparator comp);
 * Usage: HeapSort(v.begin(), v.end(), comp);
 * -------------------------------------------------------------
 * Sorts the elements in the range [begin, end) into ascending
 * order using the heapsort algorithm.  The elements are compared
 * using the comparator comp, which should be a strict weak
 * ordering.
 */
template <typename RandomIterator, typename Comparator>
void Heapsort(RandomIterator begin, 
	RandomIterator end,
	Comparator comp);

namespace heapsort_detail 
{
	/**
	* Function: HeapJoin(RandomIterator begin, RandomIterator heapStart,
	*                    RandomIterator end, Comparator comp);
	* -----------------------------------------------------------------
	* Given a range of elements [begin, end) and a suffix [heapStart, end)
	* that represents two max-heaps with the element to join them at the
	* top, applies the heap join algorithm to rearrange the elements of
	* [heapStart, end) such that the result is a max-heap according to
	* comp.  The reason for also passing in the argument begin defining
	* the beginning of the heap is so that it is possible to compute
	* the positions of the children of each node in the sequence by
	* using the absolute position in the sequence.
	*/

	template <typename RandomIterator, typename Comparator>
	void HeapJoin(RandomIterator begin, 
		RandomIterator heapStart,
		RandomIterator end, 
		Comparator comp) 
	{
		/* This type represents "the distance between two RandomIterators."*/
		typedef typename std::iterator_traits<RandomIterator>::difference_type diff_t;

		/* Cache the number of elements in the range. */
		const diff_t kNumElems = distance(begin, end);

		/* The initial position of the max element is at the top of the
		 * heap, which is at the index given by the offset of heapStart
		 * into the range starting at begin.
		 */
		diff_t position = distance(begin, heapStart);

		/* Iterate until we have no children.  The first child of node i
		 * is at position 2 * (i + 1) - 1 = 2 * i + 1, and the second
		 * at 2 * (i + 1) + 1 - 1 = 2 * i + 2.
		 */
		while (2 * position + 1 < kNumElems) 
		{
			/* Get the index of the child we will compare to.  This defaults to
			* the first child, but if there are two children becomes the bigger
			* of the two.
			*/
			diff_t compareIndex = 2 * position + 1;

			/* If two children exist.
			 * we only change the compare index if the second child is bigger.
			 */
			if (2 * position + 2 < kNumElems &&
				comp(begin[2 * position + 1], begin[2 * position + 2]))
			{ compareIndex = 2 * position + 2; }

			/* If we're bigger than the bigger child, we're done. */
			if (comp(begin[compareIndex], begin[position])) { break; }

			/* Otherwise, swap with the child and continue. */
			std::swap(begin[compareIndex], begin[position]);
			position = compareIndex;
		}
	}
}

/* The actual Heapsort implementation is rather straightforward - we just keep
 * HeapInserting until we get everything, then repeatedly HeapRemove the
 * max element.
 */
template <typename RandomIterator, typename Comparator>
void Heapsort(RandomIterator begin, RandomIterator end, Comparator comp) 
{
	/* If the range is empty or a singleton, there is nothing to do. */
	if (begin == end || begin + 1 == end) { return; }

	/* Heapify the range. */
	for (RandomIterator itr = end; itr != begin; --itr)
	{
		heapsort_detail::HeapJoin(begin, itr - 1, end, comp);
	}

	/* We continuously move the last element
	 * of the heap into the last open position, 
	 * reassemble balance by bubbling down the last element of the heap.
	 */
	for (RandomIterator itr = end - 1; itr != begin; --itr) 
	{
		std::iter_swap(begin, itr);
		heapsort_detail::HeapJoin(begin, begin, itr, comp);
	}
}

/* The default comparator version of Heapsort just uses the default
 * comparator on elements.
 */
template <typename RandomIterator>
void Heapsort(RandomIterator begin, RandomIterator end) 
{
	Heapsort(begin, end,
		std::less<typename std::iterator_traits<RandomIterator>::value_type>());
}

#endif