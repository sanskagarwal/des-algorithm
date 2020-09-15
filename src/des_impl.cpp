#include <assert.h>
#include <base/des_interface.h>

#include <vector>
#include <string>

#include "utils.h"
#include "constants.h"

namespace des {
void Des::encrypt(std::string key, const std::string src, std::string &dest) {
	// Key Validation.
	if (key.size() != DES_KEY_SIZE || src.size() != DES_BLOCK_SIZE)
		throw "Invalid Data";

	std::vector<int> keys[16];
	generate_keys(key, keys);

	dest = generate_des(src, keys);
}

void Des::decrypt(std::string key, const std::string src, std::string &dest) {
// Data Validation
	if (key.size() != DES_KEY_SIZE)
		throw "Invalid Key length";

	std::vector<int> keys[16];
	generate_keys(key, keys);

	for (int i = 0; i < 8; i++) {
		std::vector<int> temp = keys[i];
		keys[i] = keys[16 - i - 1];
		keys[16 - i - 1] = temp;
	}

	dest = generate_des(src, keys);
}

void Des::generate_keys(std::string key, std::vector<int> keys[]) {
	int i;

	// Create 16 subkeys, each of which is 48-bits.
	std::vector<int> bin_key = des::str_to_binary(key);
	std::vector<int> perm_key;

	for (i = 0; i < 56; i++)
		perm_key.push_back(bin_key[pc1[i] - 1]);

	int perm_key_bits = perm_key.size();
	std::vector<int> c_key[17], d_key[17];
	for (i = 0; i < perm_key_bits / 2; i++) {
		c_key[0].push_back(perm_key[i]);
		d_key[0].push_back(perm_key[i + perm_key_bits / 2]);
	}

	for (i = 1; i < 17; i++) {
		c_key[i] = des::circular_shift(c_key[i - 1], -shift_table[i - 1]);
		d_key[i] = des::circular_shift(d_key[i - 1], -shift_table[i - 1]);
	}

	for (i = 0; i < 16; i++) {
		for (int j = 0; j < 48; j++) {
			int num = pc2[j];
			if (num > 28)
				keys[i].push_back(d_key[i + 1][num - 28 - 1]);
			else
				keys[i].push_back(c_key[i + 1][num - 1]);
		}
	}
}

std::string Des::generate_des(std::string src, std::vector<int> keys[]) {
	int i;

	// Encode each 64-bit block of data.
	std::vector<int> bin_src = des::str_to_binary(src);
	std::vector<int> perm_src;
	for (i = 0; i < bin_src.size(); i++)
		perm_src.push_back(bin_src[ip[i] - 1]);

	int perm_src_bits = perm_src.size();
	std::vector<int> l_src[17], r_src[17];
	for (i = 0; i < perm_src_bits / 2; i++) {
		l_src[0].push_back(perm_src[i]);
		r_src[0].push_back(perm_src[i + perm_src_bits / 2]);
	}

	for (i = 1; i < 17; i++) {
		l_src[i] = r_src[i - 1];
		std::vector<int> r_src_exp;
		for (int j = 0; j < 48; j++) {
			r_src_exp.push_back(r_src[i - 1][ebit_table[j] - 1]);
		}

		std::vector<int> key_rsrc_xor = des::xor_(r_src_exp, keys[i - 1]);
		std::vector<int> sb;
		for (int j = 0; j < key_rsrc_xor.size(); j += 6) {
			int num = calculate_s_box(key_rsrc_xor, j, j / 6 + 1);
			std::vector<int> temp = des::int_to_binary(num, 4);
			sb.insert(sb.end(), temp.begin(), temp.end());
		}

		std::vector<int> sb_p;
		for (int j = 0; j < sb.size(); j++)
			sb_p.push_back(sb[per[j] - 1]);
		r_src[i] = des::xor_(l_src[i - 1], sb_p);
	}

	std::vector<int> comb;
	comb.insert(comb.end(), r_src[16].begin(), r_src[16].end());
	comb.insert(comb.end(), l_src[16].begin(), l_src[16].end());

	std::string dest;
	for (i = 0; i < comb.size(); i++) {
		dest += comb[ip_inv[i] - 1] == 1 ? '1' : '0';
	}

	return dest;
}

int Des::calculate_s_box(std::vector<int> v, int start, int group) {
	if (start + 6 > v.size())
		throw "Invalid start call";
	if (group > 8)
		throw "Invalid Group";

	int i = v[start] * 2 + v[start + 5] * 1;
	int j = v[start + 1] * 8 + v[start + 2] * 4 + v[start + 3] * 2
			+ v[start + 4] * 1;

	return s_box[group - 1][i][j];
}
} // namespace des
