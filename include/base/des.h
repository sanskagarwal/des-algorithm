/*
 * DES Cipher algorithm operations
 * 
 * Author: Sanskar Agarwal <sanskaragarwal.500@gmail.com>
*/

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8

namespace des
{
    class Des
    {
    private:
        int key_len;

    public:
        void encrypt(std::string key, const std::string src, std::string dest);

        void decrypt(std::string key, const std::string src, std::string dest);
    };
} // namespace des