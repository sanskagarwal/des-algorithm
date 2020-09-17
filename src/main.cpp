#include <iostream>
#include <fstream>
#include <iomanip>

#include "base/des_interface.h"

#include "hex_maps.h"

void pad_hex_string(std::string &text) {
	int text_len = text.size();

	if (text_len % 16 != 0) {
		int padding_len = 8 - (text_len / 2) % 8;
		std::string padding_text = "0";
		padding_text += hex_int_to_char.at(padding_len);

		for (int i = 0; i < padding_len; i++)
			text += padding_text;
	}
}

void unpad_hex_string(std::string &text) {

	int str_len = text.length();
	bool is_padded = false;
	char last_char = text[str_len - 1];
	char second_last_char = text[str_len - 2];
	int cnt = hex_char_to_int.at(last_char);

	// If it is of the form 0x where x is less than 8.
	if (second_last_char == '0' && cnt < 8 && cnt > 0) {
		int eq_cnt = 0;
		for (int i = str_len - 1; i >= 0; i -= 2) {
			if (text[i] == last_char && text[i - 1] == second_last_char)
				eq_cnt++;
		}

		if (eq_cnt == cnt)
			is_padded = true;
	}

	if (is_padded) {
		int end_index = str_len - 2 * cnt;
		text = text.substr(0, end_index);
	}
}

int main() {

	std::cout
			<< "DES Encryption\nMode: ECB(electronic codebook), Padding Mode: PKCS#7\n\n";

	int usage, input_type;
	std::string encrypt_str, decrypt_str;
	des::Des des_object;
	std::cout << "1. Encrypt \t 2. Decrypt: ";
	std::cin >> usage;
	if (!(usage == 1 || usage == 2)) {
		std::cout << "Error! Exiting...";
		return 0;
	}

	std::cout << "1. Text \t 2. File: ";
	std::cin >> input_type;
	switch (input_type) {
	case 1: {
		std::string text, key;
		std::cout << "Enter input text (in hex): ";
		std::cin >> text;
		std::cout << "Enter Key (in hex): ";
		std::cin >> key;

		std::clock_t start_time = clock();

		if (key.size() % 2 || text.size() % 2) {
			std::cout << "Invalid hex string";
			return 0;
		}

		if (usage == 1) {
			pad_hex_string(text);
			for (int i = 0; i < text.size(); i += 16) {
				std::string encrypt_text;
				des_object.encrypt(key, text.substr(i, 16), encrypt_text);
				encrypt_str += encrypt_text;
			}
			std::cout << "Encrypted form: " << encrypt_str << "\n";
		} else {
			for (int i = 0; i < text.size(); i += 16) {
				std::string decrypt_text;
				des_object.decrypt(key, text.substr(i, 16), decrypt_text);
				decrypt_str += decrypt_text;
			}
			unpad_hex_string(decrypt_str);
			std::cout << "Decrypted form: " << decrypt_str << "\n";
		}

		std::clock_t stop_time = clock();
		double time_taken = double(stop_time - start_time)
				/ double(CLOCKS_PER_SEC);
		std::cout << "\nTime Elapsed : " << std::fixed << time_taken
				<< std::setprecision(5) << " s\n";

		break;
	}
	case 2: {
		std::string fname, key, out_fname;
		std::cout << "Enter filename: ";
		std::cin >> fname;
		std::cout << "Enter output filename: ";
		std::cin >> out_fname;
		std::cout << "Enter Key (in hex): ";
		std::cin >> key;

		std::clock_t start_time = clock();

		std::ifstream inp_file;
		std::ofstream out_file;
		inp_file.open(fname, std::ios::in | std::ios::binary | std::ios::ate);
		out_file.open(out_fname,
				std::ios::out | std::ios::trunc | std::ios::binary);
		if (inp_file.is_open()) {
			std::streampos size = inp_file.tellg();
			char *memblock = new char[size];
			inp_file.seekg(0, std::ios::beg);
			inp_file.read(memblock, size);
			inp_file.close();

			std::string buffer(memblock, memblock + size);
			std::ostringstream hex_buffer_stream;
			for (int i = 0; i < buffer.size(); i++) {
				int bin_repr = buffer[i] & 0xff;
				hex_buffer_stream << std::hex << std::setfill('0')
						<< std::setw(2) << std::nouppercase << bin_repr;
			}

			std::string hex_buffer = hex_buffer_stream.str();
			std::string text_to_save;
			if (usage == 1) {
				pad_hex_string(hex_buffer);
				for (int i = 0; i < hex_buffer.size(); i += 16) {
					std::string encrypt_text;
					des_object.encrypt(key, hex_buffer.substr(i, 16),
							encrypt_text);
					encrypt_str += encrypt_text;
				}

				text_to_save = encrypt_str;
			} else {
				for (int i = 0; i < hex_buffer.size(); i += 16) {
					std::string decrypt_text;
					des_object.decrypt(key, hex_buffer.substr(i, 16),
							decrypt_text);
					decrypt_str += decrypt_text;
				}

				unpad_hex_string(decrypt_str);
				text_to_save = decrypt_str;
			}

			if (out_file.is_open()) {
				out_file.write(&text_to_save[0], text_to_save.size());
				out_file.close();

				std::cout << "Outfile written successfully!!";
			} else {
				std::cout << "Error writing file, Exiting..";
			}
		} else {
			std::cout << "Error opening file, Exiting..";
		}

		std::clock_t stop_time = clock();
		double time_taken = double(stop_time - start_time)
				/ double(CLOCKS_PER_SEC);
		std::cout << "\nTime Elapsed : " << std::fixed << time_taken
				<< std::setprecision(5) << " s\n";

		break;
	}
	default: {
		std::cout << "Error! Exiting...";
		break;
	}
	}

	return 0;
}
