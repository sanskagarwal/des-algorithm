/**
 * DES Cipher algorithm operations
 *
 * Author: Sanskar Agarwal <sanskaragarwal.500@gmail.com>
 */

#include <string>
#include <vector>

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8

namespace des {
/**
 * @brief Interface for the DES algorithm.
 *
 */
class Des {
public:
	/**
	 * @brief Encrypts the src message with the key and returns in dest.
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

private:
	/**
	 * @brief Calculate S box from start to next 6 bits.
	 *
	 * @param v
	 * @param start
	 * @param group
	 * @return int
	 */
	int calculate_s_box(std::vector<int> v, int start, int group);
};
} // namespace des
