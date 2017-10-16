#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <bitset>

#define INPUT_NAME "test.png"
#define OUTPUT_NAME "output.png"
#define NUMBER_OF_ERRORS 0.0001 //  1 - 1%
#define WITH_REPEATS true // true or false
#define NEW_SIZE size*8+3
using namespace std;


int main()
{
	srand(time(NULL));
	ifstream infile(INPUT_NAME, std::ifstream::binary);
	ofstream outfile(OUTPUT_NAME, std::ofstream::binary);

	infile.seekg(0, infile.end);
	long size = infile.tellg();
	infile.seekg(0);
	long number_of_bits_to_change = size*0.01*NUMBER_OF_ERRORS * 8; // *8 bo 8 bitow w bajcie
	long error_count = 0;
	cout << size << endl; // checking totalsize of bits
	cout << "Total number of errors that there should be " << number_of_bits_to_change << endl; // checking total number of bits to change
	char* buffer = new char[size];

	char* buffer2 = new char[NEW_SIZE];
	long random_byte;
	long random_bit;
	long sum = 0;
	bitset<8> foo, foo2, foo3;
	infile.read(buffer, size);
	for (int j = 0; j<size; j++) { // BIT PARZYSTOSCI
		foo2 = buffer[j];
		sum += foo2.count();
	}
	/////////// CRC ////////////////
	int const CRC_SIZE = 4;
	int const DIVIDER_SIZE = CRC_SIZE + 1;
	char divider[DIVIDER_SIZE] = "1111";
	char crc[CRC_SIZE] = "000";
	long long counter = 0;
	for (int i = 0; i<size; i++) {
		foo3 = bitset<8>(buffer[i]);
		for (int j = 0; j<8; j++) {
			if (foo3[7 - j] == 1)
				buffer2[counter] = '1';
			else if (foo3[7 - j] == 0)
				buffer2[counter] = '0';
			counter++;
		}
	}
	for (long i = size * 8; i<NEW_SIZE; i++)
		buffer2[i] = '0';
	//for(long long i=0; i<NEW_SIZE; i++)
	// cout << buffer2[i];

	long long save;
	for (long long i = 0; i<NEW_SIZE - 3; i++) {
		if (buffer2[i] == '1') {
			save = i;
			for (int j = 0; j<DIVIDER_SIZE - 1; j++) {
				if (divider[j] == '1' && buffer2[i + j] == '1')
					buffer2[i + j] = '0';
				else if (divider[j] == '1' && buffer2[i + j] == '0')
					buffer2[i + j] = '1';
				else if (divider[j] == '0' && buffer2[i + j] == '1')
					buffer2[i + j] = '1';
				else if (divider[j] == '0' && buffer2[i + j] == '0')
					buffer2[i + j] = '0';
			}
		}
		//  cout << buffer2 << " // " << endl;
	}
	//for(long long i=0; i<NEW_SIZE; i++)
	// cout << buffer2[i];
	cout << endl;
	crc[0] = buffer2[size * 8];
	crc[1] = buffer2[size * 8 + 1];
	crc[2] = buffer2[size * 8 + 2];
	cout << "CRC------------" << endl;
	cout << crc << endl;
	cout << "CRC------------" << endl;
	infile.read(buffer, size);
	cout << "-------------------------" << endl;
	cout << " Numberf of 1: " << sum << endl;
	cout << "Parity bit: " << sum % 2 << endl;
	cout << "Modulo sum: " << sum % 11 << endl; // SZCZEGOLNY PRZYPADEK MODULO 2
	cout << "-------------------------" << endl;

	if (WITH_REPEATS == true)
	{
		while (error_count < number_of_bits_to_change)
		{
			random_byte = rand() % size; // random byte
			random_bit = rand() % 8; // random bit
			foo = buffer[random_byte]; // actual byte to be changed
			cout << "changing " << foo << " byte, " << random_bit + 1 << " bit from ";
			if (foo.test(random_bit) == true)  // check if bit in byte is 1, set to 0, if not set 1
			{
				buffer[random_byte] &= ~(1 << random_bit);
				cout << " 1 to 0 ";
			}
			else
			{
				buffer[random_byte] |= 1 << random_bit;
				cout << " 0 to 1";
			}
			cout << "Now it's " << bitset<8>(buffer[random_byte]) << endl;
			error_count++;
		}
	}
	else
	{
		bool bool_tab[1000000]; // i
		while (error_count < number_of_bits_to_change)
		{
			random_byte = rand() % size;
			random_bit = rand() % 8;
			foo = buffer[random_byte];
			if (bool_tab[random_byte*random_bit] == false)
			{
				if (foo.test(random_bit) == true)
				{
					bool_tab[random_bit*random_byte] = true;
					cout << "changing " << foo << " byte, " << random_bit + 1 << " bit from 1 to 0 ";
					buffer[random_byte] &= ~(1 << random_bit);
					error_count++;
				}
				else
				{
					bool_tab[random_bit*random_byte] = true;
					cout << "changing " << foo << " byte, " << random_bit + 1 << " bit from 0 to 1 ";
					buffer[random_byte] |= 1 << random_bit;
					error_count++;
				}
				cout << "Now it's " << bitset<8>(buffer[random_byte]) << endl;
			}
		}
	}
	outfile.write(buffer, size);

	delete[] buffer;
	delete[] buffer2;

	outfile.close();
	infile.close();
	return 0;
}
