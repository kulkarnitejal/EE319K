// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// PortB0-3 for DAC PortA2-4 for keys

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"
#include "Music.h"

const unsigned short wave[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};		
//const unsigned short small[32] = {3,3,4,8,9,9,14,15,15,15,14,9,9,8,4,3,5,4,3,4,3,2,2,1,1,1,1,1,3,4,5,7};	
unsigned short small[32] = {3,3,4,4,4,5,5,5,5,5,5,5,4,4,4,3,3,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2};	
uint32_t ind;
extern int val;
extern int value;
// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
		ind=0;
		DAC_Init();
		NVIC_ST_CTRL_R &=0;
		NVIC_ST_RELOAD_R|=0X00FFFFFF;
		NVIC_ST_CURRENT_R&=0;
		NVIC_ST_CTRL_R|=0X07;								//enable Systick interrupt bit
  
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period)
{
		if(period ==0)
		{
			NVIC_ST_CTRL_R = 0x00;									//if nothing pressed, disable systick
			return;
		}
		NVIC_ST_CTRL_R = 0x07;										//reenable systick
		NVIC_ST_RELOAD_R = (period) &0x00FFFFFF;
		
}
void SysTick_Handler()
{
	int temp=wave[ind];													
	if(isPressed()== 0)													
	{
		//envelope
	if((value>=8&&value<=15)||(value>=24&&value<=31)||(value>=40&&value<=47)||(value<=56&&value>=63))
	{
		temp= small[ind]*2;												//if notes are between ranges listed above, multiply sine wave by 2 
	}
	
	else	if((value>=16&&value<=23)||(value>=48&&value<=55))
	{
		temp= small[ind]*3;												//multiple amplitude of sine wave by 3
	}	
	
		DAC_Out(temp);
	ind=(ind+1)%32;															//increment through struct
		
	}
	else
	{
		DAC_Out(wave[ind]);												//else use regular sine wave for notes
		ind=(ind+1)%32;
	}
}
