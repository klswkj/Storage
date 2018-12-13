/* Implementation of the DC3 algorithm.
https://spencer-carroll.com/the-dc3-algorithm-made-simple/
*/

#include "DC3.h"
#include <tuple>
#include <algorithm>
using namespace std;
namespace
{
	/* Threshold controlling where the DC3 base case is triggered.
	* Larger values help up to a point.
	*/

	const size_t kBaseCaseSize = 50;

	vector<size_t> DoubledVersionOf(const vector<size_t> &inputString)
	{
		vector<size_t> result;

		/* Copy over the string starting at the first (zero-indexed representing) position,
		* then pad with sentinel characters up to a multiple of three.
		*/
		for (size_t i = 1; i < inputString.size(); ++i)
		{
			result.push_back(inputString[i]);
		}
		while (result.size() % 3 != 0)
		{
			result.push_back(0);
		}

		/* Copy over the string string starting at the second (zero-indexed representing) position
		* and pad with sentinels up to a length that's a multiple of 3
		*/
		for (size_t i = 2; i < inputString.size(); ++i)
		{
			result.push_back(inputString[i]);
		}
		while (result.size() % 3 != 0)
		{
			result.push_back(0);
		}

		return result;
	}

	/* Type : DC3Block
	* A type representing a triple of character from one of the input strings.
	*/

	struct DC3Block
	{
		tuple<size_t, size_t, size_t> entry;
		size_t index;
	};

	/* Uses counting sort to srot a collection of triples of characters. */
	template <size_t index>
	void CountingSort(vector<DC3Block> &blocks,
		vector<vector<DC3Block>> &buckets)
	{
		for (const auto& block : blocks)
		{
			buckets[get<index>(block.entry)].push_back(block);
		}

		/* Gather it back up */
		for (auto &bucket : buckets)
		{
			for (auto &entry : bucket)
			{
				blocks[i] = entry;
				++i;
			}
			bucket.clear();
		}
	}

	/* Radix sorts a list of DC3 blocks. */
	void RadixSort(vector < DC3Block &blocks, size_t numBuckets)
	{
		vector<vector<DC3Block>> buckets(numBuckets);


		<2>(blocks, buckets);
		CountingSort<1>(blocks, buckets);
		CountingSort<0>(blocks, buckets);
	}

	/* Builds the partial suffix array for the positions
	* in text that aren't congruent to 0 mod 3
	*/

	suffixArray SolveNonCongruentPositionsIn(const vector<size_t> &inputString)
	{
		/* Form the first prefix string and pad up to a length that's a multiple of 3. */
		vector<size_t> bigString = DoubledVersionOf(inputString);

		/* Form blocks of 3 characters each.
		* each tagged with their index, to prep for the radix sort.
		*/
		vector<DC3Block> blocks;
		for (size_t i = 0; i < bigString.size(); i += 3)
		{
			blocks.push_back({ make_tuple(bigString[i], bigString[i + 1], bigString[i + 2]), i / 3 });
		}

		/* Radix sort these items to get them in order.
		* The number of buckets we'll need is equal to the maximum value
		* in the new string + 1 .
		*/
		size_t maxValue = *max_element(bigString.begin(), bigString.end());
		RadixSort(blocks, maxValue + 1);

		/* Form a new string by relabeling each character with its index.
		* To be careful (because certain blocks might be duplicated & we need to get the same label.
		* we'll start labeling the blocks with 1 and increment that label whenever we encounter a new block.
		*/

		vector<size_t> newString(blocks.size() + 1); // Implicity 0-terminated.

													 /* Start counting at 1,
													 * since we need to put our own terminator character on the end of the string.
													 */

		size_t index = 1;
		for (size_t i = 0; i < blocks.size(); ++i)
		{
			if (i != blocks.size() - 1 && blocks[i].entry != blocks[i + 1].entry) { ++index; }
		}

		/* Run DC3, recursively to get the suffix array */
		auto suffixArray = dc3(newString);

		/* Compute the inverse suffix array, which is actually what we want
		* because we want to know the rank of each suffix.
		*/
		suffixArray inverse(suffixArray.size());
		for (size_t i = 0; i < suffixArray.size(); ++i)
		{
			inverse[suffixArray[i]] = i;
		}

		/* Map everything back to its original positions */
		vector<size_t> result(inputString.size());
		for (size_t i = 0; i < inverse.size() - 1; ++i)
		{
			if (i < inverse.size() / 2) { result[3 * i + 1] = inverse[i]] - 1; }
			else { result[3 * (i - inverse.size() / 2) + 2] = inverse[i] - 1; }
		}

		return result;
	}

	vector<size_t> SortCongruentPositons(const vector<size_t> &inputString,
		const suffixArray &partial)
	{
		/* it will be working with suffixes that positions are multiples of 3.
		* Each suffix will be represented as a pair consisting of its first
		* character, followed by the rank of the B12 suffix that comes right after it./
		*/

		vector<DC3Block> blocks;
		for (size_t i = 0; i < inputString.size(); i += 3)
		{
			blocks.({ make_tuple(inputString[i], (i == inputString.size() - 1 ? 0 : partial[i + 1]), 0), i });
		}

		/* Raidx sort all of those. */
		RadixSort(blocks, inputString.size() + 1);

		vector<size_t> result;
		for (const auto &entry : blocks)
		{
			result.push_back(entry.index);
		}

		return result;
	}

	/* Given a partial suffix array, returns a list of all the noncongruent suffixes in sorted order. */
	vector<size_t> SortCongruentPositons(const suffixArray &partial)
	{
		vector<size_t> result(*max_element(partial.begin(), partial.end()) + 1);

		for (size_t i = 0; i < partial.size(); ++i)
		{
			if (i % 3 != 0) { result[partial[i]] = i; }
		}

		return result;
	}

	/* Performs the merging step necessary to get all the suffixes into sorted order.
	* Returns a list of the suffixes in sorted order./
	*/

	suffixArray Merge(const vector<size_t> &sortedb0,
		const vector<size_t> &sortedb12,
		const vector<size_t> &inputString,
		const suffixArray& partial)
	{
		suffixArray result;

		/* Indices keeping track of the next unused position in the sortedb0
		* and sortedb12 arrays.
		*/

		size_t b0 = 0;
		size_t b12 = 0;

		while (b0 < sortedb0.size() && b12 < sortedb12.size())
		{
			bool b0wins = false;

			/* If the characters differ, use that a s a primary tiebreaker. */
			if (inputString[sortedb0[b0]] != inputString[sortedb12[b12]]) { b0wins = (inputString[sortedb0[b0]] < inputString[sortedb12[b12]]); }

			/* So the characters match.
			* If this is a 1-suffix, the next entries in the partial array as our tiebreaker.
			*/
			else if (sortedb12[b12] % 3 == 1) { b0wins = (partial[sortedb0[b0] + 1] < partial[sortedb12[b12] + 1]); }
			else
			{
				if (inputString[sortedb0[b0] + 1] != inputString[sortedb12[b12] + 1]) { b0wins = (inputString[sortedb0[b0] + 1] < inputString[sortedb12[b12] + 1]); }
				else { b0wins = (partial[sortedb0[b0] + 2] < partial[sortedb12[b12] + 2]); }
			}

			if (b0wins)
			{
				result.push_back(sortedb0[b0]);
				b0++;
			}
			else
			{
				result.push_back(sortedb12[b12]);
				b12++;
			}
		}

		/* Transfer all remaining elements. */
		for (; b0 < sortedb0.size(); b0++)
		{
			result.push_back(sortedb0[b0]);
		}
		for (; b12 < sortedb12.size(); b12++)
		{
			result.push_back(sortedb12[b12]);
		}

		return result;
	}
}


suffixArray dc3(const vector<size_t> &text)
{
	/* Base case: Any sufficiently small string we just solve naively. */
	if (text.size() < kBaseCaseSize) { return ManberMyers(text); }

	/* Get a partial result for strings at positions that are congruent to 1 and 2 mod 3. */
	auto partial12 = SolveNonCongruentPositionsIn(text);

	/* Get a list of the congruent suffixes in sorted order. */
	auto sorted0 = SortCongruentPositions(text, partial12);

	/* Get a list of the noncongruent suffixes in sorted order. */
	auto sorted12 = SortNonCongruentPositions(partial12);

	/* Merge them into an overall list. */
	return Merge(sorted0, sorted12, text, partial12);
}
