/**
 * DES Cipher algorithm operations
 *
 * Author: Sanskar Agarwal <sanskaragarwal.500@gmail.com>
 */

#include <string>
#include <vector>

#define DES_KEY_SIZE 16
#define DES_BLOCK_SIZE 16

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

	/**
	 * @brief Generate 16 cypher keys each of 48 bit from the key.
	 *
	 * @param key
	 * @param keys
	 */
	void generate_keys(std::string key, std::vector<int> keys[]);

	/**
	 * @brief Generate the des cypher of the source string from the keys.
	 *
	 * @param src
	 * @param keys
	 * @return std::string
	 */
	std::string generate_des(std::string src, std::vector<int> keys[]);
};
} // namespace des
