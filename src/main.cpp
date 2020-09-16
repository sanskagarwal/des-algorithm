#include <iostream>

#include "base/des_interface.h"
#include "hex_maps.h"

int main() {

	std::cout << "DES Encryption\n\n";

	int usage, input_type;
	std::string encrypt_str, decrypt_str;
	des::Des des_object;
	std::cout << "1. Encrypt\t 2. Decrypt: ";
	std::cin >> usage;
	if (!(usage == 1 || usage == 2)) {
		std::cout << "Error! Exiting...";
		return 0;
	}

	std::cout << "1. Text\t 2. File: ";
	std::cin >> input_type;
	switch (input_type) {
	case 1: {
		std::string text, key;
		std::cout << "Enter input text (in hex): ";
		std::cin >> text;
		std::cout << "Enter Key (in hex): ";
		std::cin >> key;
		std::cout << "Mode: ECB(electronic codebook), Padding Mode: PKCS#7\n\n";

		if (key.size() % 2 || text.size() % 2) {
			std::cout << "Invalid hex string";
			return 0;
		}

		if (usage == 1) {
			int text_len = text.size();

			if (text_len % 16 != 0) {
				int padding_len = 8 - (text_len / 2) % 8;
				std::string padding_text = "0";
				padding_text += hex_int_to_char.at(padding_len);

				for (int i = 0; i < padding_len; i++)
					text += padding_text;
			}
			des_object.encrypt(key, text, encrypt_str);
		} else {
			des_object.decrypt(key, text, decrypt_str);

			int str_len = decrypt_str.length();
			bool is_padded = false;
			char last_char = decrypt_str[str_len - 1];
			char second_last_char = decrypt_str[str_len - 2];
			int cnt = hex_char_to_int.at(last_char);

			// If it is of the form 0x where x is less than 8.
			if (second_last_char == '0' && cnt < 8 && cnt > 0) {
				int eq_cnt = 0;
				for (int i = str_len - 1; i >= 0; i -= 2) {
					if (decrypt_str[i] == last_char
							&& decrypt_str[i - 1] == second_last_char)
						eq_cnt++;
				}

				if (eq_cnt == cnt)
					is_padded = true;
			}

			if (is_padded) {
				int end_index = str_len - 2 * cnt;
				decrypt_str = decrypt_str.substr(0, end_index);
			}
		}
		break;
	}
	case 2: {
		std::cout << "To be added soon!!";
		break;
	}
	default: {
		std::cout << "Error! Exiting...";
		return 0;
		break;
	}
	}

	if (usage == 1)
		std::cout << "Encrypted form: " << encrypt_str << "\n";
	else
		std::cout << "Decrypted form: " << decrypt_str << "\n";

	return 0;
}
