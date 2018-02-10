//============================================================================
// Name        : i3e754.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
using namespace std;

/*
 * ieee754.c
 *
 *  Created on: Feb 10, 2018
 *      Author: fgrando
 */

/* bit order in memory (start from bit 0, left to right)
 * single precision:
 * sign (1 bit) - exponent (7 bits) - significand (24 bits) = 32 bits in total
 */


//is easy to deal with bitwise operations using int than float
typedef union {
	int i;
	float f;
} uFloat;


// todo: create a runtime detection of endianness
int isLittleEndian = 1;


// print the 32 bits of the integer sent as parameter
void printBits(int val)
{
	for(int i = 0; i < 32; i++)
	{
		cout << ((val&(0x1<<i))?'1':'0');
		if ((i == 0)||(i == 7))
			cout<<" ";
	}
	cout << endl;
}


// print the float value in decimal and binary (splited for each type)
void printFloat(uFloat *val)
{
	uFloat f = *val;
	int len = 32;

	cout << "[" << f.f << "]" << endl;
	cout << "                                 3" << endl;
	cout << "0 1.....7 8......................1" << endl;

	// the data is displayed in big endian, so convert it to BE if the current machine is little endian
	if (isLittleEndian)
	{
		uFloat bigEndian;
		bigEndian.i = 0;
		for (int i = 0; i < len; i++)
		{
			if(f.i & (0x1 << i))
			{
				bigEndian.i |= (0x1 << (len-1-i));
			}
		}
		f = bigEndian;
	}
	printBits(f.i);
}


// convert a string of zero and ones in float
uFloat convertStrToFloat(const char *str, int len)
{
	uFloat ret;
	ret.i = 0;

	// load user binary input into float
	for(int i = 0; i < len; i++)
	{
		if(str[i] == '1')
		{
			ret.i|=(0x1<<i);
		}
	}

	// put it back in little endian (the user typed in big endian order)
	if (isLittleEndian)
	{
		uFloat littleEndian;
		littleEndian.i = 0;
		for (int i = 0; i < len; i++)
		{
			if(ret.i & (0x1 << i))
			{
				littleEndian.i |= (0x1 << (len-1-i));
			}
		}
		ret = littleEndian;
	}

	return ret;
}


int main() {
	// initialization
	uFloat myFloat;
	myFloat.i = 0;

	// loop displaying the current float value in BIG ENDIAN
	// the user can input a float value to see its binary representation
	// or otherwise can input the binary representation and get the correspondent value
	while (true)
	{
		string line;
		string signal;
		string expont;
		string signif;

		printFloat(&myFloat);
		getline(cin, line); // read the user input: a float value or 3 binary values separated by space
		stringstream ss(line);

		// parse the input
		ss >> signal >> expont >> signif;

		cout << endl;
		if (signif == "") // if there were less than 3 values, consider that the user typed a float value
		{
			istringstream ssFloatInput(signal);
			if(!(ssFloatInput >> myFloat.f))
				cout << signal << "could not be converted" << endl;
			continue;
		}

		// otherwise update current float with the typed binary
		string newFloat = signal + expont + signif;
		myFloat = convertStrToFloat(newFloat.c_str(), newFloat.length());
	}

	return 0;
}
