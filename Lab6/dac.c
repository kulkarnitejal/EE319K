// dac.c
// This software configures DAC output
// Lab 6 requires a minimum of 4 bits for the DAC, but you could have 5 or 6 bits
// Runs on LM4F120 or TM4C123
// Program written by: Tejal Kulkarni & Meha Halabe
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// PortB0-3 for DAC PortA2-4 for keys

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void)
{
	int delay;
	SYSCTL_RCGCGPIO_R |=  0x02;
	delay+=123456;
	
	GPIO_PORTB_DIR_R |=0X0F;																								//initialization of portb 0-3 as output
	GPIO_PORTB_DEN_R |=0X0F;

}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data)
{
	GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | (data & 0xF);					//convert data to voltage for dac
	
}

