/**
 * DES Cipher algorithm operations
 *
 * Author: Sanskar Agarwal <sanskaragarwal.500@gmail.com>
 */

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8

namespace des
{
    /**
     * @brief Interface for the DES algorithm.
     *
     */
    class Des
    {
    private:
        int key_len;

    public:
        /**
         * @brief Encypts the src message with the key and returns in dest.
         *
         * @param key
         * @param src
         * @param dest
         */
        void encrypt(std::string key, const std::string src, std::string &dest);

        /**
         * @brief Decrypts the src message with the key and returns in dest.
         *
         * @param key
         * @param src
         * @param dest
         */
        void decrypt(std::string key, const std::string src, std::string &dest);
    };
} // namespace des
