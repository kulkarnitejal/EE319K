// Piano.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 3 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: Tejal Kulkarni & Meha Halabe
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// PortB0-3 for DAC PortA2-4 for keys

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Piano_Init*********************
// Initialize piano key inputs, called once to initialize the digital ports
// Input: none 
// Output: none
void Piano_Init(void)
{
	int delay;
	SYSCTL_RCGCGPIO_R |=  0x01;
	delay+=123456;
	
	GPIO_PORTA_DIR_R &=0XE3;										//initialize port A bits 2-4
	GPIO_PORTA_DEN_R |=0X1C;
	
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
//   bit n is set if key n is pressed
uint32_t Piano_In(void){
	int bit2= GPIO_PORTA_DATA_R &	0X04;					
	bit2 = bit2>>2;																	//bit2 into bit0 position
	int bit3= GPIO_PORTA_DATA_R &	0X08;
	bit3 = bit3>>2;																	//bit3 into bit1 position
	int bit4= GPIO_PORTA_DATA_R &	0X10;
	bit4 = bit4>>2;																	//bit4 into pit2 position
	
	return bit2|bit3|bit4;													//keys pressed (0-7)
	
}
