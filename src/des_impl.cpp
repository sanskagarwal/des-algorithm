#include "base/des.h"
#include "utils.h"
#include "constants.h"

#include <vector>
#include <string>

namespace des
{
    void Des::encrypt(std::string key, const std::string src, std::string &dest)
    {
        // Key Validation.
        if (key.size() != DES_KEY_SIZE)
            throw "Invalid Key length";

        int i;

        // Create 16 subkeys, each of which is 48-bits.
        std::vector<int> bin_key = strToBinary(key);
        std::vector<int> perm_key;

        for (i = 0; i < bin_key.size(); i++)
            perm_key.push_back(bin_key[pc1[i]]);

        int perm_key_bits = perm_key.size();
        std::vector<int> c_key[17], d_key[17];
        for (i = 0; i < perm_key_bits / 2; i++)
        {
            c_key[0].push_back(perm_key[i]);
            d_key[0].push_back(perm_key[i + perm_key_bits / 2]);
        }

        for (i = 1; i < 17; i++)
        {
            c_key[i] = circular_shift(c_key[i - 1], shift_table[i - 1]);
            d_key[i] = circular_shift(d_key[i - 1], shift_table[i - 1]);
        }
    }

    void Des::decrypt(std::string key, const std::string src, std::string &dest)
    {
        // Data Validation
        if (key.size() != DES_KEY_SIZE)
            throw "Invalid Key length";
    }
} // namespace des
