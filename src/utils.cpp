#include <vector>
#include <string>

#include "utils.h"
namespace des
{
    std::vector<int> strToBinary(std::string s)
    {
        int n = s.length();
        std::vector<int> bin;
        for (int i = 0; i < n; i++)
        {
            int val = int(s[i]);
            while (val)
            {
                if (val % 2)
                    bin.push_back(1);
                else
                    bin.push_back(0);
                val /= 2;
            }
        }

        return bin;
    }

    std::vector<int> circular_shift(const std::vector<int> &v, int times)
    {
        std::vector<int> temp;
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            int shift = i + times;
            while (shift < 0)
                shift += n;
            if (shift >= n)
                shift %= n;
            temp[shift] = v[i];
        }

        return temp;
    }
} // namespace des
