#pragma once

#include "ManberMyers.h"

/* Computes a suffix array using the DC3 algorithm. As with the Manber-Myers
* algorithm, this implementation assumes that the input text string has been
* suffixed with a sentinel and had each of its characters remapped to its rank
* among all characters.
*/
SuffixArray dc3(const std::vector<std::size_t> &text);
