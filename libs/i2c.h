#ifndef i2c
#define i2c

#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../avr_common/uart.h" 


//0 per LOW, 1 per HIGH
char CLOCK_LEVEL;
//Address for the slave
uint8_t ADDRESS;


void begin();
void begin(uint8_t address);
void clock_start();
void clock_zero();


