#include "misc_utils.h"

//Conta da destra quindi dal bit meno significativo
char get_char_bit(char c, char n)
{
	char mask = 0x00;
	mask |= (1 << n);
	return (c & mask) != 0;
}

//mi serve per la read, setta a 1 l'n-esimo bit di c e lo ritorna (se deve settare a 0 non la chiamo)
//c viene azzerato dopo 8 bit SEMPRE
char set_char_bit(char c, char n){
	c|=1<<n;
	return c;
}
