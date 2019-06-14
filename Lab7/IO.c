// IO.c
// This software configures the switch and LED
// You are allowed to use any switch and any LED, 
// although the Lab suggests the SW1 switch PF4 and Red LED PF1
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: March 30, 2018
// Last Modified:  change this or look silly
// Lab number: 7


#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h" 

//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void) {
 // --UUU-- Code to initialize PF4 and PF2
	volatile int delay;
		SYSCTL_RCGCGPIO_R |=0X20;										//turn on clock 
		delay +=123456;	
	GPIO_PORTF_DIR_R &=0XEF;											//initialize pf4 as input, pf2 as output
	GPIO_PORTF_DIR_R |=0X04;
	GPIO_PORTF_DEN_R |= 0X14;
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;						//unlock port f
	GPIO_PORTF_PUR_R |=0X10;											//pull up resistor for negative logic
	GPIO_PORTF_CR_R |= 0XFFFFFFFF;					
	
}


//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void) {
 // --UUU-- PF2 is heartbeat
	GPIO_PORTF_DATA_R ^= 0X04;										//toggle led in pf2
}


//------------IO_Touch------------
// wait for release and press of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void) {
 // --UUU-- wait for release; delay for 20ms; and then wait for press
	uint32_t data =GPIO_PORTF_DATA_R & 0X00000010; //data has pf4		
	while(data == 0x00)														 //while pressed
	{
		data =GPIO_PORTF_DATA_R & 0X00000010;				 //wait for release
	
	}
	Delay1ms(20);																	 //Delay1ms 20ms
	while(data !=0x00)														 //while released
	{
		data =GPIO_PORTF_DATA_R & 0X00000010;				 //wait for press
	}
}  

