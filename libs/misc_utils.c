#include "misc_utils.h"

char get_char_bit(char c, char n)
{
	char mask = 0x00;
	mask |= (1 << n);
	return (c & mask) != 0;
}
