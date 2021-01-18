/*
	Hossam ElDin Khaled Mohamed Ali ElShaer
	16P3025
	DES
*/

#include "iostream"

#include <vector>
#include <string>
#include <map>

using namespace std;

int bin_to_dec_2bit(string input) {
	map<string, int> map;
	map["00"] = 0; map["01"] = 1; map["10"] = 2; map["11"] = 3;

	return map[input];
}
int bin_to_dec_4bit(string input) {
	map<string, int> map;
	map["0000"] = 0; map["0001"] = 1; map["0010"] = 2; map["0011"] = 3;
	map["0100"] = 4; map["0101"] = 5; map["0110"] = 6; map["0111"] = 7;
	map["1000"] = 8; map["1001"] = 9; map["1010"] = 10; map["1011"] = 11;
	map["1100"] = 12; map["1101"] = 13; map["1110"] = 14; map["1111"] = 15;

	return map[input];
}
string dec_to_bin_4bit(int input) {
	string map[16] = { "0000", "0001", "0010", "0011",
						"0100", "0101", "0110", "0111",
						"1000", "1001", "1010", "1011",
						"1100", "1101", "1110", "1111", };

	return map[input];
}
string hex_to_bin(string input) {
	map<char, string> map;
	map['0'] = "0000"; map['1'] = "0001"; map['2'] = "0010"; map['3'] = "0011";
	map['4'] = "0100"; map['5'] = "0101"; map['6'] = "0110"; map['7'] = "0111";
	map['8'] = "1000"; map['9'] = "1001"; map['A'] = "1010"; map['B'] = "1011";
	map['C'] = "1100"; map['D'] = "1101"; map['E'] = "1110"; map['F'] = "1111";

	string mapped_bin = "";
	for (int i = 0; i < input.length(); i++) {
		mapped_bin += map[input[i]];
	}

	return mapped_bin;
}
string bin_to_hex(string input) {
	map<string, char> map;
	map["0000"] = '0'; map["0001"] = '1'; map["0010"] = '2'; map["0011"] = '3';
	map["0100"] = '4'; map["0101"] = '5'; map["0110"] = '6'; map["0111"] = '7';
	map["1000"] = '8'; map["1001"] = '9'; map["1010"] = 'A'; map["1011"] = 'B';
	map["1100"] = 'C'; map["1101"] = 'D'; map["1110"] = 'E'; map["1111"] = 'F';

	string mapped_hex = "";
	for (int i = 0; i < input.length(); i+=4) {
		mapped_hex += map[input.substr(i, 4)];
	}

	return mapped_hex;
}

string permute(string input, int* permutation, int size) {
	string permuted = "";
	for (int i = 0; i < size; i++)
		permuted += input[permutation[i] - 1];

	return permuted;
}

string key_initial_permutation(string key) {
	int kp[56] = { 57, 49, 41, 33, 25, 17, 9,
					 1, 58, 50, 42, 34, 26, 18,
					 10, 2, 59, 51, 43, 35, 27,
					 19, 11, 3, 60, 52, 44, 36,
					 63, 55, 47, 39, 31, 23, 15,
					 7, 62, 54, 46, 38, 30, 22,
					 14, 6, 61, 53, 45, 37, 29,
					 21, 13, 5, 28, 20, 12, 4 };
	return permute(key, kp, 56);
}
string left_circular_shift(string round_key, int round_number) {
	int number_shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	int shifts = number_shifts[round_number];

	return round_key.substr(shifts, round_key.length() - shifts) + round_key.substr(0, shifts);
}
string key_comp_permutation(string round_key) {
	int cp[48] = { 14, 17, 11, 24, 1, 5,
					3, 28, 15, 6, 21, 10,
					 23, 19, 12, 4, 26, 8,
					 16, 7, 27, 20, 13, 2,
					 41, 52, 31, 37, 47, 55,
					 30, 40, 51, 45, 33, 48,
					 44, 49, 39, 56, 34, 53,
					 46, 42, 50, 36, 29, 32 };
	return permute(round_key, cp, 48);
}
vector<string> key_generator(string key) {
	vector<string> round_keys;

	string after_initial_per_56 = key_initial_permutation(key);
	string left_part = after_initial_per_56.substr(0, 28);
	string right_part = after_initial_per_56.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		left_part = left_circular_shift(left_part, i);
		right_part = left_circular_shift(right_part, i);

		string round_key = left_part + right_part;
		round_key = key_comp_permutation(round_key);

		round_keys.push_back(round_key);
	}

	return round_keys;
}

string input_inital_permutation(string input) {
	int ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
					60, 52, 44, 36, 28, 20, 12, 4,
					62, 54, 46, 38, 30, 22, 14, 6,
					64, 56, 48, 40, 32, 24, 16, 8,
					57, 49, 41, 33, 25, 17, 9, 1,
					59, 51, 43, 35, 27, 19, 11, 3,
					61, 53, 45, 37, 29, 21, 13, 5,
					63, 55, 47, 39, 31, 23, 15, 7 };

	return permute(input, ip, 64);
}
string expansion_permutation(string right_part) {
	int ep[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
					6, 7, 8, 9, 8, 9, 10, 11,
					12, 13, 12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21, 20, 21,
					22, 23, 24, 25, 24, 25, 26, 27,
					28, 29, 28, 29, 30, 31, 32, 1 };
	
	return permute(right_part, ep, 48);
}
string perform_xor(string plaintext, string round_key) {
	string result = "";
	for (int i = 0; i < plaintext.length(); i++) {
		result += ((plaintext[i] - 48) ^ (round_key[i] - 48)) + 48;
	}

	return result;
}
string substituion_sbox(string plaintext) {
	int sbox[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },

						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },

						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },

						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },

						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },

						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },

						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

	string after_sub = "";
	for (int i = 0; i < 8; i++) {
		string chunk = plaintext.substr(i * 6, 6);
		string row_text = ""; row_text += chunk[0]; row_text += chunk[5];
		string col_text = ""; col_text += chunk[1]; col_text += chunk[2]; col_text += chunk[3]; col_text += chunk[4];

		int row = bin_to_dec_2bit(row_text);
		int col = bin_to_dec_4bit(col_text);

		after_sub += dec_to_bin_4bit(sbox[i][row][col]);
	}

	return after_sub;
}
string final_permutation(string plaintext) {
	int fp[32] = { 16, 7, 20, 21, 29, 12, 28, 
					17, 1, 15, 23, 26, 5, 18, 31, 
					10, 2, 8, 24, 14, 32, 27, 3, 9,
					19, 13, 30, 6, 22, 11, 4, 25 };

	return permute(plaintext, fp, 32);
}
string inverser_first_permutation(string plaintext) {
	int ifp[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
					39, 7, 47, 15, 55, 23, 63, 31,
					38, 6, 46, 14, 54, 22, 62, 30,
					37, 5, 45, 13, 53, 21, 61, 29,
					36, 4, 44, 12, 52, 20, 60, 28,
					35, 3, 43, 11, 51, 19, 59, 27,
					34, 2, 42, 10, 50, 18, 58, 26,
					33, 1, 41, 9, 49, 17, 57, 25 };

	return permute(plaintext, ifp, 64);
}

string des_encryption(string plaintext, vector<string> round_keys) {
	string after_ip = input_inital_permutation(plaintext);

	string left_part = after_ip.substr(0, 32);
	string right_part = after_ip.substr(32, 32);
	for (int i = 0; i < 16; i++) {
		string right = expansion_permutation(right_part);
		
		right = perform_xor(right, round_keys[i]);

		right = substituion_sbox(right);

		right = final_permutation(right);

		left_part = perform_xor(left_part, right);

		if (i != 15)
			swap(left_part, right_part);
	}

	return inverser_first_permutation(left_part + right_part);
}

vector<string> dec_key_generator(vector<string> round_keys) {
	vector<string> dec_round_keys;
	for (int i = 15; i > -1; i--)
		dec_round_keys.push_back(round_keys[i]);

	return dec_round_keys;
}
string des_decryption(string ciphertext, vector<string> round_keys) {
	round_keys = dec_key_generator(round_keys);
	return des_encryption(ciphertext, round_keys);
}

int main() {
	cout << "Hossam ELShaer" << endl << "16P3025" << endl << "DES" << endl << endl;

	cout << "Enter 64-bit DES key in hex (use uppercase letters): ";
	string key;
	cin >> key;
	key = hex_to_bin(key);
	vector<string> round_keys = key_generator(key);
	
	cout << "Enter 64-bit plaintext in hex (use uppercase letters): ";
	string plaintext;
	cin >> plaintext;
	plaintext = hex_to_bin(plaintext);

	cout << "Enter number of times to run DES encryption: ";
	int n_times;
	cin >> n_times;

	string ciphertext = plaintext;
	for (int i = 0; i < n_times; i++)
		ciphertext = des_encryption(ciphertext, round_keys);
	
	cout << endl << "Ciphertext: " << bin_to_hex(ciphertext) << endl;

	cout << endl << endl << "Program finished! Close and start agin" << endl;
	string wait;
	cin >> wait;

	return 0;
}