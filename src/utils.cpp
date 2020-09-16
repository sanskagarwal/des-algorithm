#include <vector>
#include <string>
#include <algorithm>

#include "utils.h"
#include "hex_maps.h"

namespace des {
std::vector<int> hex_str_to_binary(std::string s) {
	int n = s.length();
	std::vector<int> bin;
	for (int i = 0; i < n; i++) {
		int val = hex_char_to_int.at(s[i]);
		std::vector<int> temp = int_to_binary(val, 4);
		bin.insert(bin.end(), temp.begin(), temp.end());
	}

	return bin;
}

std::vector<int> int_to_binary(int num, int size) {
	if (num >= (1 << size))
		throw "Number exceeds the given size";

	std::vector<int> bin(size, 0);
	int i = 0;
	while (num) {
		bin[i] = (num % 2 == 0) ? 0 : 1;
		num /= 2;
		i++;
	}

	std::reverse(bin.begin(), bin.end());
	return bin;
}

std::vector<int> circular_shift(const std::vector<int> &v, int times) {
	int n = v.size();
	std::vector<int> temp(n);
	for (int i = 0; i < n; i++) {
		int shift = i + times;
		while (shift < 0)
			shift += n;
		if (shift >= n)
			shift %= n;
		temp[shift] = v[i];
	}

	return temp;
}

std::vector<int> xor_(const std::vector<int> &v1, const std::vector<int> &v2) {
	if (v1.size() != v2.size())
		throw "Both vector need to be of same size";

	std::vector<int> v3;
	for (int i = 0; i < v1.size(); i++) {
		v3.push_back(!(v1[i] == v2[i]));
	}

	return v3;
}

} // namespace des
