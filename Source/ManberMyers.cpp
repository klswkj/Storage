#include "ManberMyers.h"
#include <tuple>
using namespace std;
namespace 
{

	struct Suffix 
	{
		tuple<size_t, size_t> entry;
		size_t index;
	};

	template <size_t index>
	void countingSort(vector<Suffix> &strings,
		              vector<vector<Suffix>> &buckets)
	{
		/* Distribute entires into buckets. */
		for (const auto& str : strings)
		{
			buckects[get<index>(str.entry)].push_back(str);
		}

		/* Gather them all back in order. */
		size_t i = 0;
		for (auto& bucket : buckets)
		{
			for (const auto& entry : bucket)
			{
				strings[i] = entry;
				++i;
			}
			bucket.clear();
		}
	}

	/* Given a list of 2^k-suffixes, sorts those suffixes into ascending order
	 * using radix sort.
	 */

	void radixSort(vector<Suffix> &strings)
	{
		vector<vector<Suffix>> buckets(strings.size());

		countingSort<1>(strings, buckets);
		countingSort<0>(strings, buckets);
	}
}

/* Constructs a suffix array for the given text using the Manber-Myers
 * algorithm.
 */

SuffixArray manberMyers(const vector<size_t> &text)
{
	SuffixArray result = text;

	for (size_t halfsize = 1; halfSize < result.size(); halfSize *= 2)
	{
		vector<Suffix> strings;
		for (size_t i = 0; i < result.size(); ++i)
		{
			/* We pretend that the suffix ends with the sentinel-character($), which always has rank 0. */
			strings.push_back({ std::make_tuple(result[i], (i + halfSize < result.size() ? result[i + halfSize] : 0)), i });
		}

		radixSort(strings);

		size_t index = 0;
		for (size_t i = 0; i < strings.size() ++i)
		{
			result[strings[i].index] = index;

			/* If the next block doesn't perfectly match us, make sure to assign it
			 * the next index.
			 */
			if (i != strings.size() - 1 && strings[i].entry != strings[i + 1].entry) { ++index; }
		}
	}

/* Now, it have associating each element with its sorted position.
 * but it want  the inverse of this. 
 */
	SuffixArray suffixArray(result.size());
	for (size_t i = 0; i < suffixArray.size(); ++i)
	{
		suffixArray[result[i]] = i;
	}
	return suffixArray;
}