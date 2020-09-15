#pragma once

namespace des
{
    /**
     * @brief Convert a string into binary represented as vector of integers.
     *
     * @param s
     * @return std::vector<int>
     */
    std::vector<int> strToBinary(std::string s);

    /**
     * @brief Shifts the values in a vector according to the specified bits.
     *
     * @param v
     * @param times
     *      if [+ve], returns right shift
     *      else, returns left shift
     */
    std::vector<int> circular_shift(const std::vector<int> &v, int times);
} // namespace des
