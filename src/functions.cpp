#include "functions.h"
#include "main.h"

std::string sevenSegment(char s)
{
	switch(s)
	{
		case '1':
			return "0011000";
		case '2':
			return "0110111";
		case '3':
			return "0111101";
		case '4':
			return "1011001";
		case '5':
			return "1101101";
		case '6':
			return "1101111";
		case '7':
			return "0111000";
		case '8':
			return "1111111";
		case '9':
			return "1111101";
		case '0':
			return "1111110";
		case 'S':
			return "1101101";
		case 'C':
			return "1100110";
		case 'O':
			return "1111110";
		case 'R':
			return "1111011";
		case 'E':
			return "1100111";
		case '-':
			return "0000001";
	}
}