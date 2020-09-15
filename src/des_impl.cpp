#include "base/des.h"
#include "utils.h"
#include "constants.h"

#include <vector>
#include <string>

namespace des
{
    void Des::encrypt(std::string key, const std::string src, std::string dest)
    {
        // Key Validation.
        if (key.size() != DES_KEY_SIZE)
            throw "Invalid Key length";

        // Create 16 subkeys, each of which is 48-bits.
        std::vector<int> bin_key = strToBinary(key);
        std::vector<int> perm_key;

        for (int i = 0; i < bin_key.size(); i++)
        {
            perm_key.push_back(bin_key[pc1[i]]);
        }
    }

    void Des::decrypt(std::string key, const std::string src, std::string dest)
    {
        // Data Validation
        if (key.size() != DES_KEY_SIZE)
            throw "Invalid Key length";
    }
} // namespace des