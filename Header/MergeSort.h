#pragma once
#ifndef Mergesort_Included
#define Mergesort_Included

#include <vector>
#include <functional>

/**
* Function: Mergesort(vector<T> &elems);
* Usage: Mergesort(myVector);
* ---------------------------------------------------
* Applies the Mergesort algorithm to sort an array in
* ascending order.
*/
template <typename T>
void Mergesort(std::vector<T> &elems);

/**
* Function: Mergesort(vector<T> &elems, Comparator comp);
* Usage: Mergesort(myVector, std::greater<int>());
* ---------------------------------------------------
* Applies the Mergesort algorithm to sort an array in
* ascending order according to the specified
* comparison object.  The comparator comp should take
* in two objects of type T and return true if the first
* argument is strictly less than the second.
*/
template <typename T, typename Comparator>
void Mergesort(std::vector<T> &elems, Comparator comp);

/* We store all of the helper functions in this detail namespace to avoid cluttering
* the default namespace with implementation details.
*/
namespace detail 
{
	/* Given vectors 'one' and 'two' sorted in ascending order according to comparator
	* comp, returns the sorted sequence formed by merging the two sequences.
	*/
	template <typename T, typename Comparator>
	std::vector<T> Merge(const std::vector<T> &one, const std::vector<T> &two, Comparator comp) 
	{
		/* We will maintain two indices into the sorted vectors corresponding to
		* where the next unchosen element of each list is.  Whenever we pick
		* one of the elements from the list, we'll bump its corresponding index
		* up by one.
		*/
		size_t onePos = 0, twoPos = 0;

		/* The resulting vector. */
		std::vector<T> result;

		/* For efficiency's sake, reserve space in the result vector to hold all of
		 * the elements in the two vectors.
		 */
		result.reserve(one.size() + two.size());

		/* The main loop of this algorithm continuously polls the first and second
		 * list for the next value, putting the smaller of the two into the output
		 * list.
		 */
		while (onePos < one.size() && twoPos < two.size()) 
		{
			/* If the first element of list one is less than the first element of
			 * list two, put it into the output sequence.
			 */
			if (comp(one[onePos], two[twoPos])) 
			{
				result.push_back(one[onePos]);
				++onePos;
			}
			/* Otherwise, either the two are equal or the second element is smaller
			 * than the first.  In either case, put the first element of the second
			 * sequence into the result.
			 */
			else 
			{
				result.push_back(two[twoPos]);
				++twoPos;
			}
		}

		for (; onePos < one.size(); ++onePos) { result.push_back(one[onePos]); }
		for (; twoPos < two.size(); ++twoPos) { result.push_back(two[twoPos]); }

		return result;
	}
}

/* Implementation of Mergesort itself. */
template <typename T, typename Comparator>
void Mergesort(std::vector<T> &elems, Comparator comp) 
{
	if (elems.size() < 2) { return; }

	/* Break the list into a left and right sublist. */
	std::vector<T> left, right;

	/* The left half are elements [0, elems.size() / 2). */
	for (size_t i = 0; i < elems.size() / 2; ++i) { left.push_back(elems[i]); }

	/* The right half are the elements [elems.size() / 2, elems.size()). */
	for (size_t i = elems.size() / 2; i < elems.size(); ++i) { right.push_back(elems[i]); }

	/* Merge sort each half. */
	Mergesort(left, comp);
	Mergesort(right, comp);

	/* Merge the two halves together. */
	elems = detail::Merge(left, right, comp);
}

/* The Mergesort implementation that does not require a comparator is implemented
* in terms of the Mergesort that does use a comparator by passing in std::less<T>.
*/
template <typename T>
void Mergesort(std::vector<T>& elems) 
{
	Mergesort(elems, std::less<T>());
}
#endif