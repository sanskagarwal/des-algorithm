#pragma once

#include <unordered_map>

const std::unordered_map<char, int> hex_char_to_int { { '0', 0 }, { '1', 1 }, { '2', 2 }, {
		'3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 }, { '8', 8 }, {
		'9', 9 }, { 'a', 10 }, { 'b', 11 }, { 'c', 12 }, { 'd', 13 },
		{ 'e', 14 }, { 'f', 15 } };

const std::unordered_map<int, char> hex_int_to_char { { 0, '0' }, { 1, '1' },
		{ 2, '2' }, { 3, '3' }, { 4, '4' }, { 5, '5' }, { 6, '6' }, { 7, '7' },
		{ 8, '8' }, { 9, '9' }, { 10, 'a' }, { 11, 'b' }, { 12, 'c' },
		{ 13, 'd' }, { 14, 'e' }, { 15, 'f' } };
