#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<int> Copy(const vector<int>& source, int *index, int indexLength)
{
	vector<int> result;
	for (int i = 0; i < indexLength; ++i)
	{
		result.push_back(source.operator[](index[i]));
	}

	return result;
}

bool ForwardIndex(int *index, int indexLength, int maxLength)
{
	for (int i = indexLength - 1; i >= 0; --i)
	{
		if (index[i] == maxLength - indexLength + i) { continue; }
		else
		{
			index[i] = index[i] + 1;
			for (int j = i + 1; j < indexLength; ++j)
			{
				index[j] = index[j - 1] + 1;
			}
			return true;
		}
	}

	return false;
}


bool Ksubset(const vector<int>& sourceSet, int k, vector<vector<int> > *dest)
{
	if (sourceSet.empty() == true) { return false; }

	int sourceLength = static_cast<int> (sourceSet.size());
	if (k <= 0 || k > sourceLength) { return false; }
	if (sourceLength == k)
	{
		dest->push_back(sourceSet);
		return true;
	}

	const int& maxLength = sourceLength;
	int *index = new int[k];

	for (int i = 0; i < k; ++i)
	{
		index[i] = i;
	}

	while (true)
	{
		vector<int> subset = Copy(sourceSet, index, k);
		dest->push_back(subset);
		if (ForwardIndex(index, k, maxLength) == false) { break; }
	}

	delete index;
	return true;
}

bool Allsubset(const vector<int>& sourceSet, vector<vector<int> > *dest)
{
	int length = static_cast<int> (sourceSet.size());

	for (int i = 1; i <= length; ++i)
	{
		if (Ksubset(sourceSet, i, dest) == false) { return false; }
	}

	return true;
}
