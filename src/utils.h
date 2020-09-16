#pragma once

namespace des {
/**
 * @brief Convert a hex string into binary represented as vector of integers.
 *
 * @param s
 * @return std::vector<int>
 */
std::vector<int> hex_str_to_binary(std::string s);

/**
 * @brief Convert an integer to binary form with specified size.
 *
 * @param num
 * @param size
 * @return std::vector<int>
 */
std::vector<int> int_to_binary(int num, int size);

/**
 * @brief Shifts the values in a vector according to the specified bits.
 *
 * @param v
 * @param times
 *      if [+ve], returns right shift
 *      else, returns left shift
 * @return std::vector<int>
 */
std::vector<int> circular_shift(const std::vector<int> &v, int times);

/**
 * @brief Calculate the xor of two vector of same size.
 *
 * @param v1
 * @param v2
 * @return std::vector<int>
 */
std::vector<int> xor_(const std::vector<int> &v1, const std::vector<int> &v2);
} // namespace des
